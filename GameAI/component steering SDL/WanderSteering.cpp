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

	mpFaceSteering = new FaceSteering(ownerID, targetLoc, targetID);
}

Steering * WanderSteering::getSteering()
{
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

	//Delegate to face
	mpFaceSteering->setTargetLoc(mTargetLoc);
	Steering* newSteering = mpFaceSteering->getSteering();

	if (newSteering != NULL)
	{
		data.rotAcc = newSteering->getData().rotAcc;
	}
	
	//Set linear acceleration
	data.acc = characterOriVec * pOwner->getMaxAcc();

	//Set data
	this->mData = data;
	return this;
}
