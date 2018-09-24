#include "InputSystem.h"
#include <iostream>
#include <SDL_events.h>
#include "Game.h"
#include "GameMessageManager.h"
#include "GameMessage.h"
#include "PlayerMoveToMessage.h"
#include "OutputMouseCoordsMessage.h"
#include "DeleteRandomUnitMessage.h"
#include "AddRandomUnitMessage.h"
#include "ExitGameMessage.h"

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
	cleanup();
}

void InputSystem::init()
{
}

void InputSystem::cleanup()
{

}

void InputSystem::update()
{
	GameMessageManager* mpGameMessageManager = gpGame->getMessageManager();
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
			case D_KEY:
				pMessage = new DeleteRandomUnitMessage();
				mpGameMessageManager->addMessage(pMessage, 0);
				break;
			case ENTER_KEY:
				pMessage = new AddRandomUnitMessage();
				mpGameMessageManager->addMessage(pMessage, 0);
				break;
			case ESC_KEY:
				pMessage = new ExitGameMessage();
				mpGameMessageManager->addMessage(pMessage, 0);
				break;
			default:
				break;
			}
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			//Move player to mouse position
			Vector2D pos(event.button.x, event.button.y);
			pMessage = new PlayerMoveToMessage(pos);
			mpGameMessageManager->addMessage(pMessage, 0);
		}
		else if (event.type == SDL_MOUSEMOTION)
		{
			//Print moues coords when moving mouse
			Vector2D pos(event.button.x, event.button.y);
			pMessage = new OutputMouseCoordsMessage(pos);
			mpGameMessageManager->addMessage(pMessage, 0);
		}
	}
	//Process messages for the frame
	mpGameMessageManager->processMessagesForThisframe();
}