#include <cassert>

#include "Steering.h"
#include "FaceSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"

FaceSteering::FaceSteering(const UnitID & ownerID, const Vector2D & targetLoc, const UnitID & targetID)
{
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
}

Steering * FaceSteering::getSteering()
{
	Vector2D rotation;
	Vector2D targetRotation;
	float rotationSize;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();

	if (mTargetID != INVALID_UNIT_ID)
	{
		//arrive unit
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != NULL);
		mTargetLoc = pTarget->getPositionComponent()->getPosition();
	}

	//Get naive direction to the target
	rotation = mTargetLoc - pOwner->getPositionComponent()->getPosition();

	//Map to (-pi, pi) interval
	rotation = (float)atan2(rotation.getX(), rotation.getY());
	rotationSize = abs(rotation.getLength());
	
	if (rotationSize < getTargetRadius())
	{
		//stop rotating
		data.rotVel = 0;
		data.rotAcc = 0;
		this->mData = data;
		return this;
	}
	else if (rotationSize > getSlowRadius())
	{
		targetRotation = pOwner->getMaxRotVel();
	}
	else
	{
		targetRotation = pOwner->getMaxRotVel() * rotationSize / getSlowRadius();
	}

	//Combine final target rotation
	targetRotation = rotation;
	targetRotation /= rotationSize;

	//Acceleration to target rotation
	//data.rotAcc = targetRotation - ;

	//Cap rotation acceleration
	


	return nullptr;
}
