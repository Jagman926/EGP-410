#pragma once

#include "GameMessage.h"
#include "Vector2D.h"

class AddRandomUnitMessage :public GameMessage
{
public:
	AddRandomUnitMessage();
	~AddRandomUnitMessage();

	void process();
};
