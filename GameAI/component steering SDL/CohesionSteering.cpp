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
	Vector2D totalPositions = (0,0), averagePosition, direction;
	float distance;
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
	//Average out positions
	averagePosition /= unitsInRange.size();
	//get direction to position
	direction = pOwner->getPositionComponent()->getPosition() - averagePosition;
	//Get distance apart
	distance = direction.getLength();
	//Add acceleration
	direction.normalize();
	data.acc += direction * pOwner->getMaxAcc();
	
	//Return steering
	this->mData = data;
	return this;
}
