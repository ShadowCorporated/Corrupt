#include "Electronics.h"

SmallElectric::SmallElectric(COORD2 a_location, int emp)
{
	setEMP(emp);
	setCOORD(a_location);
}

SmallElectric::SmallElectric()
{

}

SmallElectric::~SmallElectric()
{

}

void SmallElectric::setEMP(int emp)
{
	countEMP = emp;
}

void SmallElectric::setCOORD(COORD2 a_location)
{
	location = a_location;
}

int SmallElectric::getEMP() const
{
	return countEMP;
}

COORD2 SmallElectric::getCOORD() const
{
	return location;
}

float SmallElectric::getX() const
{
	return location.X;
}

float SmallElectric::getY() const
{
	return location.Y;
}

BigElectric::BigElectric(COORD2 b_location, int emp)
{
	setCOORD(b_location);
	setEMP(emp);
}

BigElectric::BigElectric()
{

}

BigElectric::~BigElectric()
{
	//destroy
}