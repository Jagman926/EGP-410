#include <cassert>

#include "SeparationSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"

SeparationSteering::SeparationSteering(const UnitID & ownerID, const Vector2D & targetLoc, const UnitID& targetID)
{
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
	mType = Steering::SEPARATION;
}

Steering * SeparationSteering::getSteering()
{
	Vector2D direction;
	float distance, strength;
	std::vector<Unit*> unitsInRange;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();

	//Get all units in range of seperation radius
	unitsInRange = gpGame->getUnitManager()->getUnitsInRange(pOwner->getPositionComponent()->getData(), getSeperationRadius());
	//Loop to move away from units
	for (Unit* unit : unitsInRange)
	{
		//Get direction
		direction = pOwner->getPositionComponent()->getPosition() - unit->getPositionComponent()->getPosition();
		//Get distance
		distance = direction.getLength();
		//Get strength
		strength = std::fmin(getDecayCoefficient() / pow(distance, 2), pOwner->getMaxAcc());
		//Add acceleration
		direction.normalize();
		data.acc += direction * strength;
	}
	//Return if no units in range
	if (unitsInRange.size() == 0)
	{
		data.acc = 0;
		data.rotAcc = 0;
	}
	else
	{
		data.acc /= unitsInRange.size();
	}
	//Return steering
	this->mData = data;
	return this;
}
