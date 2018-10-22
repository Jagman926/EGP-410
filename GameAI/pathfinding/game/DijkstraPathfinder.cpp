#include "DijkstraPathfinder.h"
#include "Path.h"
#include "Connection.h"
#include "GridGraph.h"
#include "Game.h"
#include "PriorityQueue.h"
#include <PerformanceTracker.h>
#include <functional>
#include <list>
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

	//Initialize the record for the start node
	NodeRecord startRecord;
	startRecord.mNode = pFrom;
	startRecord.mConnection = nullptr;
	startRecord.mCostSoFar = 0;
	startRecord.mEstimatedTotalCost = 1; //FIX HEURISTIC FOR A*

	//Initialize the open and closed lists
	PriorityQueue<NodeRecord, std::vector<NodeRecord>, CompareEstimatedCost> nodesToVisit;
	nodesToVisit.push(startRecord);

	//Reset and clear path
	#ifdef VISUALIZE_PATH
	delete mpPath;
	mVisitedNodes.clear();
	mVisitedNodes.push_back(pFrom);
	#endif

	//create Path
	Path* pPath = new Path();
	
	//Initiate current node
	NodeRecord currentNode;

	//Iterate through processing each node
	while (!nodesToVisit.empty())
	{
		//Find smallest element in the open list
		currentNode = nodesToVisit.top();

		//If it is the goal node, then terminate
		if (currentNode.mNode == pTo)
		{
			break;
		}

		//Otherwise get its outgoing connections
		std::vector<Connection*> connections = mpGraph->getConnections(currentNode.mNode->getId());

		//Loop through each connecto=ion in turn
		for (unsigned int i = 0; i < connections.size(); i++)
		{
			Connection* connection = connections[i];
			Node* endNode = connections[i]->getToNode();

			//Get the estimate for the end node
			float endNodeCost = currentNode.mCostSoFar + connection->getCost();
			NodeRecord endNodeRecord;
			float endNodeHeuristic;

			//Create queue check
			NodeRecord queueCheck = {};
			queueCheck.mNode = endNode;

			//If the node is closed we may have to skip, or remove it from the closed list
			if (std::find(mVisitedNodes.begin(), mVisitedNodes.end(), endNode) != mVisitedNodes.end())
			{
				//Here we find the record in the closed list corresponding to the endNode
				endNodeRecord.mNode = *std::find(mVisitedNodes.begin(), mVisitedNodes.end(), endNode);

				//If we didn't find a shorter route, skip
				if (endNodeRecord.mCostSoFar <= endNodeCost)
				{
					continue;
				}

				//Otherwise remove it from the closed list
				mVisitedNodes.erase(std::find(mVisitedNodes.begin(), mVisitedNodes.end(), endNode));

				//We can use the node's old cost values to calculate its heuristic without
				//calling the possibly expensive heuristic finction
				endNodeHeuristic = 1; //FIX HEURISTIC FOR A*
			}
			//Skip if the node is open and we've not found a better route
			else if (nodesToVisit.contains(queueCheck))
			{
				//Here we find the record in the open list corresponding to the endNode
				endNodeRecord = *std::find(nodesToVisit.begin(), nodesToVisit.end(), queueCheck);

				//If our route is no better, then skip
				if (endNodeRecord.mCostSoFar <= endNodeCost)
				{
					continue;
				}

				//We can use the node's old cost values to calculate its heuristic without
				//calling the possibly expensive heuristic finction
				endNodeHeuristic = 1; //FIX HEURISTIC FOR A*
			}
			//Otherwise we know we;ve got an unvisited node, so make a record for it
			else
			{
				endNodeRecord.mNode = endNode;

				//We'll need to calculate the heuristic value using the function, since
				//we don't have an existing record to use
				endNodeHeuristic = 1; //FIX HEURISTIC FOR A*
			}
			//We're here if we need to update the node
			//Update the cost, estimate, and connection
			endNodeRecord.mCost = endNodeCost;
			endNodeRecord.mConnection = connection;
			endNodeRecord.mEstimatedTotalCost = endNodeCost + endNodeHeuristic;

			//And add it to the open list
			if (nodesToVisit.contains(queueCheck))
			{
				nodesToVisit.push(endNodeRecord);
			}
		}
		//We've finished looking at the connections for the current node, so add
		//it to the closed list and remove it from the open list
		nodesToVisit.remove(currentNode);
		#ifdef VISUALIZE_PATH
		mVisitedNodes.push_back(currentNode.mNode);
		#endif
	}
	//We're here if we've either found the goal, or if we've no more nodes to
	//search, find which
	if (currentNode.mNode != pTo)
	{
		return nullptr;
	}
	else
	{
		//Compile the list of connections in the path
		//Work back along the path, accumulating connections
		while (currentNode.mNode != pFrom)
		{
			pPath->addNode(currentNode.mNode);
			currentNode.mNode = currentNode.mConnection->getFromNode();			
		}
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

float DijkstraPathfinder::heuristic(Vector2D a, Vector2D b)
{
	//Manhattan diatance on a square grid
	return abs(a.getX() - b.getX()) + abs(a.getY() - b.getY());
}


