#pragma once

#include "Coordinates.h"
#include "vectory.h"
#include "Doors.h"
#include <vector>

struct Character
{
	bool flashlight; //guards equal true intil useEMP()
	bool key; //if the player/enemy has a key = true
};

class KeyHolder : public Character
{
public:
	KeyHolder(float x, float y);
	KeyHolder();
	bool fieldOfView(COORD2 player); //calculates if the player is within the enemies FOV

	void setCoord(float x, float y); //sets up the enemies' coordinates on the plane
	COORD2 getCoord() const; //returns the enemy Coordinates

	void setDirection(float x, float y); //sets the direction of vision vector of the enemies
	vec2 getDirection() const; //returns that selfsame vector, might not be needed, might be deleted later

	float getX() const; //gets only the X coordinate
	float getY() const; //gets only the y coordinate
protected:
	vec2 direction; //the direction of the enemies' line of sight
	COORD2 enemy; //the coordinates of the enemy
	bool left;
};

class Guard : public KeyHolder //for the FOV functionality, hell yeah!
{
public:
	Guard(float x, float y); //different declaration of subtype of Keyholder. Guard.key = false
	Guard();
};

class Player : public Character
{
public:
	Player();
	void pickPocket(bool &enemykey); //allows the player to steal keys
	void openLock(bool &doorlock); //allows the player to unlock doors

	void setCoord(float x, float y); //sets the player position on the map
	void addEMP( int ); //adds EMP's to the player inventory
	void useEMP(std::vector<KeyHolder>&); //lets the player use EMPs to knock out enemy lights

	COORD2 getCoord() const; //returns the coordinate of the player

	float getX() const; //returns the x value of the player coordinate
	float getY() const; //returns the y value of the player coordinate
	~Player(); //destroys the player
private:
	int EMP; //contains the number of EMP's the player is holding
	COORD2 player; //contain's the player coordinates
};