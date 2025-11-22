// Copyright (c) Sawnoff Games. All rights reserved.


#include "Weapons/AK47/AK47.h"

AAK47::AAK47()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAK47::Fire()
{
	constexpr float kLineTraceDistance = 10000.f;

	FVector CameraLocation = GetActorLocation();
	FRotator CameraRotation = GetActorRotation();
	
	FVector Start = CameraLocation;
	FVector End = Start + (CameraRotation.Vector() * kLineTraceDistance);

	FCollisionQueryParams TraceParams(FName(TEXT("InteractTrace")), true, nullptr);
	TraceParams.bTraceComplex = false;

	FHitResult HitDetails = FHitResult(ForceInit);

	bool bIsHit = GetWorld()->LineTraceSingleByChannel(
		HitDetails,		// FHitResult object that will be populated with hit info
		Start,			// Starting position
		End,			// End position
		ECC_Camera,		// Camera channel
		TraceParams);	// Additional trace settings

	if (bIsHit)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("We hit something"));

		DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 5.f, ECC_WorldStatic, 1.f);

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Hit Actor Name: %s"), *HitDetails.GetActor()->GetName()));
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Distance: %s"), *FString::SanitizeFloat(HitDetails.Distance)));

		DrawDebugBox(GetWorld(), HitDetails.ImpactPoint, FVector(2.f, 2.f, 2.f), FColor::Blue, false, 5.f, ECC_WorldStatic, 1.f);

		// UGameplayStatics::ApplyDamage(HitDetails.GetActor(),	// Damaged Actor
		// 							  100,												// Damage
		// 							  GetController(),									// Instigator (Controller)
		// 							  this,												// Damage Causer (Actor)
		// 							  UDamageType::StaticClass());						// Default damage type
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Nothing was hit"));

		DrawDebugLine(GetWorld(), Start, End, FColor::Purple, false, 5.f, ECC_WorldStatic, 1.f);
	}
}

