#ifndef DEBUG_CONTENT
#define DEBUG_CONTENT

#include <string>
#include <Trackable.h>

class DebugContent :public Trackable
{
public:
	DebugContent() {};
	virtual ~DebugContent() {};

	virtual std::string getDebugString() = 0;
};

#endif // !DEBUG_CONTENT