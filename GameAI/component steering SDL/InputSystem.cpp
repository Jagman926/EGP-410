#include "InputSystem.h"
#include <iostream>
#include <SDL_events.h>
#include "Game.h"
#include "GameMessageManager.h"
#include "GameMessage.h"
#include "PlayerMoveToMessage.h"

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
		if (event.type == SDL_KEYDOWN)
		{
			int keyCode = event.key.keysym.sym;
			switch (keyCode)
			{
			case Q_KEY:
				break;
			case W_KEY:
				break;
			case E_KEY:
				break;
			case R_KEY:
				break;
			case D_KEY:
				break;
			case ENTER_KEY:
				break;
			case ESC_KEY:
				break;
			default:
				break;
			}
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			Vector2D pos(event.button.x, event.button.y);
			GameMessage* pMessage = new PlayerMoveToMessage(pos);
			mpGameMessageManager->addMessage(pMessage, 0);
		}
		else if (event.type == SDL_MOUSEMOTION)
		{
			Vector2D pos(event.button.x, event.button.y);
			//std::stringstream mousePos;
			//mousePos << x << ":" << y;
			//mpGraphicsSystem->writeText(*mpFont, (float)x, (float)y, mousePos.str(), BLACK_COLOR);
		}
	}
	//Process messages for the frame
	mpGameMessageManager->processMessagesForThisframe();
}