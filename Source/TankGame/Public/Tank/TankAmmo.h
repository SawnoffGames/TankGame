// Copyright (c) Sawnoff Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TankAmmo.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class AFieldSystemActor;

/**
 * @class ATankAmmo
 * @brief Represents the ammunition used by the tank within the game.
 *
 * Inherits from AActor and encapsulates all necessary components and logic for tank ammunition functionality.
 * Includes collision detection, movement, and destruction effects upon impact.
 */
UCLASS()
class TANKGAME_API ATankAmmo : public AActor
{
	GENERATED_BODY()
	
public:	
	ATankAmmo();
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Default")
	TObjectPtr<USphereComponent> CollisionComponent;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Default")
	TObjectPtr<UStaticMeshComponent> Ammo;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Default")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(BlueprintreadOnly, VisibleAnywhere, Category="Default")
	TObjectPtr<UParticleSystem> ExplosionParticleSystem;

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
