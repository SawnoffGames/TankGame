// Copyright (c) Sawnoff Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UBoxComponent;
class UTimelineComponent;

UCLASS()
class TANKGAME_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMainCharacter();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animations, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> AttackMontage;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> AttackCapsule;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTimelineComponent> CameraZoomTimeline;

	UPROPERTY(EditAnywhere, Category = Camera)
	TObjectPtr<UCurveFloat> CameraZoomCurve;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float AimFOV = 45;

	float StartFOV;
	float DesiredFOV;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float MinZoomLevel = 120;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float MaxZoomLevel = 300;
	
	float ZoomValue;

protected:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

public:
	
	void Aim(bool aim);
	void Attack();
	void ActivateAttack(bool activate) const;
	bool IsAttacking() const;

	void ZoomCamera(float ZoomValue);
	
	bool bIsAiming = false;
	bool bIsZoomFinished = true;
	
	UFUNCTION()
	void OnComponentBeginOverlap_AttackCapsule(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnComponentBeginOverlap_CapsuleComponent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnComponentEndOverlap_CapsuleComponent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UFUNCTION()
	void OnCameraZoomTimelineUpdate(float TimelineAlpha);

	UFUNCTION()
	void OnCameraZoomTimelineFinished();
	
private:
	void PerformLineTraceAndApplyDamage();
	void PlayMeleeAttackAnimation();

	FOnTimelineFloat CameraZoomTimelineUpdate;
	FOnTimelineEventStatic CameraZoomTimelineFinished;
};