#include <cassert>

#include "Steering.h"
#include "WanderSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"

WanderSteering::WanderSteering(const UnitID & ownerID, const Vector2D & targetLoc, const UnitID & targetID)
{
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
}

Steering * WanderSteering::getSteering()
{
	//Variables
	Vector2D target;
	Vector2D targetVec2Ori;
	float targetOrientation;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	float wanderOrientation = pOwner->getFacing();

	if (mTargetID != INVALID_UNIT_ID)
	{
		//face unit
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != NULL);
		mTargetLoc = pTarget->getPositionComponent()->getPosition();
	}

	//Update wander rotation
	wanderOrientation += genRandomBinomial() * getWanderRate();

	//Calculate the combined target orientation
	targetOrientation = wanderOrientation + pOwner->getFacing();

	//Calculate the center of the wander cirlce
	target = pOwner->getPositionComponent()->getPosition() + getWanderOffset() * (sin(pOwner->getFacing()), cos(pOwner->getFacing()));

	//Calculate the target location
	targetVec2Ori = mTargetLoc - pOwner->getPositionComponent()->getPosition();
	target += getWanderRadius() * (targetVec2Ori.getX(), targetVec2Ori.getY());

	//Delegate to face

	//Set linear acceleration
	data.acc = data.maxAccMagnitude * (sin(pOwner->getFacing()), cos(pOwner->getFacing()));

	//Set data
	this->mData = data;
	return this;
}
