#pragma once
#include "Coordinates.h"

class World_Collision
{
public:
	World_Collision(float x, float y, float width, float height);
	World_Collision();
	void setCoord(float x, float y); //set the coordinate of platform/wall/floor/misc...
	void setWidth(float w);
	void setHeight(float h);
	COORD2 getCoord() const; // returns coordinates of said object

	float getX() const;
	float getY() const;
	float getWidth() const;
	float getHeight() const;

	~World_Collision();
private:
	COORD2 World; //coordinates of world objects
	float width;
	float height;
};