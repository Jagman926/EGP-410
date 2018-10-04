#pragma once

#include <Trackable.h>
#include "Steering.h"

class GroupAlignmentSteering : public Steering
{
public:
	GroupAlignmentSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID);
	//
	virtual Steering* getSteering();
	//
	void setAlignmentRadius(float radius) { mAlignmentRadius = radius; };
	void setTimeToAlign(float time) { mTimeToAlign = time; };

protected:
	float getAlignmentRadius() { return mAlignmentRadius; };
	float getTimeToAlign() { return mTimeToAlign; };

private:
	float mAlignmentRadius;
	float mTimeToAlign;
};
