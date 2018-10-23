#ifndef EXIT_MESSAGE_H
#define EXIT_MESSAGE_H

#include "GameMessage.h"

class ExitMessage : public GameMessage
{
public:
	ExitMessage();
	~ExitMessage();

	void process();
};

#endif // !EXIT_MESSAGE_H