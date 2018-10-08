#include <cassert>

#include "CohesionSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"

CohesionSteering::CohesionSteering(const UnitID & ownerID, const Vector2D & targetLoc, const UnitID & targetID)
{
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
	mType = Steering::COHESION;
}

Steering * CohesionSteering::getSteering()
{
	Vector2D totalPositions = (0.0f,0.0f), direction;
	std::vector<Unit*> unitsInRange;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();

	//Get all units in range of cohesion radius
	unitsInRange = gpGame->getUnitManager()->getUnitsInRange(pOwner->getPositionComponent()->getData(), getCohesionRadius());
	//Loop to move towards units
	for (Unit* unit : unitsInRange)
	{
		//Total positions of all units in range
		totalPositions += unit->getPositionComponent()->getPosition();
	}
	//Return if no units in range
	if (unitsInRange.size() == 0)
	{
		data.acc = 0;
		data.rotAcc = 0;
	}
	else
	{
		//Average out positions
		totalPositions /= unitsInRange.size();
		//get direction to position
		direction = totalPositions - pOwner->getPositionComponent()->getPosition();
		//Add acceleration
		data.acc = direction;
	}

	//Return steering
	this->mData = data;
	return this;
}
