#pragma once

#include <Trackable.h>
#include "Steering.h"

class CohesionSteering : public Steering
{
public:
	CohesionSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID);
	//
	virtual Steering* getSteering();
	//
	void setCohesionRadius(float radius) { mCohesionRadius = radius; };

protected:
	float getCohesionRadius() { return mCohesionRadius; };

private:
	float mCohesionRadius = 125.0f;
};
