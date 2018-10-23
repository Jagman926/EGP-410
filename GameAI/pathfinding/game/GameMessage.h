#ifndef GAME_MESSAGE
#define GAME_MESSAGE

#include <Trackable.h>

enum MessageType
{
	INVALID_MESSAGE_TYPE = -1,
	PLAYER_MOVETO_MESSAGE,
	PATH_TO_MESSAGE,
	EXIT_GAME_MESSAGE,
	PATHFINDER_TYPE_MESSAGE
};

class GameMessage : public Trackable
{
public:
	friend class GameMessageManager;

	GameMessage(MessageType type);
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


#endif // !GAME_MESSAGE

