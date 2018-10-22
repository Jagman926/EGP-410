#include "InputManager.h"
#include "Game.h"
#include "GameApp.h"
#include "GameMessageManager.h"
#include "GameMessage.h"
#include "PathToMessage.h"
#include "ExitMessage.h"
#include "PathfinderTypeMessage.h"
#include <iostream>
#include <SDL_events.h>

InputManager::InputManager()
{

}

InputManager::~InputManager()
{
	cleanUp();
}

void InputManager::init()
{

}

void InputManager::cleanUp()
{

}

void InputManager::update()
{
	GameApp* pGame = dynamic_cast<GameApp*>(gpGame);
	GameMessageManager* mpGameMessageManager = pGame->getMessageManager();
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		//Game message
		GameMessage* pMessage;

		if (event.type == SDL_KEYDOWN)
		{
			int keyCode = event.key.keysym.sym;
			switch (keyCode)
			{
			case F_KEY:
				pMessage = new PathfinderTypeMessage('f');
				mpGameMessageManager->addMessage(pMessage, 0);
				break;
			case A_KEY:
				pMessage = new PathfinderTypeMessage('a');
				mpGameMessageManager->addMessage(pMessage, 0);
				break;
			case D_KEY:
				pMessage = new PathfinderTypeMessage('d');
				mpGameMessageManager->addMessage(pMessage, 0);
				break;
			case ESC_KEY:
				pMessage = new ExitMessage();
				mpGameMessageManager->addMessage(pMessage, 0);
				break;
			default:
				break;
			}
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			//Get mouse position
			Vector2D pos(event.button.x, event.button.y);
			static Vector2D lastPos(0.0f, 0.0f);
			if (lastPos.getX() != pos.getX() || lastPos.getY() != pos.getY())
			{
				pMessage = new PathToMessage(lastPos, pos);
				mpGameMessageManager->addMessage(pMessage, 0);
				lastPos = pos;
			}
		}
	}
	//Process messages for the frame
	mpGameMessageManager->processMessagesForThisframe();
}
