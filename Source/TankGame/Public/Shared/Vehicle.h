// Copyright (c) Sawnoff Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Vehicle.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UVehicle : public UInterface
{
	GENERATED_BODY()
};

/**
 * @brief Interface class that defines vehicle-related actions.
 *
 * The IVehicle interface is intended to provide basic functionality for any class
 * implementing vehicle operations such as entering and exiting the vehicle.
 * This interface serves as a common blueprint for vehicle behavior in a game environment.
 */
class TANKGAME_API IVehicle
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Vehicle")
	void EnterVehicle();
};
