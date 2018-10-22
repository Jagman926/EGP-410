#include "InputSystem.h"
#include <iostream>
#include <SDL_events.h>
#include "Game.h"
#include "GameMessageManager.h"
#include "GameMessage.h"

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
			case F_KEY:
				//pMessage = new Message();
				//mpGameMessageManager->addMessage(pMessage, 0);
				break;
			case A_KEY:
				//pMessage = new Message();
				//mpGameMessageManager->addMessage(pMessage, 0);
				break;
			case D_KEY:
				//pMessage = new Message();
				//mpGameMessageManager->addMessage(pMessage, 0);
				break;
			case ESC_KEY:
				//pMessage = new Message();
				//mpGameMessageManager->addMessage(pMessage, 0);
				break;
			default:
				break;
			}
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			//Move player to mouse position
			//Vector2D pos(event.button.x, event.button.y);
			//pMessage = new Message();
			//mpGameMessageManager->addMessage(pMessage, 0);
		}
		else if (event.type == SDL_MOUSEMOTION)
		{
			//Print moues coords when moving mouse
			//Vector2D pos(event.button.x, event.button.y);
			//pMessage = new Message();
			//mpGameMessageManager->addMessage(pMessage, 0);
		}
	}
	//Process messages for the frame
	mpGameMessageManager->processMessagesForThisframe();
}