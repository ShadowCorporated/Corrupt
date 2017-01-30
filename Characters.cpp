#include "Characters.h"
#include <iostream>
#include <cmath>

#define pi 3.141592654

KeyHolder::KeyHolder(int x, int y)
{
	flashlight = true;
	key = true;
	setCoord(x, y);
}

KeyHolder::KeyHolder()
{
	key = true;
	flashlight = true;
}

bool KeyHolder::fieldOfView(COORD player) //this is where the magic is
{
	vec2 view(enemy.X - player.X, enemy.Y - player.Y);
	float magnitude = view.getMagnitude(view); //declared in vectory.cpp
	float angle = view.getAngle(view, direction); //also in vectory.cpp
	if (magnitude <= 20 && (angle < (30 * pi)/180 && angle > -(30 * pi)/180))	//this is the magic, if the player exists
	{																			//within a certain range of angles
		key = false;															//that add up to a 60 degree FOV
		std::cout << "Spotted" << std::endl;
		return true;															//and about 20 (pixels probably?)									
	}																			//also, the key is destroyed upon a keyholder seeing the player									
	else																		//If not, then the enemy has not seen the player		
	{																			//thus, nothing happens					
		std::cout << "Hidden" << std::endl;
		return false;															//and these comments are useless								
	}																			//Hello World! Press any key to continue...		
}

void KeyHolder::setCoord(int x, int y) //sets up the enemy's location based on the system's input
{
	enemy.X = x;
	enemy.Y = y;
}

COORD KeyHolder::getCoord() const //returns the whole enemy coordinate, might not be needed
{
	return enemy;
}

int KeyHolder::getX() const	//returns only the enemy's X value
{							//believe me, it's more efficient
	return enemy.X;
}

int KeyHolder::getY() const //returns only the enemy's Y value location
{							//trust
	return enemy.Y;
}

void KeyHolder::setDirection(int x, int y) //sets the direction, based on what is set by the system
{
	direction = vec2(x, y);
}

vec2 KeyHolder::getDirection() const //returns the vector of the direction a guard is looking
{
	return direction;
}

Guard::Guard()
{
	flashlight = true;
	key = false;
}

Guard::Guard(int x, int y)
{
	flashlight = true;
	key = false;
	setCoord(x, y);
}

Player::Player() //the player will never have a true flashlight, but could have a true key, depending on stealthiness
{
	key = false;
	flashlight = false;
}

Player::~Player()
{
	//do absolutely NOTHING here. EVER!!!
}

void Player::setCoord(int x, int y) //assigns the Coordinates of the player using a custom structure
{
	player.X = x;
	player.Y = y;
}

void Player::pickPocket(bool enemykey) //allows the player to steal the key of the nearest enemy with a key
{
	key = true;
	enemykey = false;
}

void Player::addEMP() //adds the EMP to the player depending on the location (only at techy stuff)
{
	EMP++;
}

COORD Player::getCoord() const //returns the player's location
{
	return player;
}

int Player::getX() const //returns only the X value of the player's location
{						 //believe me, it IS more efficient this way
	return player.X;
}

int Player::getY() const //returns only the Y value of the location, for the reasons listed above
{						 //trust
	return player.Y;
}