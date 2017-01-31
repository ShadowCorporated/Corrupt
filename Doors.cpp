#include "Doors.h"

Door::Door(COORD locat, bool lock)
{
	locked = lock;
	location = locat;
}

Door::~Door()
{
	//break down the doors
}