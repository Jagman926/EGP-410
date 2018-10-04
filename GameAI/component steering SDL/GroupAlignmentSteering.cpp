#include <cassert>

#include "Steering.h"
#include "GroupAlignmentSteering.h"
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
	std::vector<Unit*> unitsInRange;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();

	//Get all units in range of alignment radius
	unitsInRange = gpGame->getUnitManager()->getUnitsInRange(pOwner->getPositionComponent()->getData(), getAlignmentRadius());
	//Loop to align with units
	for (Unit* unit : unitsInRange)
	{

	}
	//Return steering
	this->mData = data;
	return this;
}
