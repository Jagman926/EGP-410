#include <Trackable.h>
#include "Steering.h"

class FaceSteering : public Steering
{
public:
	FaceSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID);
	//
	virtual Steering* getSteering();
	//
	void setTargetRadius(float radius) { mTargetRadius = radius; };
	void setSlowRadius(float radius) { mSlowRadius = radius; };
	void setTimeToTarget(float time) { mTimeToTarget = time; };
	float mapToRange(float roationInRadians);

protected:
	float getTargetRadius() { return mTargetRadius; };
	float getSlowRadius() { return mSlowRadius; };
	float getTimeToTarget() { return mTimeToTarget; };

private:
	const float PI = 3.1415926f;
	float mTargetRadius = 0.1f;
	float mSlowRadius = 0.5f;
	float mTimeToTarget = 0.5f;
};
