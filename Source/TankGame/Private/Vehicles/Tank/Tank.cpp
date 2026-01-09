// Copyright (c) Sawnoff Games. All rights reserved.


#include "Vehicles/Tank/Tank.h"

#include "ChaosWheeledVehicleMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Camera/CameraComponent.h"
#include "Characters/MainCharacter/MainCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Particles/ParticleSystemComponent.h"
#include "Vehicles/Tank/TankAmmo.h"
#include "Vehicles/Tank/TankWheel.h"

class UEnhancedInputLocalPlayerSubsystem;

ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = true;

	ExitSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ExitSpawnPoint"));
	ExitSpawnPoint->SetupAttachment(GetMesh());

	EnterVehicleBox = CreateDefaultSubobject<UBoxComponent>(TEXT("EnterVehicleBox"));
	EnterVehicleBox->SetupAttachment(GetMesh());
	EnterVehicleBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	EnterVehicleBox->SetGenerateOverlapEvents(true);

	LeftLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("LeftLight"));
	LeftLight->SetupAttachment(GetMesh(), TEXT("lf_light"));

	RightLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("RightLight"));
	RightLight->SetupAttachment(GetMesh(), TEXT("rt_light"));

	Smoke = CreateDefaultSubobject<USceneComponent>(TEXT("Smoke"));
	Smoke->SetupAttachment(GetMesh());

	WheelVFX_L1 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("WheelVFX_L1"));
	WheelVFX_L1->SetupAttachment(Smoke);

	WheelVFX_L2 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("WheelVFX_L2"));
	WheelVFX_L2->SetupAttachment(Smoke);

	WheelVFX_L3 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("WheelVFX_L3"));
	WheelVFX_L3->SetupAttachment(Smoke);

	WheelVFX_L4 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("WheelVFX_L4"));
	WheelVFX_L4->SetupAttachment(Smoke);

	WheelVFX_L5 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("WheelVFX_L5"));
	WheelVFX_L5->SetupAttachment(Smoke);

	WheelVFX_R1 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("WheelVFX_R1"));
	WheelVFX_R1->SetupAttachment(Smoke);

	WheelVFX_R2 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("WheelVFX_R2"));
	WheelVFX_R2->SetupAttachment(Smoke);

	WheelVFX_R3 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("WheelVFX_R3"));
	WheelVFX_R3->SetupAttachment(Smoke);

	WheelVFX_R4 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("WheelVFX_R4"));
	WheelVFX_R4->SetupAttachment(Smoke);

	WheelVFX_R5 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("WheelVFX_R5"));
	WheelVFX_R5->SetupAttachment(Smoke);

	GunFire = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("GunFire"));
	GunFire->SetupAttachment(GetMesh());

	GunBarrelEnd = CreateDefaultSubobject<USceneComponent>(TEXT("GunBarrelEnd"));
	GunBarrelEnd->SetupAttachment(GetMesh(), TEXT("gun_1_jntSocket"));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetMesh());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	ShootTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("ShootTimeline"));
	LightsTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("LightsTimeline"));
	HatchTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("HatchTimeline"));

	UChaosWheeledVehicleMovementComponent* VehicleMovement = Cast<UChaosWheeledVehicleMovementComponent>(GetVehicleMovementComponent());

	FChaosWheelSetup RtWheel08;
	RtWheel08.WheelClass = UTankWheel::StaticClass();
	RtWheel08.BoneName = FName("rt_wheel_08_jnt");
	VehicleMovement->WheelSetups.Add(RtWheel08);

	FChaosWheelSetup RtWheel07;
	RtWheel07.WheelClass = UTankWheel::StaticClass();
	RtWheel07.BoneName = FName("rt_wheel_07_jnt");
	VehicleMovement->WheelSetups.Add(RtWheel07);

	FChaosWheelSetup RtWheel06;
	RtWheel06.WheelClass = UTankWheel::StaticClass();
	RtWheel06.BoneName = FName("rt_wheel_06_jnt");
	VehicleMovement->WheelSetups.Add(RtWheel06);

	FChaosWheelSetup RtWheel05;
	RtWheel05.WheelClass = UTankWheel::StaticClass();
	RtWheel05.BoneName = FName("rt_wheel_05_jnt");
	VehicleMovement->WheelSetups.Add(RtWheel05);

	FChaosWheelSetup RtWheel04;
	RtWheel04.WheelClass = UTankWheel::StaticClass();
	RtWheel04.BoneName = FName("rt_wheel_04_jnt");
	VehicleMovement->WheelSetups.Add(RtWheel04);

	FChaosWheelSetup RtWheel03;
	RtWheel03.WheelClass = UTankWheel::StaticClass();
	RtWheel03.BoneName = FName("rt_wheel_03_jnt");
	VehicleMovement->WheelSetups.Add(RtWheel03);

	FChaosWheelSetup RtWheel02;
	RtWheel02.WheelClass = UTankWheel::StaticClass();
	RtWheel02.BoneName = FName("rt_wheel_02_jnt");
	VehicleMovement->WheelSetups.Add(RtWheel02);

	FChaosWheelSetup LfWheel08;
	LfWheel08.WheelClass = UTankWheel::StaticClass();
	LfWheel08.BoneName = FName("lf_wheel_08_jnt");
	VehicleMovement->WheelSetups.Add(LfWheel08);

	FChaosWheelSetup LfWheel07;
	LfWheel07.WheelClass = UTankWheel::StaticClass();
	LfWheel07.BoneName = FName("lf_wheel_07_jnt");
	VehicleMovement->WheelSetups.Add(LfWheel07);

	FChaosWheelSetup LfWheel06;
	LfWheel06.WheelClass = UTankWheel::StaticClass();
	LfWheel06.BoneName = FName("lf_wheel_06_jnt");
	VehicleMovement->WheelSetups.Add(LfWheel06);

	FChaosWheelSetup LfWheel05;
	LfWheel05.WheelClass = UTankWheel::StaticClass();
	LfWheel05.BoneName = FName("lf_wheel_05_jnt");
	VehicleMovement->WheelSetups.Add(LfWheel05);

	FChaosWheelSetup LfWheel04;
	LfWheel04.WheelClass = UTankWheel::StaticClass();
	LfWheel04.BoneName = FName("lf_wheel_04_jnt");
	VehicleMovement->WheelSetups.Add(LfWheel04);

	FChaosWheelSetup LfWheel03;
	LfWheel03.WheelClass = UTankWheel::StaticClass();
	LfWheel03.BoneName = FName("lf_wheel_03_jnt");
	VehicleMovement->WheelSetups.Add(LfWheel03);

	FChaosWheelSetup LfWheel02;
	LfWheel02.WheelClass = UTankWheel::StaticClass();
	LfWheel02.BoneName = FName("lf_wheel_02_jnt");
	VehicleMovement->WheelSetups.Add(LfWheel02);

	VehicleMovement->EngineSetup.MaxTorque = 4000.f;
	VehicleMovement->EngineSetup.MaxRPM = 2500.f;
	VehicleMovement->EngineSetup.EngineIdleRPM = 2000.f;
	VehicleMovement->EngineSetup.EngineBrakeEffect = 1.f;
	VehicleMovement->EngineSetup.EngineRevUpMOI = 5.f;
	VehicleMovement->EngineSetup.EngineRevDownRate = 7995.f;

	VehicleMovement->Mass = 10000.f;
	VehicleMovement->DragCoefficient = 1.f;

	VehicleMovement->TorqueControl.Enabled = true;
	VehicleMovement->TorqueControl.YawTorqueScaling = 6.f;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	ShootTimelineFinished.BindUFunction(this, FName("OnShootTimelineFinished"));
	ShootTimeline->SetTimelineFinishedFunc(ShootTimelineFinished);
	ShootTimeline->SetTimelineLength(2.f);
	ShootTimeline->SetLooping(false);

	LightsTimelineFinished.BindUFunction(this, FName("OnLightsTimelineFinished"));
	LightsTimeline->SetTimelineFinishedFunc(LightsTimelineFinished);
	LightsTimeline->SetTimelineLength(0.1f);
	LightsTimeline->SetLooping(false);

	HatchTimelineUpdate.BindUFunction(this, FName("OnHatchTimelineUpdate"));
	HatchTimeline->AddInterpFloat(HatchTimelineCurve, HatchTimelineUpdate);
	HatchTimeline->SetTimelineLength(2.5f);
	HatchTimeline->SetLooping(false);
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	bStopTurn = GetMesh()->GetPhysicsAngularVelocityInDegrees().Size() > 30.f;
	
	TurretAngle = GetTurretAngle();
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATank::Look);

		EnhancedInputComponent->BindAction(ThrottleAction, ETriggerEvent::Triggered, this, &ATank::Throttle);
		EnhancedInputComponent->BindAction(ThrottleAction, ETriggerEvent::Completed, this, &ATank::Throttle);

		EnhancedInputComponent->BindAction(ThrottleAction, ETriggerEvent::Started, this, &ATank::Brake);
		EnhancedInputComponent->BindAction(ThrottleAction, ETriggerEvent::Canceled, this, &ATank::Brake);

		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ATank::TurnTriggered);
		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Started, this, &ATank::TurnStarted);
		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Canceled, this, &ATank::TurnFinished);
		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Completed, this, &ATank::TurnFinished);

		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &ATank::Shoot);

		EnhancedInputComponent->BindAction(HandbrakeAction, ETriggerEvent::Triggered, this, &ATank::HandbrakeStart);
		EnhancedInputComponent->BindAction(HandbrakeAction, ETriggerEvent::Started, this, &ATank::HandbrakeStart);
		EnhancedInputComponent->BindAction(HandbrakeAction, ETriggerEvent::Ongoing, this, &ATank::HandbrakeStart);
		EnhancedInputComponent->BindAction(HandbrakeAction, ETriggerEvent::Canceled, this, &ATank::HandbrakeStop);
		EnhancedInputComponent->BindAction(HandbrakeAction, ETriggerEvent::Completed, this, &ATank::HandbrakeStop);

		EnhancedInputComponent->BindAction(LightsAction, ETriggerEvent::Triggered, this, &ATank::ToggleLights);
		EnhancedInputComponent->BindAction(ExitVehicleAction, ETriggerEvent::Triggered, this, &ATank::ExitVehicle);
	}
}

