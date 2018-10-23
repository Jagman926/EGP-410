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
	//
	Path* findPath(Node* pFrom, Node* pTo);

private:
	//Heuristic struct
	struct Heuristic
	{
		Node* toNode;
		Vector2D toNodePos;

		void setGoal(Node* goal)
		{
			//Set toNode
			toNode = goal;
			//Get toNode Position
			GameApp * pGame = dynamic_cast<GameApp*>(gpGame);
			toNodePos = pGame->getGrid()->getULCornerOfSquare(toNode->getId());
		};

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
