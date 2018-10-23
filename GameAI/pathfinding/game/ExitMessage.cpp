#include "ExitMessage.h"
#include "Game.h"
#include "GameApp.h"

ExitMessage::ExitMessage()
	:GameMessage(EXIT_GAME_MESSAGE)
{

}

ExitMessage::~ExitMessage()
{

}

void ExitMessage::process()
{
	GameApp* pGame = dynamic_cast<GameApp*>(gpGame);
	pGame->markForExit();
}
