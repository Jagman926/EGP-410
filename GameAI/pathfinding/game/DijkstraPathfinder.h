#pragma once

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
	//
	Path* findPath(Node* pFrom, Node* pTo);

private:
	NodeRecord mNodeRecord;
};