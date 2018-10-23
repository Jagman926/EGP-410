#ifndef PATHFINDER_TYPE_MESSAGE_H
#define PATHFINDER_TYPE_MESSAGE_H

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

#endif // !PATHFINDER_TYPE_MESSAGE_H