#include <Trackable.h>
#include "Steering.h"

class WanderSteering : public Steering
{
public:
	WanderSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID);

protected:
	virtual Steering* getSteering();
	//
	void setWanderRadius(float radius) { wanderRadius = radius; };
	void setWanderOffset(float radius) { wanderOffset = radius; };
	void setWanderRate(float time) { wanderRate = time; };
	float getWanderRadius() { return wanderRadius; };
	float getWanderOffset() { return wanderOffset; };
	float getWanderRate() { return wanderRate; };

private:
	float wanderOffset = 20.0f;
	float wanderRadius = 400.0f;
	float wanderRate = 0.1f;
};
