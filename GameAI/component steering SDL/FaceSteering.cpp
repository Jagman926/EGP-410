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
	Vector2D direction;
	float targetRotation;
	float rotation;
	float rotationSize;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();

	if (mTargetID != INVALID_UNIT_ID)
	{
		//face unit
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != NULL);
		mTargetLoc = pTarget->getPositionComponent()->getPosition();
	}

	//Get naive direction to the target
	direction = mTargetLoc - pOwner->getPositionComponent()->getPosition();
	float targetOri = atan2(direction.getY(), direction.getX()) + .5f * PI;
	float currentRotation = fmod(pOwner->getFacing(), 2 * PI);
	rotation = targetOri - currentRotation;

	//Get rotation size
	rotationSize = abs(rotation);
	
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
	targetRotation *= rotation / rotationSize;

	//Acceleration to target rotation
	data.rotAcc = targetRotation - currentRotation;
	data.rotAcc /= getTimeToTarget();

	//Cap rotation acceleration
	float rotAcc = abs(data.rotAcc);
	if (rotAcc > data.maxRotAcc)
	{
		data.rotAcc /= rotAcc;
		data.rotAcc *= data.maxRotAcc;
	}

	//Set data
	data.vel = 0;
	this->mData = data;
	return this;
}
