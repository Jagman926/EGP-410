#include <cassert>

#include "FlockingSteering.h"
#include "WanderSteering.h"
#include "SeparationSteering.h"
#include "CohesionSteering.h"
#include "GroupAlignmentSteering.h"
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
	Steering* pWanderSteering = mpWanderSteering->getSteering();
	Steering* pSeparationSteeringData = mpSeparationSteering->getSteering();
	Steering* pCohesionSteeringData = mpCohesionSteering->getSteering();
	Steering* pGroupAlignmentData = mpGroupAlignmentSteering->getSteering();

	//Set base wander steering
	data = pWanderSteering->getData();
	//Add steerings with weights
	//Separation
	data.acc += pSeparationSteeringData->getData().acc * getSeparationWeight();
	//Cohesion
	data.acc += pCohesionSteeringData->getData().acc * getCohesionWeight();
	//Alignment
	data.acc += pGroupAlignmentData->getData().acc * getAlignmentWeight();

	//cap acceleration
	if (data.acc.getLength() > pOwner->getMaxAcc())
	{
		data.acc.normalize();
		data.acc *= pOwner->getMaxAcc();
	}

	//Return steering
	this->mData = data;
	return this;
}
