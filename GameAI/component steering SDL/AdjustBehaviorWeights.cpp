#include "AdjustBehaviorWeights.h"
#include "Game.h"

AdjustBehaviorWeights::AdjustBehaviorWeights(char key)
	:GameMessage(ADJUST_WEIGHTS)
{
	mKey = key;
}

AdjustBehaviorWeights::~AdjustBehaviorWeights()
{

}

void AdjustBehaviorWeights::process()
{
	switch (mKey)
	{
	case 'q':
		gpGame->setSeparationWeight(gpGame->getSeparationWeight() + .1f);
		break;
	case 'w':
		gpGame->setSeparationWeight(gpGame->getSeparationWeight() - .1f);
		break;
	case 'e':
		gpGame->setCohesionWeight(gpGame->getCohesionWeight() + .1f);
		break;
	case 'r':
		gpGame->setCohesionWeight(gpGame->getCohesionWeight() - .1f);
		break;
	case 't':
		gpGame->setAlignmentWeight(gpGame->getAlignmentWeight() + .1f);
		break;
	case 'y':
		gpGame->setAlignmentWeight(gpGame->getAlignmentWeight() - .1f);
		break;
	default:
		break;
	}
}
