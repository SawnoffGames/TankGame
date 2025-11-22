// Copyright (c) Sawnoff Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapons/Weapon.h"
#include "AK47.generated.h"

UCLASS()
class TANKGAME_API AAK47 : public AWeapon
{
	GENERATED_BODY()
	
public:	
	AAK47();
	
	virtual void Fire() override;
};
