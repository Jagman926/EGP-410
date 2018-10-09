#include <cassert>

#include "SeparationSteering.h"
#include "CohesionSteering.h"
#include "GroupAlignmentSteering.h"
#include "FlockingSteering.h"
#include "FaceSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"

FlockingSteering::FlockingSteering(const UnitID & ownerID, const Vector2D & targetLoc, const UnitID & targetID)
{
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
	mType = Steering::FLOCKING;
}

Steering * FlockingSteering::getSteering()
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data;
	//Get Steering pointers
	mpSeparationSteering = new SeparationSteering(mOwnerID, mTargetLoc, mTargetID);
	mpCohesionSteering = new CohesionSteering(mOwnerID, mTargetLoc, mTargetID);
	mpGroupAlignmentSteering = new GroupAlignmentSteering(mOwnerID, mTargetLoc, mTargetID);
	//Assign steering data
	Steering* pSeparationSteeringData = mpSeparationSteering->getSteering();
	Steering* pCohesionSteeringData = mpCohesionSteering->getSteering();
	Steering* pGroupAlignmentSteeringData = mpGroupAlignmentSteering->getSteering();
	Steering* pFaceSteeringData;

	//Wander
	////////////////////////////////////////////////////////////////////////////
	//Orientations
	float wanderOri = 0, targetOri = 0;

	//Update wander rotation
	wanderOri += genRandomBinomial() * mWanderRate;
	//Calculate the combined target orientation
	targetOri = wanderOri + pOwner->getFacing();
	//Calculate the center of the wander cirlce
	Vector2D characterOriVec = Vector2D(cos(pOwner->getFacing()), sin(pOwner->getFacing()));
	mTargetLoc = pOwner->getPositionComponent()->getPosition() + characterOriVec * mWanderOffset;
	//Calculate the target location
	Vector2D targetOriVec = Vector2D(cos(targetOri), sin(targetOri));
	mTargetLoc += targetOriVec * mWanderRadius * .3;
	////////////////////////////////////////////////////////////////////////////////
	//Add steerings with weights
	Vector2D separation, cohesion, alignment;

	//Separation
	separation = pSeparationSteeringData->getData().acc * getSeparationWeight();
	//Cohesion
	cohesion = pCohesionSteeringData->getData().acc * getCohesionWeight();
	//Alignment
	alignment = pGroupAlignmentSteeringData->getData().acc * getAlignmentWeight();

	//Total acceleration
	mTargetLoc += separation + cohesion + alignment;

	//Normalize and face
	mTargetLoc.normalize();
	FaceSteering mFaceSteering(mOwnerID, mTargetLoc + pOwner->getPositionComponent()->getPosition(), mTargetID);
	data = mFaceSteering.getSteering()->getData();
	data.acc = mTargetLoc * pOwner->getMaxAcc();

	//Return steering
	this->mData = data;
	delete mpSeparationSteering;
	delete mpCohesionSteering;
	delete mpGroupAlignmentSteering;
	return this;
}

