#include "Game.h"
#include "GraphicsSystem.h"
#include "GameMessageManager.h"
#include "OutputMouseCoordsMessage.h"
#include "UnitManager.h"

OutputMouseCoordsMessage::OutputMouseCoordsMessage(const Vector2D& pos)
	:GameMessage(OUTPUT_MOUSE_COORDS)
	, mPos(pos)
{
}

OutputMouseCoordsMessage::~OutputMouseCoordsMessage()
{
}

void OutputMouseCoordsMessage::process()
{
	std::stringstream mousePos;
	mousePos << mPos.getX() << ":" << mPos.getY();
	gpGame->getGraphicsSystem()->writeText(*gpGame->getFont(), (float)mPos.getX(), (float)mPos.getY(), mousePos.str(), BLACK_COLOR);
}