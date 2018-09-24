#pragma once
#include <sstream>

#include "GameMessage.h"
#include "Vector2D.h"

class Vector2D;

class OutputMouseCoordsMessage :public GameMessage
{
public:
	OutputMouseCoordsMessage(const Vector2D& pos);
	~OutputMouseCoordsMessage();

	void process();

private:
	Vector2D mPos;
};
