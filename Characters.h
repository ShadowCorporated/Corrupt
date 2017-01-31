#pragma once

#include "Coordinates.h"
#include "vectory.h"

struct Character
{
	bool flashlight;
	bool key;
};

class KeyHolder : public Character
{
public:
	KeyHolder(int x, int y);
	KeyHolder();
	bool fieldOfView(COORD player); //calculates if the player is within the enemies FOV

	void setCoord(int x, int y); //sets up the enemies' coordinates on the plane
	COORD getCoord() const; //returns the enemy Coordinates

	void setDirection(int x, int y); //sets the direction of vision vector of the enemies
	vec2 getDirection() const; //returns that selfsame vector, might not be needed, might be deleted later

	int getX() const; //gets only the X coordinate
	int getY() const; //gets only the y coordinate
private:
	vec2 direction; //the direction of the enemies' line of sight
	COORD enemy; //the coordinates of the enemy
};

class Guard : public KeyHolder //for the FOV functionality, hell yeah!
{
public:
	Guard(int x, int y); //different declaration of subtype of Keyholder. Guard.key = false
	Guard();
private:
	vec2 direction;
	COORD enemy;
};

class Player : public Character
{
public:
	Player();
	void pickPocket(bool &enemykey);
	void openLock(bool &doorlock);

	void setCoord(int x, int y);
	void addEMP();
	COORD getCoord() const;

	int getX() const;
	int getY() const;
	~Player();
private:
	int EMP;
	COORD player;
};