#pragma once

#include "GameMessage.h"
#include "Vector2D.h"

class ExitGameMessage :public GameMessage
{
public:
	ExitGameMessage();
	~ExitGameMessage();

	void process();
};