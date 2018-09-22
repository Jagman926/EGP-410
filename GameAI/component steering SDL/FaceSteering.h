#include <Trackable.h>
#include "Steering.h"

class FaceSteering : public Steering
{
public:
	FaceSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID);
	//
	void setTargetRadius(float radius) { targetRadius = radius; };
	void setSlowRadius(float radius) { slowRadius = radius; };
	void setTimeToTarget(float time) { timeToTarget = time; };
	float getTargetRadius() { return targetRadius; };
	float getSlowRadius() { return slowRadius; };
	float getTimeToTarget() { return timeToTarget; };

protected:
	virtual Steering* getSteering();

private:
	float targetRadius = 10.0f;
	float slowRadius = 200.0f;
	float timeToTarget = .25f;
};