double ATank::GetTurretAngle() const
{
	FVector NormalizedForwardVector = Camera->GetForwardVector();
	
	NormalizedForwardVector.Z = 0;
	NormalizedForwardVector.Normalize(0.0001f);
	//
	// float AngleOfTurretRotationComparedToCamera = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), NormalizedForwardVector));
	// float TurretOnRightOfCameraForward = FVector::DotProduct(NormalizedForwardVector, GetActorRightVector());
	//
	// float Yaw = TurretOnRightOfCameraForward > 0 ? AngleOfTurretRotationComparedToCamera : AngleOfTurretRotationComparedToCamera - 360;
	// Yaw = Yaw - GetActorRotation().Yaw;
	//
	// FRotator Current = FRotator(0, TurretAngle, 0);
	// FRotator Target = FRotator(0, Yaw, 0);
	//
	// FRotator Rotation = FMath::RInterpTo(Current, Target, GetWorld()->GetDeltaSeconds(), TurretInterpSpeed);
	//
	// return Rotation.Yaw;
	
	return TurretAngle;
}

void ATank::GunElevation()
{
	FVector ForwardVector = Camera->GetForwardVector();
	FVector ComponentLocation = Camera->GetComponentLocation();

	GunLocation = ForwardVector * 7000.f + ComponentLocation;

	FHitResult HitResult;

	bool bIsHit = UKismetSystemLibrary::LineTraceSingleForObjects(
		GetWorld(),
		ComponentLocation,
		GunLocation,
		GunFireCollisionObjectTypes,
		false,
		TArray<AActor*>(),
		EDrawDebugTrace::None,
		HitResult,
		true);

	FVector StartLookAtVector = GetMesh()->GetSocketLocation(GunSocketName);
	FVector EndLookAtVector = bIsHit ? HitResult.Location : GunLocation;

	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(StartLookAtVector, EndLookAtVector);
	FMath::Clamp(LookAtRotation.Pitch, -3.f, 20.f);

	GunAngle = FMath::FInterpTo(GunAngle, LookAtRotation.Pitch, GetWorld()->GetDeltaSeconds(), 2.f);
}

