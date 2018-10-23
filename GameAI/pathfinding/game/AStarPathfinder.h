#ifndef A_STAR_PATHFINDER
#define A_STAR_PATHFINDER

#include "GameApp.h"
#include "GridPathfinder.h"
#include "Grid.h"
#include "Node.h"
#include <vector>
#include <Vector2D.h>

class Path;
class Graph;
class GraphicsBuffer;
class Grid;
class Connection;

class AStarPathfinder : public GridPathfinder
{
public:
	AStarPathfinder(Graph *pGraph);
	~AStarPathfinder();
	
	//Finds path from starting node (pFrom) to the goal node (pTo) using a heuristic
	//based on linear distance. Will return a path through a visual grid when complete
	Path* findPath(Node* pFrom, Node* pTo);

private:
	//Heuristic struct which holds information for the 
	//heuristic being added to nodes
	struct Heuristic
	{
		Node* toNode;
		Vector2D toNodePos;

		//Sets goal for the heuristic to make its estimate off of
		void setGoal(Node* goal)
		{
			//Set toNode
			toNode = goal;
			//Get toNode Position
			GameApp * pGame = dynamic_cast<GameApp*>(gpGame);
			toNodePos = pGame->getGrid()->getULCornerOfSquare(toNode->getId());
		};

		//Gets the heuristic value give the current node. Currently returs a linear
		//distance heuristic, but a manhatten distance heuristic is included
		float getHeuristic(Node* node)
		{
			Vector2D currentNodePos;
			//Get currentNode Position
			GameApp * pGame = dynamic_cast<GameApp*>(gpGame);
			currentNodePos = pGame->getGrid()->getULCornerOfSquare(node->getId());

			//Heuristic Types
			//----------------------

			//Manhattan distance on a square grid
			//return abs(nodePos.getX() - goalPos.getX()) + abs(nodePos.getY() - goalPos.getY());

			//Linear distance
			return (currentNodePos - toNodePos).getLength();
		};
	} mHeuristic;

};

#endif // !A_STAR_PATHFINDER
