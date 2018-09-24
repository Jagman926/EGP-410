#include "Game.h"
#include "GameMessageManager.h"
#include "DeleteRandomUnitMessage.h"
#include "UnitManager.h"

DeleteRandomUnitMessage::DeleteRandomUnitMessage()
	:GameMessage(DELETE_RANDOM_UNIT)
{
}

DeleteRandomUnitMessage::~DeleteRandomUnitMessage()
{
}

void DeleteRandomUnitMessage::process()
{
	gpGame->getUnitManager()->deleteRandomUnit();
}