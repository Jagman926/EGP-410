#pragma once

#include "GameMessage.h"
#include "Vector2D.h"

class AddMultipleUnits :public GameMessage
{
public:
	AddMultipleUnits();
	~AddMultipleUnits();

	void process();
};
