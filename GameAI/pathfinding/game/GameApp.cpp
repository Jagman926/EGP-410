#include "Game.h"
#include "GameApp.h"
#include "InputManager.h"
#include "GameMessageManager.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "GraphicsBufferManager.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Grid.h"
#include "GridGraph.h"
#include "Connection.h"
#include "Path.h"
#include "AStarPathfinder.h"
#include "DijkstraPathfinder.h"
#include "DepthFirstPathfinder.h"
#include "Pathfinder.h"
#include "GridPathfinder.h"
#include "GridVisualizer.h"
#include "DebugDisplay.h"
#include "PathfindingDebugContent.h"

#include <Vector2D.h>
#include <SDL.h>
#include <fstream>
#include <vector>

const int GRID_SQUARE_SIZE = 32;
const std::string gFileName = "pathgrid.txt";

GameApp::GameApp()
:mpMessageManager(NULL)
,mpInputManager(NULL)
,mpGrid(NULL)
,mpGridGraph(NULL)
,mpPathfinder(NULL)
,mpDebugDisplay(NULL)
{
}

GameApp::~GameApp()
{
	cleanup();
}

bool GameApp::init()
{
	bool retVal = Game::init();
	if( retVal == false )
	{

		return false;
	}

	//Init Input and Message Managers
	mpMessageManager = new GameMessageManager();
	mpInputManager = new InputManager();

	//create and load the Grid, GridBuffer, and GridRenderer
	mpGrid = new Grid(mpGraphicsSystem->getWidth(), mpGraphicsSystem->getHeight(), GRID_SQUARE_SIZE);
	mpGridVisualizer = new GridVisualizer( mpGrid );
	std::ifstream theStream( gFileName );
	mpGrid->load( theStream );

	//create the GridGraph for pathfinding
	mpGridGraph = new GridGraph(mpGrid);
	//init the nodes and connections
	mpGridGraph->init();
	//Init current pathfinder type
	mpPathfinder = new DijkstraPathfinder(mpGridGraph);

	//load buffers
	mpGraphicsBufferManager->loadBuffer(mBackgroundBufferID, "wallpaper.bmp");

	//setup sprites
	GraphicsBuffer* pBackGroundBuffer = mpGraphicsBufferManager->getBuffer( mBackgroundBufferID );
	if( pBackGroundBuffer != NULL )
	{
		mpSpriteManager->createAndManageSprite( BACKGROUND_SPRITE_ID, pBackGroundBuffer, 0, 0, (float)pBackGroundBuffer->getWidth(), (float)pBackGroundBuffer->getHeight() );
	}

	//debug display
	PathfindingDebugContent* pContent = new PathfindingDebugContent( mpPathfinder, 'd');
	mpDebugDisplay = new DebugDisplay( Vector2D(0,12), pContent );

	mpMasterTimer->start();
	return true;
}

void GameApp::cleanup()
{
	delete mpInputManager;
	mpInputManager = NULL;

	delete mpMessageManager;
	mpMessageManager = NULL;

	delete mpGrid;
	mpGrid = NULL;

	delete mpGridVisualizer;
	mpGridVisualizer = NULL;

	delete mpGridGraph;
	mpGridGraph = NULL;

	delete mpPathfinder;
	mpPathfinder = NULL;

	delete mpDebugDisplay;
	mpDebugDisplay = NULL;
}

void GameApp::beginLoop()
{
	//should be the first thing done
	Game::beginLoop();
}

void GameApp::processLoop()
{
	//get back buffer
	GraphicsBuffer* pBackBuffer = mpGraphicsSystem->getBackBuffer();

	//copy to back buffer
	mpGridVisualizer->draw( *pBackBuffer );

	//show pathfinder visualizer
	#ifdef VISUALIZE_PATH
	mpPathfinder->drawVisualization(mpGrid, pBackBuffer);
	#endif

	//Update inputs
	mpInputManager->update();

	//Flip backbuffer
	mpDebugDisplay->draw( pBackBuffer );

	//Process messages for frame
	mpMessageManager->processMessagesForThisframe();

	//should be last thing in processLoop
	Game::processLoop();
}

bool GameApp::endLoop()
{
	return Game::endLoop();
}

//Sets new path for pathfinder from PathfinderTypeMessage. Also resets pathfinder content
//and Debug Display so that the previous path is removed
void GameApp::setPathfinder(char pathType)
{
	//Set new pathfinder
	switch (pathType)
	{
	case 'f':
		delete mpPathfinder;
		mpPathfinder = new DepthFirstPathfinder(mpGridGraph);
		break;
	case 'd':
		delete mpPathfinder;
		mpPathfinder = new DijkstraPathfinder(mpGridGraph);
		break;
	case 'a':
		delete mpPathfinder;
		mpPathfinder = new AStarPathfinder(mpGridGraph);
		break;
	default:
		break;
	}
	//debug display
	delete mpDebugDisplay;
	PathfindingDebugContent* pContent = new PathfindingDebugContent(mpPathfinder, pathType);
	mpDebugDisplay = new DebugDisplay(Vector2D(0, 12), pContent);
}