void ATank::GunSightScreen()
{
	FVector LineTraceStart = GetMesh()->GetSocketLocation(GunSocketName);
	FVector LineTraceEnd = GetMesh()->GetSocketLocation(GunSocketName);

	FRotator GunBarrelRotation = GetMesh()->GetSocketRotation(GunSocketName);
	LineTraceEnd.X = GunBarrelRotation.Vector().X * GunShootDistance;
	
	FHitResult OutHit;

	FCollisionObjectQueryParams ObjectQueryParams;

	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_Destructible);
	
	GetWorld()->LineTraceSingleByObjectType(OutHit, LineTraceStart, LineTraceEnd, ObjectQueryParams);
}

bool ATank::VehicleFlip() const
{
	return FVector::DotProduct(GetMesh()->GetUpVector(), FVector::UpVector) > 0.f;
}

void ATank::EnterVehicle_Implementation()
{
	APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	CameraManager->ViewPitchMin = -60.f;
	CameraManager->ViewPitchMax = 15.f;

	if (GunSightWidget)
	{
		GunSightWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), GunSightWidget);

		if (GunSightWidgetInstance)
		{
			GunSightWidgetInstance->AddToViewport();
		}
	}

	GetVehicleMovementComponent()->SetHandbrakeInput(false);
}

