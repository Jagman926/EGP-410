#pragma once

#include <Trackable.h>
#include "Steering.h"

class SeparationSteering;
class CohesionSteering;
class GroupAlignmentSteering;
class FaceSteering;

class FlockingSteering : public Steering
{
public:
	FlockingSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID);
	//
	virtual Steering* getSteering();
	//
	float getSeparationWeight() { return gpGame->getSeparationWeight(); };
	float getCohesionWeight() { return gpGame->getCohesionWeight(); };
	float getAlignmentWeight() { return gpGame->getAlignmentWeight(); };

protected:
	SeparationSteering* mpSeparationSteering;
	CohesionSteering* mpCohesionSteering;
	GroupAlignmentSteering* mpGroupAlignmentSteering;
	FaceSteering* mpFaceSteering;

private:
	//Wander
	const float PI = 3.1415926f;
	float mWanderOffset = 130.0f;
	float mWanderRadius = 90.0f;
	float mWanderRate = 2.0f * PI;
};
