#pragma once

#include "Coordinates.h"
#include "vectory.h"

class Door
{
public:
	Door(COORD2, bool = true);
	~Door();
private:
	bool locked;
	COORD2 location;
};