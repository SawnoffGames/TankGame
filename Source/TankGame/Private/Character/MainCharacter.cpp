// Copyright (c) Sawnoff Games. All rights reserved.


#include "Character/MainCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Input/CharacterPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Shared/Vehicle.h"

AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	AttackCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("AttackCapsule"));
	AttackCapsule->InitCapsuleSize(10.f, 30.f);
	AttackCapsule->CanCharacterStepUpOn = ECB_No;
	AttackCapsule->SetGenerateOverlapEvents(true);
	AttackCapsule->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	AttackCapsule->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("LeftHandSocket"));
	AttackCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	CameraZoomTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("CameraZoomTimeline"));
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	StartFOV = FollowCamera->FieldOfView;
	DesiredFOV = StartFOV;

	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->ViewPitchMin = -30;
	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->ViewPitchMax = 30;

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMainCharacter::OnComponentBeginOverlap_CapsuleComponent);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AMainCharacter::OnComponentEndOverlap_CapsuleComponent);
	AttackCapsule->OnComponentBeginOverlap.AddDynamic(this, &AMainCharacter::OnComponentBeginOverlap_AttackCapsule);
	
	if (CameraZoomCurve)
	{
		CameraZoomTimelineUpdate.BindUFunction(this, FName("OnCameraZoomTimelineUpdate"));
		CameraZoomTimelineFinished.BindUFunction(this, FName("OnCameraZoomTimelineFinished"));
		
		CameraZoomTimeline->AddInterpFloat(CameraZoomCurve, CameraZoomTimelineUpdate);
		CameraZoomTimeline->SetTimelineFinishedFunc(CameraZoomTimelineFinished);
		CameraZoomTimeline->SetLooping(false);
	}
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float FOV = FMath::Lerp(FollowCamera->FieldOfView, DesiredFOV, DeltaTime * 10.0f);
	FollowCamera->SetFieldOfView(FOV);
}

void AMainCharacter::Aim(bool aim)
{
	bIsAiming = aim;
	bUseControllerRotationYaw = aim;
	DesiredFOV = (aim ? AimFOV : StartFOV);
	FollowCamera->bUsePawnControlRotation = aim;
}

void AMainCharacter::Attack()
{
	if (bIsAiming)
	{
		PlayMeleeAttackAnimation();
	}
}

void AMainCharacter::ActivateAttack(bool activate) const
{
	if (activate)
	{
		AttackCapsule->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else
	{
		AttackCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

bool AMainCharacter::IsAttacking() const
{
	UAnimInstance* AnimInstance = GetMesh() ? GetMesh()->GetAnimInstance() : nullptr;

	if (AnimInstance && AttackMontage)
	{
		return AnimInstance->Montage_IsPlaying(AttackMontage);
	}

	return false;
}

void AMainCharacter::ZoomCamera(float ActionValue)
{
	if (!bIsAiming && bIsZoomFinished)
	{
		bIsZoomFinished = false;
		
		ZoomValue = ActionValue;

		CameraZoomTimeline->SetTimelineLength(0.3f);
		CameraZoomTimeline->PlayFromStart();
	}
}

void AMainCharacter::OnComponentBeginOverlap_AttackCapsule(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != this && OtherActor->IsA(ACharacter::StaticClass()))
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, TEXT("Hit Other Character"));
		}
	}

	UGameplayStatics::ApplyDamage(OtherActor,	// Damaged Actor
		25,										// Damage
		Cast<APawn>(this)->GetController(),		// Instigator (Controller)
		this,									// Damage Causer (Actor)
		UDamageType::StaticClass());			// Default damage type
}

void AMainCharacter::OnComponentBeginOverlap_CapsuleComponent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != this && OtherActor->GetClass()->ImplementsInterface(UVehicle::StaticClass()))
	{
		if (ACharacterPlayerController* PlayerController = Cast<ACharacterPlayerController>(GetController()))
		{
			PlayerController->ControllableVehicle = OtherActor;
		}
	}
}

void AMainCharacter::OnComponentEndOverlap_CapsuleComponent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ACharacterPlayerController* PlayerController = Cast<ACharacterPlayerController>(GetController()))
	{
		PlayerController->ControllableVehicle = nullptr;
	}
}

void AMainCharacter::PlayMeleeAttackAnimation()
{
	if (AttackMontage)
	{
		if (GetCurrentMontage() == nullptr)
		{
			PlayAnimMontage(AttackMontage);

			Aim(false);
		}
		else
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Red, TEXT("MyBaseCharacter: AttackMontage already playing"));
			}
		}
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Red, TEXT("MyBaseCharacter: Cannot play AttackMontage"));
		}
	}
}

void AMainCharacter::OnCameraZoomTimelineUpdate(float TimelineAlpha)
{
	float TargetArmLength = CameraBoom->TargetArmLength;
	float DesiredArmLength = TargetArmLength - ZoomValue;
	
	float ClampedAlpha = FMath::Clamp(DesiredArmLength, MinZoomLevel, MaxZoomLevel);
	float LerpValue = FMath::Lerp(TargetArmLength, ClampedAlpha, TimelineAlpha);
	
	CameraBoom->TargetArmLength = LerpValue;
}

void AMainCharacter::OnCameraZoomTimelineFinished()
{
	bIsZoomFinished = true;
}
