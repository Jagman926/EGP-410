#pragma once

#include <Trackable.h>
#include "Steering.h"

class FaceSteering;

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
	FaceSteering* mpFaceSteering;
	//
	float getAlignmentRadius() { return mAlignmentRadius; };
	float getTimeToAlign() { return mTimeToAlign; };

private:
	float mAlignmentRadius = 60.0f;
	float mTimeToAlign = 0.1f;
};