void ATank::OnShootTimelineFinished()
{
	bShoot = true;
}

void ATank::OnLightsTimelineFinished()
{
	bAllowLightChange = true;
}

void ATank::OnHatchTimelineUpdate(float TimelineAlpha)
{
	HatchAngle = FMath::Lerp(135.f, 0.f, TimelineAlpha);
}

void ATank::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void ATank::Throttle(const FInputActionValue& Value)
{
	if (UChaosVehicleMovementComponent* VehicleMovement = GetVehicleMovementComponent())
	{
		FVector2D Throttle = Value.Get<FVector2D>();

		if (Throttle.Y >= 0.0f)
		{
			VehicleMovement->SetThrottleInput(Throttle.Y);
			VehicleMovement->SetBrakeInput(0);
		}
		else
		{
			VehicleMovement->SetThrottleInput(Throttle.Y);
			VehicleMovement->SetBrakeInput(-Throttle.Y);
		}
	}
}

void ATank::Brake()
{
	if (UChaosVehicleMovementComponent* VehicleMovement = GetVehicleMovementComponent())
	{
		VehicleMovement->SetYawInput(0);
		VehicleMovement->SetBrakeInput(0);
	}
}

void ATank::TurnTriggered(const FInputActionValue& Value)
{
	float TurnValue = Value.Get<float>();

	float WheelSmokeIntensity = FMath::Abs(TurnValue);

	WheelVFX_L1->SetActive(WheelSmokeIntensity > 0.1f);
	WheelVFX_L2->SetActive(WheelSmokeIntensity > 0.1f);
	WheelVFX_L3->SetActive(WheelSmokeIntensity > 0.1f);
	WheelVFX_L4->SetActive(WheelSmokeIntensity > 0.1f);
	WheelVFX_L5->SetActive(WheelSmokeIntensity > 0.1f);

	WheelVFX_R1->SetActive(WheelSmokeIntensity > 0.1f);
	WheelVFX_R2->SetActive(WheelSmokeIntensity > 0.1f);
	WheelVFX_R3->SetActive(WheelSmokeIntensity > 0.1f);
	WheelVFX_R4->SetActive(WheelSmokeIntensity > 0.1f);
	WheelVFX_R5->SetActive(WheelSmokeIntensity > 0.1f);

	if (UChaosVehicleMovementComponent* VehicleMovement = GetVehicleMovementComponent())
	{
		if (bStopTurn)
		{
			VehicleMovement->SetYawInput(0);
		}
		else
		{
			VehicleMovement->SetYawInput(TurnValue);
		}
	}
}

