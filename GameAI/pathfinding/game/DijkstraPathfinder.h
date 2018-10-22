#pragma once

#include "GridPathfinder.h"
#include <vector>
#include <Vector2D.h>

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
	//Heuristic
	float heuristic(Vector2D a, Vector2D b);

	//Node record strut
	struct NodeRecord
	{
		Node* mNode;
		Connection* mConnection;
		float mCost;
		float mCostSoFar;
		float mEstimatedTotalCost;
	};

	//Compare estimated cost struct
	struct CompareEstimatedCost : public std::binary_function<NodeRecord, NodeRecord, bool>
	{
		bool operator()(const NodeRecord lhs, const NodeRecord rhs) const
		{
			return lhs.mEstimatedTotalCost < rhs.mEstimatedTotalCost;
		}
	};
};