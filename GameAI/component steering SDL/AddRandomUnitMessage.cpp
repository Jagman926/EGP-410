#include "Game.h"
#include "GameMessageManager.h"
#include "AddRandomUnitMessage.h"
#include "UnitManager.h"
#include "SpriteManager.h"

AddRandomUnitMessage::AddRandomUnitMessage()
	:GameMessage(ADD_RANDOM_UNIT)
{
}

AddRandomUnitMessage::~AddRandomUnitMessage()
{
}

void AddRandomUnitMessage::process()
{
	gpGame->getUnitManager()->createRandomUnit(*gpGame->getSpriteManager()->getSprite(AI_ICON_SPRITE_ID));
}