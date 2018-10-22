#include "PathfindingDebugContent.h"
#include "GridPathfinder.h"
#include "Path.h"
#include <sstream>

using namespace std;

PathfindingDebugContent::PathfindingDebugContent( GridPathfinder* pPathfinder, char currentPathfinderType )
	:mpPathfinder(pPathfinder)
	,currentPathfinderType(currentPathfinderType)
{
}

string PathfindingDebugContent::getDebugString()
{
	stringstream theStream;

#ifdef VISUALIZE_PATH
	if( mpPathfinder->mpPath != NULL )
	{
		switch (currentPathfinderType)
		{
		case 'f':
			theStream << "DepthFirst | ";
			break;
		case 'd':
			theStream << "Dijkstra | ";
			break;
		case 'a':
			theStream << "A* | ";
			break;
		default:
			break;
		}

		theStream << "Pathlength:"<< mpPathfinder->mpPath->getNumNodes();
	}
	
	theStream << "  Num Nodes Processed:" << mpPathfinder->mVisitedNodes.size();
#endif
	theStream << "  Elapsed Time:" << mpPathfinder->mTimeElapsed;
	return theStream.str();
}

