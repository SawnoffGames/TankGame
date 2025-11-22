// Copyright (c) Sawnoff Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "ChaosVehicleWheel.h"
#include "TankWheel.generated.h"

/**
 * @class UTankWheel
 * @brief Represents a custom vehicle wheel specifically designed for tank vehicles.
 *
 * The UTankWheel is a specialized class derived from the UChaosVehicleWheel base class.
 * It is intended to provide functionality- and configuration-specific to tank vehicle wheels
 * within the Chaos Physics Vehicle framework.
 */
UCLASS()
class TANKGAME_API UTankWheel : public UChaosVehicleWheel
{
	GENERATED_BODY()
	
public:
	UTankWheel();
};
