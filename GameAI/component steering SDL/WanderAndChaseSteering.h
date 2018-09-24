#include <Trackable.h>
#include "Steering.h"

class SeekSteering;
class WanderSteering;
class FaceSteering;

class WanderAndChaseSteering : public Steering
{
public:
	WanderAndChaseSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);

protected:
	Steering* mpSteeringData;
	SeekSteering* mpSeekSteering;
	WanderSteering* mpWanderSteering;
	FaceSteering* mpFaceSteering;
	//
	virtual Steering* getSteering();
	//
	const float mSEEK_RADIUS = 300;
};
