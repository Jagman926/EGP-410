#include <Trackable.h>
#include "Steering.h"

class SeekSteering;
class WanderSteering;
class FaceSteering;

class WanderAndChaseSteering : public Steering
{
public:
	WanderAndChaseSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);
	//
	void setSeekRadius(float seekRadius) { mSeekRadius = seekRadius; };

protected:
	Steering* mpSteeringData;
	SeekSteering* mpSeekSteering;
	WanderSteering* mpWanderSteering;
	FaceSteering* mpFaceSteering;
	//
	virtual Steering* getSteering();
	float getSeekRadius() { return mSeekRadius; };

private:
	float mSeekRadius = 300;
};
