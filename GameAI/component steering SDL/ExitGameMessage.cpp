#include "Game.h"
#include "GameMessageManager.h"
#include "ExitGameMessage.h"

ExitGameMessage::ExitGameMessage()
	:GameMessage(EXIT_GAME)
{
}

ExitGameMessage::~ExitGameMessage()
{
}

void ExitGameMessage::process()
{
	gpGame->shouldExit();
}