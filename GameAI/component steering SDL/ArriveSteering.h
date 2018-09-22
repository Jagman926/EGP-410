#include <Trackable.h>
#include "Steering.h"

class ArriveSteering : public Steering
{
public:
	ArriveSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID);
	//
	void setArriveRadius(float radius) { arriveRadius = radius; };
	void setSlowRadius(float radius) { slowRadius = radius; };
	void setTimeToTarget(float time) { timeToTarget = time; };
	float getArriveRadius() { return arriveRadius; };
	float getSlowRadius() { return slowRadius; };
	float getTimeToTarget() { return timeToTarget; };

protected:
	virtual Steering* getSteering();

private:
	float arriveRadius = 10.0f;
	float slowRadius = 200.0f;
	float timeToTarget = .25f;
};
