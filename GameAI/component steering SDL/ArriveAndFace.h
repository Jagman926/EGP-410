#include <Trackable.h>
#include "Steering.h"

class ArriveSteering;
class FaceSteering;

class ArriveAndFaceSteering : public Steering
{
public:
	ArriveAndFaceSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID);

protected:
	ArriveSteering* mpArriveSteering;
	FaceSteering* mpFaceSteering;
		//
	virtual Steering* getSteering();

};
