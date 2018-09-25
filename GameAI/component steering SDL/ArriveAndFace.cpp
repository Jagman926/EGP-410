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
	//steering pointers
	mpArriveSteering = new ArriveSteering(mOwnerID, mTargetLoc, mTargetID);
	mpFaceSteering = new FaceSteering(mOwnerID, mTargetLoc, mTargetID);
	//steering data
	Steering* pFaceSteeringData = mpFaceSteering->getSteering();
	Steering* pArriveSteeringData = mpArriveSteering->getSteering();

	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();

	if (pArriveSteeringData != NULL)
	{
		data.acc = pArriveSteeringData->getData().acc;

		if (pFaceSteeringData != NULL)
		{
			data.rotAcc = pFaceSteeringData->getData().rotAcc;
		}
	}
	else
	{
		data.acc = 0;
		data.vel = 0;
		data.rotAcc = 0;
		data.rotVel = 0;
	}

	this->mData = data;
	delete mpArriveSteering;
	delete mpFaceSteering;
	return this;
}
