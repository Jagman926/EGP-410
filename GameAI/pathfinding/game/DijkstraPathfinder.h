#ifndef DIJKSTRA_PATHFINDER
#define DIJKSTRA_PATHFINDER

#include "GridPathfinder.h"
#include "NodeRecord.h"

class Node;
class Path;
class Graph;
class GraphicsBuffer;
class Grid;
class Connection;

class DijkstraPathfinder : public GridPathfinder
{
public:
	DijkstraPathfinder(Graph *pGraph);
	~DijkstraPathfinder();
	
	//Finds path from starting node (pFrom) to the goal node (pTo) a priority queue
	//(acts like a breadth first search)d
	Path* findPath(Node* pFrom, Node* pTo);
};

#endif // !DIJKSTRA_PATHFINDER