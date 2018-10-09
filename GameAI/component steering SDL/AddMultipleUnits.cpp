#include "Game.h"
#include "AddMultipleUnits.h"
#include "AddRandomUnitMessage.h"
#include "UnitManager.h"
#include "SpriteManager.h"

AddMultipleUnits::AddMultipleUnits()
	:GameMessage(ADD_MULTIPLE_UNITS)
{

}

AddMultipleUnits::~AddMultipleUnits()
{

}

void AddMultipleUnits::process()
{
	for (size_t i = 0; i < 10; i++)
	{
		gpGame->getUnitManager()->createRandomUnit(*gpGame->getSpriteManager()->getSprite(AI_ICON_SPRITE_ID));
	}
}
