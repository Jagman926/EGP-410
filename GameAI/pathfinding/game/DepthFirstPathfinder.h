#ifndef DEPTH_FIRST_PATHFINDER
#define DEPTH_FIRST_PATHFINDER

#include "GridPathfinder.h"
#include <vector>

class Path;
class Graph;
class GraphicsBuffer;
class Grid;

class DepthFirstPathfinder :public GridPathfinder
{
public:
	DepthFirstPathfinder(Graph* pGraph);
	~DepthFirstPathfinder();

	//Finds path from starting node (pFrom) to the goal node (pTo) using a depth first 
	//searched by implementing a list in the form of a stack
	Path* findPath(Node* pFrom, Node* pTo);

private:
};

#endif // !DEPTH_FIRST_PATHFINDER

