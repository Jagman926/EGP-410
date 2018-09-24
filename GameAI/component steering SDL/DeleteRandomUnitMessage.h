#pragma once

#include "GameMessage.h"
#include "Vector2D.h"

class DeleteRandomUnitMessage :public GameMessage
{
public:
	DeleteRandomUnitMessage();
	~DeleteRandomUnitMessage();

	void process();
};
