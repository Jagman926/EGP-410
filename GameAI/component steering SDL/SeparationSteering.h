#ifndef SEPARATION_STEERING

#include <Trackable.h>
#include "Steering.h"

class SeparationSteering : public Steering
{
public:
	SeparationSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID);
	//
	virtual Steering* getSteering();
	//
	void setDecayCoefficient(float decay) { mDecayCoefficient = decay; };
	void setSeperationRadius(float radius) { mSeperationRadius = radius; };

protected:
	float getDecayCoefficient() { return mDecayCoefficient; };
	float getSeperationRadius() { return mSeperationRadius; };

private:
	float mDecayCoefficient = .3f;
	float mSeperationRadius = 30.0f;
};

#endif // !SEPARATION_STEERING
