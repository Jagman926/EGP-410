#pragma once

#include "GridPathfinder.h"
#include "Node.h"
#include <list>

class Grid;
class GraphicsBuffer;
class Graph;
class Path;
class Connection;

struct NodeRecord
{
	Node* mNode;
	Connection* mConnection;
	float mCostSoFar;
	float mEstimatedTotalCost;

	void insert(Node* n, Connection* c, float cost, float estimatedCost = -1.0f) { mNode = n; mConnection = c; mCostSoFar = cost; mEstimatedTotalCost = estimatedCost; };

	friend bool operator== (const NodeRecord &lhs, const NodeRecord &rhs) { return  lhs.mNode == rhs.mNode; };

	bool operator ==(const NodeRecord& rhs) { return mNode == rhs.mNode; };
};