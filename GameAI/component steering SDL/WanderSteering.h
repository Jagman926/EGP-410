#include <Trackable.h>
#include "Steering.h"

class FaceSteering;

class WanderSteering : public Steering
{
public:
	WanderSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID);
	//
	virtual Steering* getSteering();
	//
	void setWanderRadius(float radius) { wanderRadius = radius; };
	void setWanderOffset(float radius) { wanderOffset = radius; };
	void setWanderRate(float time) { wanderRate = time; };
	float getWanderRadius() { return wanderRadius; };
	float getWanderOffset() { return wanderOffset; };
	float getWanderRate() { return wanderRate; };

private:
	const float PI = 3.1415926;
	float wanderOffset = 90.0f;
	float wanderRadius = 70.0f;
	float wanderRate = 2 * PI;

	FaceSteering* mpFaceSteering;
};
