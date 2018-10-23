#ifndef NODE_RECORD
#define NODE_RECORD

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
	//Variables
	Node* mNode;
	Connection* mConnection;
	float mCostSoFar;
	float mEstimatedTotalCost;

	//Insert function
	void insert(Node* n, Connection* c, float cost, float estimatedCost = -1.0f);

	//Operator functions
	friend bool operator== (const NodeRecord &lhs, const NodeRecord &rhs) { return  lhs.mNode == rhs.mNode; };
	bool operator ==(const NodeRecord& rhs) { return mNode == rhs.mNode; };
};

#endif // !NODE_RECORD