// Copyright (c) Sawnoff Games. All rights reserved.


#include "Tank/TankWheel.h"

UTankWheel::UTankWheel()
{
	WheelWidth = 40.f;
	WheelMass = 500.f;
	SlipThreshold = 1000.f;
	SkidThreshold = 1000.f;
	bAffectedByHandbrake = true;
	bAffectedByEngine = true;
	bABSEnabled = true;
	SuspensionMaxRaise = 5.f;
	SuspensionMaxDrop = 5.f;
	SpringRate = 5000.f;
	SuspensionSmoothing = 1.f;
}