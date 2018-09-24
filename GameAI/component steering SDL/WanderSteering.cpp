#include <cassert>

#include "WanderSteering.h"
#include "FaceSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"


WanderSteering::WanderSteering(const UnitID & ownerID, const Vector2D & targetLoc, const UnitID & targetID)
{
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
	mType = Steering::WANDER;
}

Steering * WanderSteering::getSteering()
{
	//steering pointers
	mpFaceSteering = new FaceSteering(mOwnerID, mTargetLoc, mTargetID);
	//steering data
	Steering* pFaceSteeringData = mpFaceSteering->getSteering();

	//Variables
	Vector2D target;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	//Orientations
	float wanderOri = 0;
	float targetOri = 0;

	//Update wander rotation
	wanderOri += genRandomBinomial() * getWanderRate();

	//Calculate the combined target orientation
	targetOri = wanderOri + pOwner->getFacing();

	//Calculate the center of the wander cirlce
	Vector2D characterOriVec = Vector2D(cos(pOwner->getFacing()), sin(pOwner->getFacing()));
	mTargetLoc = pOwner->getPositionComponent()->getPosition() + characterOriVec * getWanderOffset();

	//Calculate the target location
	Vector2D targetOriVec = Vector2D(cos(targetOri), sin(targetOri));
	mTargetLoc += targetOriVec * getWanderRadius();

	//set face to target
	mpFaceSteering->setTargetLoc(mTargetLoc);

	if (pFaceSteeringData != NULL)
	{
		data.rotAcc = pFaceSteeringData->getData().rotAcc;
	}
	
	//Set linear acceleration
	data.acc = characterOriVec * pOwner->getMaxAcc();

	//Set data
	this->mData = data;
	delete mpFaceSteering;
	return this;
}
