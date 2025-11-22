// Copyright (c) Sawnoff Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.generated.h"

UCLASS()
class TANKGAME_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	virtual void Fire() PURE_VIRTUAL();
};
