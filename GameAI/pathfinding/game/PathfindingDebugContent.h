#ifndef PATHFINDING_DEBUG_CONTENT
#define PATHFINDING_DEBUG_CONTENT

#include "DebugContent.h"

class GridPathfinder;

class PathfindingDebugContent :public DebugContent
{
public:
	PathfindingDebugContent(GridPathfinder* pPathfinder, char currentPathfinderType);
	~PathfindingDebugContent() {};

	std::string getDebugString();

private:
	GridPathfinder* mpPathfinder;
	char currentPathfinderType;
};

#endif // !PATHFINDING_DEBUG_CONTENT