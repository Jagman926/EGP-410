#include <cassert>

#include "Steering.h"
#include "ArriveSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"

ArriveSteering::ArriveSteering(const UnitID & ownerID, const Vector2D & targetLoc, const UnitID & targetID)
{
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
	mType = Steering::ARRIVE;
}

Steering * ArriveSteering::getSteering()
{
	//Variables
	Vector2D direction, targetVelocity;
	float distance, targetSpeed;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();

	if (mTargetID != INVALID_UNIT_ID)
	{
		//arrive unit
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != NULL);
		mTargetLoc = pTarget->getPositionComponent()->getPosition();
	}

	//Get distance to target
	direction = mTargetLoc - pOwner->getPositionComponent()->getPosition();
	distance = direction.getLength();

	//Check if inside arrive radius
	if (distance < getArriveRadius())
	{
		//stop steering
		data.acc = 0;
		data.vel = 0;
		this->mData = data;
		return this;
	}
	//If outside slow radius
	else if (distance > getSlowRadius())
	{
		targetSpeed = data.maxSpeed;
	}
	//If inside slow radius
	else
	{
		targetSpeed = (data.maxSpeed * distance / getSlowRadius());
	}

	//taget velocity combines speed and direction
	targetVelocity = direction;
	targetVelocity.normalize();
	targetVelocity *= targetSpeed;

	//Acceleration tries to get to the target velocity
	data.acc = targetVelocity - pOwner->getPhysicsComponent()->getVelocity();
	data.acc /= getTimeToTarget();

	//Cap acceleration
	if (data.acc.getLength() > data.maxAccMagnitude)
	{
		data.acc.normalize();
		data.acc *= data.maxAccMagnitude;
	}

	//Set data
	data.rotVel = 0;
	this->mData = data;
	return this;
}