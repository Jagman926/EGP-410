#include "PathfinderTypeMessage.h"
#include "DepthFirstPathfinder.h"
#include "DijkstraPathfinder.h"
#include "AStarPathfinder.h"
#include "GridPathfinder.h"
#include "Game.h"
#include "GameApp.h"
#include "GameMessage.h"

PathfinderTypeMessage::PathfinderTypeMessage(char pathType)
	:GameMessage(PATHFINDER_TYPE_MESSAGE)
{
	mTypeChange = true;
	mCurrentPathType = pathType;
}

PathfinderTypeMessage::~PathfinderTypeMessage()
{

}

void PathfinderTypeMessage::process()
{
	if (mTypeChange)
	{
		GameApp* pGame = dynamic_cast<GameApp*>(gpGame);
		switch (mCurrentPathType)
		{
		case 'f':
			//std::cout << "DepthFirst" << std::endl;
			pGame->setPathfinder(mCurrentPathType);
			break;
		case 'd':
			//std::cout << "Dijkstra" << std::endl;
			pGame->setPathfinder(mCurrentPathType);
			break;
		case 'a':
			//std::cout << "A*" << std::endl;
			pGame->setPathfinder(mCurrentPathType);
			break;
		default:
			break;
		}
	}
}
