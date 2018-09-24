#include <cassert>

#include "Steering.h"
#include "WanderAndChaseSteering.h"
#include "SeekSteering.h" 
#include "WanderSteering.h"
#include "FaceSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"

WanderAndChaseSteering::WanderAndChaseSteering(const UnitID & ownerID, const Vector2D & targetLoc, const UnitID & targetID, bool shouldFlee)
{
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
	mType = Steering::WANDER_CHASE;
}

Steering * WanderAndChaseSteering::getSteering()
{
	//steering pointers
	mpSeekSteering = new SeekSteering(mOwnerID, mTargetLoc, mTargetID);
	mpWanderSteering = new WanderSteering(mOwnerID, mTargetLoc, mTargetID);
	mpFaceSteering = new FaceSteering(mOwnerID, mTargetLoc, mTargetID);
	//steering data
	Steering* pFaceSteeringData = mpFaceSteering->getSteering();
	mpSteeringData = NULL;

	Vector2D direction;
	float playerDirection;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();

	if (mTargetID != INVALID_UNIT_ID)
	{
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != NULL);
		mTargetLoc = pTarget->getPositionComponent()->getPosition();
	}

	//set directions
	direction = mTargetLoc - pOwner->getPositionComponent()->getPosition();
	playerDirection = direction.getLength();

	if (playerDirection < getSeekRadius())
	{
		//get to seek steering
		mpSteeringData = mpSeekSteering->getSteering();

		//set target location for face
		mpFaceSteering->setTargetLoc(mTargetLoc);
		pFaceSteeringData = mpFaceSteering->getSteering();

		//apply rotation from face data
		data.rotAcc = mpFaceSteering->getData().rotAcc;
	}
	else
	{
		//set to wander steering
		mpSteeringData = mpWanderSteering->getSteering();
		//apply rotation from wander data
		data.rotAcc = mpSteeringData->getData().rotAcc;
	}
	//set acceleration
	data.acc = mpSteeringData->getData().acc;

	this->mData = data;

	//clean up
	delete mpFaceSteering;
	delete mpSeekSteering;
	delete mpWanderSteering;

	return this;
}
