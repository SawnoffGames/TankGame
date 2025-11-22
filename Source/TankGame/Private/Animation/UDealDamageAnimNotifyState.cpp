// Copyright (c) Sawnoff Games. All rights reserved.


#include "Animation/UDealDamageAnimNotifyState.h"

#include "Character/MainCharacter.h"

void UDealDamageAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Yellow, TEXT("DealDamageAnimNotifyState: NotifyBegin"));

	if (AMainCharacter* Character = Cast<AMainCharacter>(MeshComp->GetOwner()))
	{
		Character->ActivateAttack(true);
	}
}

void UDealDamageAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	FVector StartTraceLocation = MeshComp->GetSocketLocation(TEXT("RightHandSocket"));
	FVector EndTraceLocation = MeshComp->GetSocketLocation(TEXT("RightHandSocket"));
	float Radius = 10;
	bool bComplexTrace = false;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(MeshComp->GetOwner());
	bool bIgnoreSelf = true;
	FLinearColor TraceColor = FLinearColor::Red;
	FLinearColor TraceHitColor = FLinearColor::Green;
	float DrawTime = 10;

	TArray<FHitResult> HitArray;

	// const bool Hit = UKismetSystemLibrary::SphereTraceMulti(MeshComp, StartTraceLocation, EndTraceLocation, Radius,
	// 	UEngineTypes::ConvertToTraceType(ECC_Camera), bComplexTrace, ActorsToIgnore, EDrawDebugTrace::ForDuration,
	// 	HitArray, bIgnoreSelf, TraceColor, TraceHitColor, DrawTime);
	//
	// if (Hit)
	// {
	// 	for (const FHitResult HitResult : HitArray)
	// 	{
	// 		UGameplayStatics::ApplyDamage(HitResult.GetActor(),
	// 			20,													// Damage
	// 			Cast<APawn>(MeshComp->GetOwner())->GetController(),	// Instigator
	// 			MeshComp->GetOwner(),								// Damage Causer (Actor)
	// 			UDamageType::StaticClass());						// Default damage type
	// 	}
	// }
}

void UDealDamageAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Yellow, TEXT("DealDamageAnimNotifyState: NotifyEnd"));

	if (AMainCharacter* Character = Cast<AMainCharacter>(MeshComp->GetOwner()))
	{
		Character->ActivateAttack(false);
	}
}
