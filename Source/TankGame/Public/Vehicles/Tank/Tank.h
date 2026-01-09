// Copyright (c) Sawnoff Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "Components/TimelineComponent.h"
#include "Core/Vehicles/Vehicle.h"
#include "Tank.generated.h"

struct FInputActionValue;
class UInputAction;
class UBoxComponent;
class USpringArmComponent;
class UCameraComponent;
class USpotLightComponent;
class UUserWidget;

/**
 * @brief Represents a tank vehicle, inheriting from AWheeledVehiclePawn and implementing the IVehicle interface.
 *        This class includes properties for tank functionalities, visual effects, controls, and gameplay-related components.
 */
UCLASS(Blueprintable, BlueprintType)
class ATank : public AWheeledVehiclePawn, public IVehicle
{
	GENERATED_BODY()

public:
	ATank();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Default")
	TSubclassOf<UUserWidget> GunSightWidget;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Default")
	TObjectPtr<USceneComponent> ExitSpawnPoint;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Default")
	TObjectPtr<UBoxComponent> EnterVehicleBox;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Default")
	TObjectPtr<USpotLightComponent> LeftLight;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Default")
	TObjectPtr<USpotLightComponent> RightLight;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Default")
	TObjectPtr<USceneComponent> Smoke;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Default")
	TObjectPtr<UParticleSystemComponent> WheelVFX_L1;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Default")
	TObjectPtr<UParticleSystemComponent> WheelVFX_L2;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Default")
	TObjectPtr<UParticleSystemComponent> WheelVFX_L3;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Default")
	TObjectPtr<UParticleSystemComponent> WheelVFX_L4;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Default")
	TObjectPtr<UParticleSystemComponent> WheelVFX_L5;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Default")
	TObjectPtr<UParticleSystemComponent> WheelVFX_R1;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Default")
	TObjectPtr<UParticleSystemComponent> WheelVFX_R2;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Default")
	TObjectPtr<UParticleSystemComponent> WheelVFX_R3;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Default")
	TObjectPtr<UParticleSystemComponent> WheelVFX_R4;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Default")
	TObjectPtr<UParticleSystemComponent> WheelVFX_R5;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Default")
	TObjectPtr<UParticleSystemComponent> GunFire;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Default")
	TObjectPtr<USceneComponent> GunBarrelEnd;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Default")
	TObjectPtr<USpringArmComponent> SpringArm;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Default")
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Default")
	TObjectPtr<UTimelineComponent> ShootTimeline;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Default")
	TObjectPtr<UTimelineComponent> LightsTimeline;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Default")
	TObjectPtr<UTimelineComponent> HatchTimeline;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Default")
	TObjectPtr<UCurveFloat> HatchTimelineCurve;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Default")
	TArray<TEnumAsByte<EObjectTypeQuery>> GunFireCollisionObjectTypes;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Default")
	float TurretInterpSpeed = 12.f;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Default")
	float TurretAngle;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Default")
	float HatchAngle;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Default")
	float GunAngle;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Default")
	float GunShootDistance = 7000.f;

protected:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ThrottleAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> TurnAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ShootAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> HandbrakeAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LightsAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ExitVehicleAction;
	
public:
	UFUNCTION(BlueprintPure)
	double GetTurretAngle() const;
	
	UFUNCTION(BlueprintCallable)
	void GunElevation();
	
	UFUNCTION(BlueprintCallable)
	void GunSightScreen();
	
	UFUNCTION(BlueprintPure)
	bool VehicleFlip() const;
	
	UFUNCTION(BlueprintCallable)
	virtual void EnterVehicle_Implementation() override;

	UFUNCTION()
	void OnShootTimelineFinished();

	UFUNCTION()
	void OnLightsTimelineFinished();

	UFUNCTION()
	void OnHatchTimelineUpdate(float TimelineAlpha);

private:
	FVector GunLocation;
	FName GunSocketName = FName("gun_jnt");
	
	UPROPERTY()
	UUserWidget* GunSightWidgetInstance;
	
	bool bStopTurn = false;
	bool bShoot = true;
	bool bLightsOn = false;
	bool bAllowLightChange = true;
	
	FOnTimelineEventStatic ShootTimelineFinished;
	FOnTimelineEventStatic LightsTimelineFinished;
	FOnTimelineFloat HatchTimelineUpdate;

	UFUNCTION()
	void Look(const FInputActionValue& Value);
	
	UFUNCTION()
	void Throttle(const FInputActionValue& Value);

	UFUNCTION()
	void Brake();

	UFUNCTION()
	void TurnTriggered(const FInputActionValue& Value);

	UFUNCTION()
	void TurnStarted();

	UFUNCTION()
	void TurnFinished();

	UFUNCTION()
	void Shoot();

	UFUNCTION()
	void HandbrakeStart();

	UFUNCTION()
	void HandbrakeStop();

	UFUNCTION()
	void ToggleLights();

	UFUNCTION()
	void ExitVehicle();
};
