#include <cassert>

#include "GroupAlignmentSteering.h"
#include "FaceSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"

GroupAlignmentSteering::GroupAlignmentSteering(const UnitID & ownerID, const Vector2D & targetLoc, const UnitID & targetID)
{
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
	mType = Steering::GROUP_ALIGNMENT;
}

Steering * GroupAlignmentSteering::getSteering()
{
	Vector2D averageAcc, totalVel = (0.0f,0.0f);
	std::vector<Unit*> unitsInRange;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	//Face
	mpFaceSteering = new FaceSteering(mOwnerID, mTargetLoc, mTargetID);
	Steering* pFaceSteeringData = mpFaceSteering->getSteering();

	//Get all units in range of alignment radius
	unitsInRange = gpGame->getUnitManager()->getUnitsInRange(pOwner->getPositionComponent()->getData(), getAlignmentRadius());
	//Loop to align with units
	for (Unit* unit : unitsInRange)
	{
		//Add total velocity of all units in range
		totalVel += (unit->getPhysicsComponent()->getVelocity() - pOwner->getPhysicsComponent()->getVelocity());
	}
	//Return if no units in range
	if (unitsInRange.size() == 0)
	{
		data.acc = 0;
		data.rotAcc = 0;
	}
	else
	{
		//Divide by total units
		totalVel /= unitsInRange.size();
		//divide by timeToAlign
		averageAcc = totalVel * (1.0f / getTimeToAlign());
		//Set owners acceleration to average acceleration
		data.acc = averageAcc;
	}
	//Return steering
	this->mData = data;
	delete mpFaceSteering;
	return this;
}
