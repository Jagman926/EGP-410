#include <cassert>

#include "WanderSteering.h"
#include "SeparationSteering.h"
#include "CohesionSteering.h"
#include "GroupAlignmentSteering.h"
#include "FlockingSteering.h"
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
	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	//Get Steering pointers
	mpWanderSteering = new WanderSteering(mOwnerID, mTargetLoc, mTargetID);
	mpSeparationSteering = new SeparationSteering(mOwnerID, mTargetLoc, mTargetID);
	mpCohesionSteering = new CohesionSteering(mOwnerID, mTargetLoc, mTargetID);
	mpGroupAlignmentSteering = new GroupAlignmentSteering(mOwnerID, mTargetLoc, mTargetID);
	//Assign steering data
	Steering* pWanderSteeringData = mpWanderSteering->getSteering();
	Steering* pSeparationSteeringData = mpSeparationSteering->getSteering();
	Steering* pCohesionSteeringData = mpCohesionSteering->getSteering();
	Steering* pGroupAlignmentSteeringData = mpGroupAlignmentSteering->getSteering();

	//Set base wander steering
	data.acc += pWanderSteeringData->getData().acc;
	data.rotAcc += pWanderSteeringData->getData().rotAcc;
	//Add steerings with weights
	//Separation
	data.acc += pSeparationSteeringData->getData().acc * getSeparationWeight();
	data.rotAcc += pSeparationSteeringData->getData().rotAcc * getSeparationWeight();
	//Cohesion
	data.acc += pCohesionSteeringData->getData().acc * getCohesionWeight();
	data.rotAcc += pCohesionSteeringData->getData().rotAcc * getCohesionWeight();
	//Alignment
	data.acc += pGroupAlignmentSteeringData->getData().acc * getAlignmentWeight();
	data.rotAcc += pGroupAlignmentSteeringData->getData().rotAcc * getAlignmentWeight();

	//cap acceleration
	if (data.acc.getLength() > pOwner->getMaxAcc())
	{
		data.acc.normalize();
		data.acc *= pOwner->getMaxAcc();
	}
	//cap rotation acceleration
	if (data.rotAcc > pOwner->getMaxRotAcc())
	{
		data.rotAcc = pOwner->getMaxRotAcc();
	}

	//Return steering
	this->mData = data;
	delete mpWanderSteering;
	delete mpSeparationSteering;
	delete mpCohesionSteering;
	delete mpGroupAlignmentSteering;
	return this;
}
