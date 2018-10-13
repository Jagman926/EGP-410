/*main.cpp
	*
	*	Dean Lawson
	*	Champlain College
	*	2011
	*
	*/
#include <cstdlib>
#include <ctime>
#include <crtdbg.h>

#include <SDL.h>

#include "Game.h"
#include "GameApp.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "Defines.h"
#include <Timer.h>
#include <MemoryTracker.h>
#include <PerformanceTracker.h>

using namespace std;

PerformanceTracker* gpPerformanceTracker = NULL;

int main(int argc, char **argv)
{
	gpPerformanceTracker = new PerformanceTracker();
	gpPerformanceTracker->startTracking("init");

	gpGame = new GameApp();

	gpGame->init();

	gpPerformanceTracker->stopTracking("init");
	cout << "initialization took:" << gpPerformanceTracker->getElapsedTime("init") << "ms\n";

	bool shouldExit = false;

	while( !shouldExit )
	{
		gpPerformanceTracker->clearTracker("loop");
		gpPerformanceTracker->startTracking("loop");

		gpGame->beginLoop();

		gpPerformanceTracker->clearTracker("draw");
		gpPerformanceTracker->startTracking("draw");

		gpGame->processLoop();

		gpPerformanceTracker->stopTracking("draw");

		shouldExit = gpGame->endLoop();

		gpPerformanceTracker->stopTracking("loop");
		//cout << "loop took:" << gpPerformanceTracker->getElapsedTime("loop") << "ms";
		//cout << "draw took:" << gpPerformanceTracker->getElapsedTime("draw") << "ms\n";
	}

	//cleanup
	gpGame->cleanup();
	delete gpGame;
	delete gpPerformanceTracker;

	MemoryTracker::getInstance()->reportAllocations(cout);
	system("pause");

	return 0;
}

