#include "Electronics.h"

SmallElectric::SmallElectric(float x, float y, int emp)
{
	setEMP(emp);
	setCOORD(x, y);
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

void SmallElectric::setCOORD(float x, float y)
{
	location.X = x;
	location.Y = y;
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

BigElectric::BigElectric(float x, float y, int emp)
{
	setCOORD(x, y);
	setEMP(emp);
}

BigElectric::BigElectric()
{

}

BigElectric::~BigElectric()
{
	//destroy
}