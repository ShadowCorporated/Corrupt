#pragma once

#include "Coordinates.h"

class SmallElectric
{
public:
	SmallElectric(COORD2, int = 1);
	SmallElectric();

	void setEMP(int = 0);
	int getEMP() const;

	void setCOORD(COORD2);
	COORD2 getCOORD() const;

	float getX() const;
	float getY() const;

	~SmallElectric();
private:
	int countEMP;
	COORD2 location;
};

class BigElectric : public SmallElectric
{
public:
	BigElectric(COORD2, int = 2);
	BigElectric();

	~BigElectric();
private:
	int countEMP;
	COORD2 location;
};