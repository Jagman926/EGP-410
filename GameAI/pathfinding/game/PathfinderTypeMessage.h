#pragma once

#include "GameMessage.h"

class PathfinderTypeMessage : public GameMessage
{
public:
	PathfinderTypeMessage(char pathType);
	~PathfinderTypeMessage();

	void process();

private:
	bool mTypeChange;
	char mCurrentPathType;
};