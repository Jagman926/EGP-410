#include "DijkstraPathfinder.h"
#include "Path.h"
#include "Connection.h"
#include "GridGraph.h"
#include "Game.h"
#include "PriorityQueue.h"
#include <PerformanceTracker.h>
#include <functional>
#include <vector>
#include <algorithm>

DijkstraPathfinder::DijkstraPathfinder(Graph * pGraph)
	:GridPathfinder(dynamic_cast<GridGraph*>(pGraph))
{
	#ifdef VISUALIZE_PATH
	mpPath = NULL;
	#endif
}

DijkstraPathfinder::~DijkstraPathfinder()
{
	#ifdef VISUALIZE_PATH
	delete mpPath;
	#endif
}

Path * DijkstraPathfinder::findPath(Node * pFrom, Node * pTo)
{
	//Performance tracking
	gpPerformanceTracker->clearTracker("path");
	gpPerformanceTracker->startTracking("path");

	//Reset and clear path
	#ifdef VISUALIZE_PATH
	delete mpPath;
	mVisitedNodes.clear();
	#endif

	//Create path
	Path* pPath = new Path();
	//Initialize the open and closed lists
	PriorityQueue<NodeRecord, std::vector<NodeRecord>, CompareCost> nodesToVisit, visitedNodes;
	//Node* endNode
	Node* endNode;
	//Node records
	NodeRecord currentRecord = {}, endNodeRecord = {};
	//End heuristic and cost
	float endNodeCost;

	//Initialize the record for the start node
	mNodeRecord = {};
	mNodeRecord.mNode = pFrom;
	mNodeRecord.mConnection = nullptr;
	mNodeRecord.mCostSoFar = 0;

	nodesToVisit.push(mNodeRecord);

	//Iterate through processing each node
	while (currentRecord.mNode != pTo && nodesToVisit.size() > 0)
	{
		//Find smallest element in the open list
		currentRecord = nodesToVisit.top();
		nodesToVisit.pop();

		//If it is the goal node, then terminate
		if (currentRecord.mNode == pTo)
		{
			break;
		}

		//Otherwise get its outgoing connections
		std::vector<Connection*> connections = mpGraph->getConnections(currentRecord.mNode->getId());

		//Loop through each connecto=ion in turn
		for (unsigned int i = 0; i < connections.size(); i++)
		{
			bool containedInOpenList = false;
			Connection* currentConnection = connections[i];

			//get end node and cost
			endNode = currentConnection->getToNode();
			endNodeCost = currentRecord.mCostSoFar + currentConnection->getCost();

			//Create queue check
			NodeRecord tmpClosed = {};
			PriorityQueue <NodeRecord, std::vector<NodeRecord>, CompareCost>::const_iterator it;

			tmpClosed.mNode = endNode;

			it = nodesToVisit.contains(tmpClosed);

			//If the node is closed we may have to skip, or remove it from the closed list
			if (visitedNodes.contains(tmpClosed) != visitedNodes.end())
			{
				continue;
			}
			//Skip if the node is open and we've not found a better route
			else if (it != nodesToVisit.end())
			{
				containedInOpenList = true;

				//Here we find the record in the open list corresponding to the endNode
				endNodeRecord.insert(it->mNode, it->mConnection, it->mCostSoFar);

				//If our route is no better, then skip
				if (endNodeRecord.mCostSoFar <= endNodeCost)
				{
					continue;
				}

			}
			//Otherwise we know we;ve got an unvisited node, so make a record for it
			else
			{
				endNodeRecord = {};
				endNodeRecord.mNode = endNode;

			}

			//We're here if we need to update the node
			//Update the cost, estimate, and connection
			endNodeRecord.mCostSoFar = endNodeCost;
			endNodeRecord.mConnection = currentConnection;

			//And add it to the open list
			if (!containedInOpenList)
			{
				nodesToVisit.push(endNodeRecord);
			}

		}
		//We've finished looking at the connections for the current node, so add
		//it to the closed list and remove it from the open list
		nodesToVisit.remove(currentRecord);
		visitedNodes.push(currentRecord);
		mVisitedNodes.push_back(currentRecord.mNode);

	}
	//We're here if we've either found the goal, or if we've no more nodes to
	//search, find which
	if (currentRecord.mNode != pTo)
	{
		return NULL;

	}
	else
	{
		Path* finalPath = new Path();
		//Compile the list of connections in the path
		//Work back along the path, accumulating connections
		while (currentRecord.mNode != pFrom)
		{
			pPath->addNode(currentRecord.mNode);

			currentRecord.mNode = currentRecord.mConnection->getFromNode();	

			PriorityQueue <NodeRecord, std::vector<NodeRecord>, CompareCost>::const_iterator it;
			
			it = visitedNodes.contains(currentRecord);

			if (it != visitedNodes.end())
			{
				currentRecord.mConnection = it->mConnection;
			}
		}
		int size = finalPath->getNumNodes();
		for (int i = 0; i < size; i++)
		{
			//output path
			pPath->addNode(finalPath->getAndRemoveNextNode());
		}

		delete finalPath;
	}

	//Performance tracking
	gpPerformanceTracker->stopTracking("path");
	mTimeElapsed = gpPerformanceTracker->getElapsedTime("path");

	//Set visual grid path to path
	#ifdef VISUALIZE_PATH
	mpPath = pPath;
	#endif

	//Return path
	return pPath;

}


