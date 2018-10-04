#include <cassert>

#include "Steering.h"
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
	std::vector<Unit*> unitsInRange;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();

	//Get all units in range of cohesion radius
	unitsInRange = gpGame->getUnitManager()->getUnitsInRange(pOwner->getPositionComponent()->getData(), getCohesionRadius());
	//Loop to move towards units
	for (Unit* unit : unitsInRange)
	{

	}
	//Return steering
	this->mData = data;
	return this;
}
