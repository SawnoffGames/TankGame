// Copyright (c) 2025 Sawnoff Games. All rights reserved.


#include "Tank/TankAmmo.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ATankAmmo::ATankAmmo()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));

	Ammo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ammo"));
	Ammo->SetupAttachment(CollisionComponent);
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->ProjectileGravityScale = 0;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	
	ProjectileMovement->Velocity.X = 3000.f;
	ProjectileMovement->Velocity.Y = 0;
	ProjectileMovement->Velocity.Z = 0;
}

void ATankAmmo::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != nullptr && OtherActor != this && OtherComp != nullptr && OtherComp->IsSimulatingPhysics())
	{
		FVector Impulse = GetVelocity() * 100;
		FVector Location = GetActorLocation();

		HitComponent->AddImpulseAtLocation(Impulse, Location);
	}

	FVector ImpactPoint = Hit.ImpactPoint;
	UParticleSystem* ParticleSystem = ExplosionParticleSystem.Get();
	
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystem, ImpactPoint, FRotator::ZeroRotator, FVector(2, 2, 2));

	Destroy();
}
