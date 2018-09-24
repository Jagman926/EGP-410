#pragma once

#include "Trackable.h"

enum MessageType
{
	INVALID_MESSAGE_TYPE = -1,
	PLAYER_MOVETO_MESSAGE,
	OUTPUT_MOUSE_COORDS,
	DELETE_RANDOM_UNIT,
	ADD_RANDOM_UNIT,
	EXIT_GAME
};

class GameMessage: public Trackable
{
public:
	friend class GameMessageManager;

	GameMessage( MessageType type  );
	~GameMessage();

	double getSubmittedTime() const { return mSubmittedTime; };
	double getScheduledTime() const { return mScheduledTime; };

protected:
	MessageType mType;
	double mSubmittedTime;
	double mScheduledTime;

private:
	virtual void process() = 0; 
};

