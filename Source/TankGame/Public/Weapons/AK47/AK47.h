// Copyright (c) Sawnoff Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapons/CharacterWeapon.h"
#include "AK47.generated.h"

UCLASS()
class TANKGAME_API AAK47 : public AActor, public ICharacterWeapon
{
	GENERATED_BODY()
	
public:	
	AAK47();
};
