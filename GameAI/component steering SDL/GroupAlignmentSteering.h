#pragma once

#include <Trackable.h>
#include "Steering.h"

class GroupAlignmentSteering : public Steering
{
public:
	GroupAlignmentSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);
	//
	virtual Steering* getSteering();
};
