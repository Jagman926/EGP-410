#include <Trackable.h>
#include "Steering.h"

class FaceSteering : public Steering
{
public:
	FaceSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID);
	//
	virtual Steering* getSteering();
	//
	void setTargetRadius(float radius) { targetRadius = radius; };
	void setSlowRadius(float radius) { slowRadius = radius; };
	void setTimeToTarget(float time) { timeToTarget = time; };
	float getTargetRadius() { return targetRadius; };
	float getSlowRadius() { return slowRadius; };
	float getTimeToTarget() { return timeToTarget; };

private:
	const float PI = 3.1415926;
	float targetRadius = 2.0 / 180 * PI;
	float slowRadius = 30.0f /180 * PI;
	float timeToTarget = 0.2f;
};
