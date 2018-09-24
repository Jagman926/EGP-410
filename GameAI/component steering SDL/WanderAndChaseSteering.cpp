#include <cassert>

#include "Steering.h"
#include "WanderAndChaseSteering.h"
#include "WanderSteering.h"
#include "SeekSteering.h" 
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"

WanderAndChaseSteering::WanderAndChaseSteering(const UnitID & ownerID, const Vector2D & targetLoc, const UnitID & targetID, bool shouldFlee)
{
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
	mType = Steering::WANDER_CHASE;
}

Steering * WanderAndChaseSteering::getSteering()
{
	return nullptr;
}
