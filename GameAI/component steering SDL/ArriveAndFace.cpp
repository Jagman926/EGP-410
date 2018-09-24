#include <cassert>

#include "ArriveAndFace.h"
#include "ArriveSteering.h"
#include "FaceSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"

ArriveAndFaceSteering::ArriveAndFaceSteering(const UnitID & ownerID, const Vector2D & targetLoc, const UnitID & targetID)
{
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
	mType = Steering::ARRIVE_FACE;
}

Steering * ArriveAndFaceSteering::getSteering()
{
	mpArriveSteering = new ArriveSteering(mOwnerID, mTargetLoc, mTargetID);
	mpFaceSteering = new FaceSteering(mOwnerID, mTargetLoc, mTargetID);

	Steering* faceSteeringData = mpFaceSteering->getSteering();
	Steering* arriveSteeringData = mpArriveSteering->getSteering();
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();

	if (arriveSteeringData != NULL)
	{
		data.acc = arriveSteeringData->getData().acc;

		if (faceSteeringData != NULL)
		{
			data.rotAcc = faceSteeringData->getData().rotAcc;
		}
	}
	else
	{
		data.vel = 0;
		data.acc = 0;
		data.rotVel = 0;
		data.rotAcc = 0;
	}

	this->mData = data;
	delete mpArriveSteering;
	delete mpFaceSteering;
	return this;
}