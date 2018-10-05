#pragma once

#include <Trackable.h>
#include "Steering.h"

class WanderSteering;
class SeparationSteering;
class CohesionSteering;
class GroupAlignmentSteering;

class FlockingSteering : public Steering
{
public:
	FlockingSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID);
	//
	virtual Steering* getSteering();
	//
	void setSeparationWeight(float weight) { mSeparationWeight = weight; };
	void setCohesionWeight(float weight) { mCohesionWeight = weight; };
	void setAlignmentWeight(float weight) { mAlignmentWeight = weight; };

protected:
	WanderSteering* mpWanderSteering;
	SeparationSteering* mpSeparationSteering;
	CohesionSteering* mpCohesionSteering;
	GroupAlignmentSteering* mpGroupAlignmentSteering;
	//
	float getSeparationWeight() { return mSeparationWeight; };
	float getCohesionWeight() { return mCohesionWeight; };
	float getAlignmentWeight() { return mAlignmentWeight; };

private:
	float mSeparationWeight;
	float mCohesionWeight;
	float mAlignmentWeight;
};
