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
	mpSeekSteering = new SeekSteering(mOwnerID, mTargetLoc, mTargetID);
	mpWanderSteering = new WanderSteering(mOwnerID, mTargetLoc, mTargetID);
	mpFaceSteering = new FaceSteering(mOwnerID, mTargetLoc, mTargetID);

	Vector2D direction;
	float playerDirection;
	Steering* faceSteeringData = mpFaceSteering->getSteering();
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	mpSteeringData = NULL;

	if (mTargetID != INVALID_UNIT_ID)
	{
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != NULL);
		mTargetLoc = pTarget->getPositionComponent()->getPosition();
	}

	direction = mTargetLoc - pOwner->getPositionComponent()->getPosition();
	playerDirection = direction.getLength();

	if (playerDirection < mSEEK_RADIUS)
	{
		mpSteeringData = mpSeekSteering->getSteering();

		mpFaceSteering->setTargetLoc(mTargetLoc);
		faceSteeringData = mpFaceSteering->getSteering();

		data.rotAcc = mpFaceSteering->getData().rotAcc;
	}
	else
	{
		mpSteeringData = mpWanderSteering->getSteering();
		data.rotAcc = mpSteeringData->getData().rotAcc;
	}

	data.acc = mpSteeringData->getData().acc;

	this->mData = data;
	delete mpFaceSteering;
	delete mpSeekSteering;
	delete mpWanderSteering;
	return this;
}
