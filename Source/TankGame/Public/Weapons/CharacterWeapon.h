// Copyright (c) Sawnoff Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CharacterWeapon.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCharacterWeapon : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface class representing the behavior of a character weapon in the game.
 * Classes implementing this interface define the behavior for weapon-related functionality such as firing.
 */
class TANKGAME_API ICharacterWeapon
{
	GENERATED_BODY()

public:
	TWeakObjectPtr<UStaticMeshComponent> WeaponMesh;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CharacterWeapon")
	void Fire();
};
