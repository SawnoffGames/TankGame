// Copyright (c) Sawnoff Games. All rights reserved.


#include "Core/Animation/CharacterAnimInstance.h"


#include "KismetAnimationLibrary.h"
#include "Characters/MainCharacter/MainCharacter.h"
#include "GameFramework/PawnMovementComponent.h"

void UCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (MainCharacter == nullptr)
	{
		MainCharacter = Cast<AMainCharacter>(TryGetPawnOwner());
	}
}

void UCharacterAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (MainCharacter == nullptr)
	{
		MainCharacter = Cast<AMainCharacter>(TryGetPawnOwner());
	}

	if (MainCharacter)
	{
		FVector Speed = MainCharacter->GetVelocity();
		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0);

		MovementSpeed = LateralSpeed.Size();
		
		bIsInAir = MainCharacter->GetMovementComponent()->IsFalling();
		
		Direction = UKismetAnimationLibrary::CalculateDirection(Speed, MainCharacter->GetActorRotation());

		bIsAiming = MainCharacter->bIsAiming;
		bIsCrouching = MainCharacter->IsCrouched();

		FRotator PawnRotation = MainCharacter->GetActorRotation();
		FRotator ControllerRotation = MainCharacter->GetControlRotation();
		FRotator DeltaRotation = ControllerRotation - PawnRotation;

		FRotator Interp = FMath::RInterpTo(FRotator(AimPitch, AimYaw, 0), DeltaRotation, DeltaTime, 15.0f);
		AimPitch = FMath::ClampAngle(Interp.Pitch, -90, 90);
		AimYaw = FMath::ClampAngle(Interp.Yaw, -90, 90);
	}
}
