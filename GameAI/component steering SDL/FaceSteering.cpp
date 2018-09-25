#include <cassert>

#include "FaceSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"


FaceSteering::FaceSteering(const UnitID & ownerID, const Vector2D & targetLoc, const UnitID & targetID)
{
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
	mType = Steering::FACE;
}

Steering * FaceSteering::getSteering()
{
	Vector2D direction;
	float targetRotation, rotation, rotationSize, mappedRotation;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();

	if (mTargetID != INVALID_UNIT_ID)
	{
		//seeking unit
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != NULL);
		mTargetLoc = pTarget->getPositionComponent()->getPosition();
	}

	//Get naive direction to the target
	direction = mTargetLoc - pOwner->getPositionComponent()->getPosition();
	float targetOri = atan2(direction.getY(), direction.getX());
	rotation = targetOri - pOwner->getFacing();

	//Get rotation size
	mappedRotation = mapToRange(rotation);
	rotationSize = abs(mappedRotation);
	
	if (rotationSize < getTargetRadius())
	{
		//stop rotating
		return nullptr;
	}
	if (rotationSize > getSlowRadius())
	{
		targetRotation = pOwner->getMaxRotAcc();
	}
	else
	{
		targetRotation = pOwner->getMaxRotAcc() * rotationSize / getSlowRadius();
	}

	//Combine final target rotation
	targetRotation *= rotation / rotationSize;

	//Acceleration to target rotation
	data.rotAcc = targetRotation - data.rotVel;
	data.rotAcc /= getTimeToTarget();

	//Cap rotation acceleration
	float angularAcc = abs(data.rotAcc);
	if (angularAcc > data.maxRotAcc)
	{
		data.rotAcc /= angularAcc;
		data.rotAcc *= data.maxRotAcc;
	}

	data.acc = 0;
	//Set data
	this->mData = data;
	return this;
}

float FaceSteering::mapToRange(float rotationInRadians)
{
	float convertedRotation;

	convertedRotation = fmod((rotationInRadians), 2 * PI);
	if (convertedRotation > PI)
	{
		convertedRotation = (convertedRotation - PI) * -1.0f;
	}
	else if (convertedRotation < -PI)
	{
		convertedRotation = (convertedRotation + PI) * -1.0f;
	}

	return convertedRotation;

}
