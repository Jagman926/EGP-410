#include "AStarPathfinder.h"
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

AStarPathfinder::AStarPathfinder(Graph * pGraph)
	:GridPathfinder(dynamic_cast<GridGraph*>(pGraph))
{
	#ifdef VISUALIZE_PATH
	mpPath = NULL;
	#endif
}

AStarPathfinder::~AStarPathfinder()
{
	#ifdef VISUALIZE_PATH
	delete mpPath;
	#endif
}

Path * AStarPathfinder::findPath(Node * pFrom, Node * pTo)
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
	PriorityQueue<NodeRecord, std::vector<NodeRecord>, CompareEstimatedCost> nodesToVisit, visitedNodes;
	//endNode variables
	Node* endNode;
	float endNodeHeuristic, endNodeCost;
	//Node records
	NodeRecord currentRecord = {}, endNodeRecord = {};

	//Set heuristic goal
	mHeuristic.setGoal(pTo);

	//Initialize the record for the start node
	NodeRecord startRecord = {};
	startRecord.mNode = pFrom;
	startRecord.mConnection = nullptr;
	startRecord.mCostSoFar = 0;
	startRecord.mEstimatedTotalCost = mHeuristic.getHeuristic(pFrom);

	//Add start to open queue
	nodesToVisit.push(startRecord);

	//Iterate through processing each node
	while (currentRecord.mNode != pTo && nodesToVisit.size() > 0)
	{
		//Find smallest element in the open list and pop
		currentRecord = nodesToVisit.top();
		nodesToVisit.pop();

		//If it is the goal node, then terminate
		if (currentRecord.mNode == pTo)
		{
			break;
		}

		//Otherwise get its outgoing connections
		std::vector<Connection*> connections = mpGraph->getConnections(currentRecord.mNode->getId());

		//Loop through each connection in turn
		for (unsigned int i = 0; i < connections.size(); i++)
		{
			bool inVisitedQueue = false;
			Connection* currentConnection = connections[i];

			//get end node and cost
			endNode = currentConnection->getToNode();
			endNodeCost = currentRecord.mCostSoFar + currentConnection->getCost();

			//Create queue check
			NodeRecord tmpRecord = {};
			tmpRecord.mNode = endNode;

			//Create iterator to check if contained in queues
			PriorityQueue <NodeRecord, std::vector<NodeRecord>, CompareEstimatedCost>::const_iterator itVisited, itToVisit;
			itVisited = visitedNodes.contains(tmpRecord);
			itToVisit = nodesToVisit.contains(tmpRecord);

			//If the node is closed we may have to skip, or remove it from the closed list
			if (itVisited != visitedNodes.end())
			{
				//Here we find the record in the closed list corresponding to the endNode
				endNodeRecord.insert(itVisited->mNode, itVisited->mConnection, itVisited->mCostSoFar, itVisited->mEstimatedTotalCost);

				//If route is worse, then skip
				if (endNodeRecord.mCostSoFar <= endNodeCost)
				{
					continue;
				}

				//Otherwise remove it from the closed list
				visitedNodes.remove(endNodeRecord);

				//We can use the node's old cost values to calculate its heuristic without
				//calling the possibly expensive heuristic finction
				endNodeHeuristic = endNodeRecord.mEstimatedTotalCost - endNodeRecord.mCostSoFar;

			}
			//Skip if the node is open and we've not found a better route
			else if (itToVisit != nodesToVisit.end())
			{
				//in visited queue true
				inVisitedQueue = true;

				//Here we find the record in the open list corresponding to the endNode
				endNodeRecord.insert(itToVisit->mNode, itToVisit->mConnection, itToVisit->mCostSoFar, itToVisit->mEstimatedTotalCost);

				//If our route is no better, then skip
				if (endNodeRecord.mCostSoFar <= endNodeCost)
				{
					continue;
				}

				//We can use the node's old cost values to calculate its heuristic without
				//calling the possibly expensive heuristic finction
				endNodeHeuristic = endNodeRecord.mConnection->getCost() - endNodeRecord.mCostSoFar;

			}
			//Otherwise we know we've got an unvisited node, so make a record for it
			else
			{
				endNodeRecord = {};
				endNodeRecord.mNode = endNode;
				endNodeHeuristic = mHeuristic.getHeuristic(endNode);

			}

			//We're here if we need to update the node
			//Update the cost, estimate, and connection
			endNodeRecord.mCostSoFar = endNodeCost;
			endNodeRecord.mConnection = currentConnection;
			endNodeRecord.mEstimatedTotalCost = endNodeCost + endNodeHeuristic;

			//And add it to the open list
			if (!inVisitedQueue)
			{
				nodesToVisit.push(endNodeRecord);
			}

		}
		//We've finished looking at the connections for the current node, so add
		//it to the closed list and remove it from the open list
		nodesToVisit.remove(currentRecord);
		visitedNodes.push(currentRecord);
		#ifdef VISUALIZE_PATH
		mVisitedNodes.push_back(currentRecord.mNode);
		#endif

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
			//Add node to path
			pPath->addNode(currentRecord.mNode);
			//Get connection from
			currentRecord.mNode = currentRecord.mConnection->getFromNode();

			//Create iterator to check visited queue
			PriorityQueue <NodeRecord, std::vector<NodeRecord>, CompareCost>::const_iterator it;
			it = visitedNodes.contains(currentRecord);

			if (it != visitedNodes.end())
			{
				//Set connection to visited connection
				currentRecord.mConnection = it->mConnection;
			}
		}
		//Revere path for output
		int size = finalPath->getNumNodes();
		for (int i = 0; i < size; i++)
		{
			//output path
			pPath->addNode(finalPath->getAndRemoveNextNode());
		}

		//Cleanup path
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