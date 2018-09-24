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
	void setWanderRadius(float radius) { mWanderRadius = radius; };
	void setWanderOffset(float radius) { mWanderOffset = radius; };
	void setWanderRate(float time) { mWanderRate = time; };

protected:
	FaceSteering* mpFaceSteering;
	//
	float getWanderRadius() { return mWanderRadius; };
	float getWanderOffset() { return mWanderOffset; };
	float getWanderRate() { return mWanderRate; };

private:
	const float PI = 3.1415926f;
	float mWanderOffset = 130.0f;
	float mWanderRadius = 90.0f;
	float mWanderRate = 2.0f * PI;
};
