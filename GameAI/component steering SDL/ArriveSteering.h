#include <Trackable.h>
#include "Steering.h"

class ArriveSteering : public Steering
{
public:
	ArriveSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID);
	//
	virtual Steering* getSteering();
	//
	void setArriveRadius(float radius) { mArriveRadius = radius; };
	void setSlowRadius(float radius) { mSlowRadius = radius; };
	void setTimeToTarget(float time) { mTimeToTarget = time; };

protected:
	float getArriveRadius() { return mArriveRadius; };
	float getSlowRadius() { return mSlowRadius; };
	float getTimeToTarget() { return mTimeToTarget; };

private:
	float mArriveRadius = 10.0f;
	float mSlowRadius = 200.0f;
	float mTimeToTarget = .25f;
};
