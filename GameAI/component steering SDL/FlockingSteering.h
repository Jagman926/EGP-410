#pragma once

#include <Trackable.h>
#include "Steering.h"

class FlockingSteering : public Steering
{
public:
	FlockingSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);
	//
	virtual Steering* getSteering();
};
