#pragma once
#include "Coordinates.h"

class HidingSpot
{
public:
	HidingSpot(COORD2);
	~HidingSpot();

	float getX() const;
	float getY() const;

	COORD2 getCOORD() const;
protected:
	COORD2 location;
};