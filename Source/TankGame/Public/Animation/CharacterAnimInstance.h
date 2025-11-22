// Copyright (c) Sawnoff Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimInstance.generated.h"

class AMainCharacter;
/**
 * AnimInstance subclass for controlling animation properties of the MainCharacter.
 */
UCLASS()
class TANKGAME_API UCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = AnimationProperties)
	void UpdateAnimationProperties(float DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float Direction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	bool bIsInAir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	bool bIsAiming;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	bool bIsCrouching;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float AimPitch;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float AimYaw;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	TObjectPtr<AMainCharacter> MainCharacter;
};
