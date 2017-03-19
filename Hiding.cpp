#include "Hiding.h"

HidingSpot::HidingSpot(COORD2 loc)
{
	location = loc;
}

float HidingSpot::getX() const
{
	return location.X;
}

float HidingSpot::getY() const
{
	return location.Y;
}

COORD2 HidingSpot::getCOORD() const
{
	return location;
}

HidingSpot::~HidingSpot()
{

}