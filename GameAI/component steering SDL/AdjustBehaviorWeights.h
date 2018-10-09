#pragma once

#include "GameMessage.h"
#include "Vector2D.h"

class AdjustBehaviorWeights :public GameMessage
{
public:
	AdjustBehaviorWeights(char key);
	~AdjustBehaviorWeights();

	void process();

private:
	char mKey;
};
