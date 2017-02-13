#include "World Collision.h"
#include "Characters.h"

World_Collision::World_Collision(float x, float y, float width, float height)
{
	setCoord(x, y); //set location
	setWidth(width); //set width
	setHeight(height); //set height
}

World_Collision::World_Collision()
{
	//nothing, default
}

void World_Collision::setCoord(float x, float y)
{
	World.X = x;
	World.Y = y;
}

void World_Collision::setWidth(float w)
{
	width = w;
}

void World_Collision::setHeight(float h)
{
	height = h;
}

COORD2 World_Collision::getCoord() const
{
	return World;
}

float World_Collision::getX() const
{
	return World.X;
}

float World_Collision::getY() const
{
	return World.Y;
}

float World_Collision::getWidth() const
{
	return width;
}

float World_Collision::getHeight() const
{
	return height;
}

World_Collision::~World_Collision()
{
}


