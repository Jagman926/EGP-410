#pragma once

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
	struct PathHeuristic
	{
		Node* goalNode;
		Vector2D goalPos;

		void setGoal(Node* goal)
		{
			goalNode = goal;
			GameApp * pGame = dynamic_cast<GameApp*>(gpGame);
			goalPos = pGame->getGrid()->getULCornerOfSquare(goalNode->getId());
		};

		float estimate(Node* node)
		{
			Vector2D nodePos;
			GameApp * pGame = dynamic_cast<GameApp*>(gpGame);
			nodePos = pGame->getGrid()->getULCornerOfSquare(node->getId());
			//Manhattan diatance on a square grid
			return abs(nodePos.getX() - goalPos.getX()) + abs(nodePos.getY() - goalPos.getY());
		};
	} mHeuristic;

};