void ATank::TurnStarted()
{
	if (UChaosVehicleMovementComponent* VehicleMovement = GetVehicleMovementComponent())
	{
		VehicleMovement->SetThrottleInput(0.1f);
	}
}

void ATank::TurnFinished()
{
	if (UChaosVehicleMovementComponent* VehicleMovement = GetVehicleMovementComponent())
	{
		VehicleMovement->SetYawInput(0);
		VehicleMovement->SetThrottleInput(0);

		WheelVFX_L1->SetActive(false);
		WheelVFX_L2->SetActive(false);
		WheelVFX_L3->SetActive(false);
		WheelVFX_L4->SetActive(false);
		WheelVFX_L5->SetActive(false);

		WheelVFX_R1->SetActive(false);
		WheelVFX_R2->SetActive(false);
		WheelVFX_R3->SetActive(false);
		WheelVFX_R4->SetActive(false);
		WheelVFX_R5->SetActive(false);
	}
}

void ATank::Shoot()
{
	if (bShoot)
	{
		GunFire->Activate();

		// Maybe debug draw where tank ammo is
		// Check whether socket is being referenced properly
		// Breakpoint in BeginPlay for TankAmmo
		GetWorld()->SpawnActor<ATankAmmo>(ATankAmmo::StaticClass(), GunBarrelEnd->GetComponentTransform());

		bShoot = false;

		ShootTimeline->PlayFromStart();
	}
}

void ATank::HandbrakeStart()
{
	if (UChaosVehicleMovementComponent* VehicleMovement = GetVehicleMovementComponent())
	{
		VehicleMovement->SetHandbrakeInput(true);
	}
}

void ATank::HandbrakeStop()
{
	if (UChaosVehicleMovementComponent* VehicleMovement = GetVehicleMovementComponent())
	{
		VehicleMovement->SetHandbrakeInput(false);
	}
}

void ATank::ToggleLights()
{
	if (bAllowLightChange)
	{
		bAllowLightChange = false;
		bLightsOn = !bLightsOn;

		RightLight->SetVisibility(bLightsOn);
		LeftLight->SetVisibility(bLightsOn);

		LightsTimeline->PlayFromStart();
	}
}

void ATank::ExitVehicle()
{
	if (UChaosVehicleMovementComponent* VehicleMovement = GetVehicleMovementComponent())
	{
		VehicleMovement->SetThrottleInput(0);
		VehicleMovement->SetHandbrakeInput(true);
		VehicleMovement->SetYawInput(0);
		VehicleMovement->SetRequiresControllerForInputs(false);

		FVector3d ExitLocation = ExitSpawnPoint->GetComponentLocation() + FVector(0.f, 0.f, 100.f);

		ACharacter* MainCharacter = GetWorld()->SpawnActor<AMainCharacter>();
		MainCharacter->SetActorLocation(ExitLocation);

		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

		PlayerController->Possess(MainCharacter);

		UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
	}
}
