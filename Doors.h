#pragma once

#include "Coordinates.h"
#include "vectory.h"

class Door
{
public:
	Door(COORD, bool = true);
	~Door();
private:
	bool locked;
	COORD location;
};