#include <cassert>

#include "ArriveAndFace.h"
#include "ArriveSteering.h"
#include "FaceSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"

ArriveAndFaceSteering::ArriveAndFaceSteering(const UnitID & ownerID, const Vector2D & targetLoc, const UnitID & targetID)
{
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
	mType = Steering::ARRIVE_FACE;
}

Steering * ArriveAndFaceSteering::getSteering()
{
	return nullptr;
}
