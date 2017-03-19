#include "Characters.h"
#include <iostream>
#include <cmath>

#define pi 3.141592654

KeyHolder::KeyHolder(float x, float y)
{
	flashlight = true; //sets keyholder flashlight to true
	key = true; //sets the keyholder guard's key stat to true
	setCoord(x, y); //sets keyholder location
}

KeyHolder::KeyHolder()
{
	key = true; //sets default keyholder to 
	flashlight = true;
}

bool KeyHolder::FOV(COORD2 a_player) //this is where the magic is
{
	if (flashlight == true) //while the flashlight is lit, then the enemy can spot the player
	{
		vec2 view(enemy.X - a_player.X, enemy.Y - a_player.Y);
		float magnitude = view.getMagnitude(view); //declared in vectory.cpp
		float angle = view.getAngle(view, direction); //also in vectory.cpp
		if (magnitude <= 210 && (angle < (27 * pi) / 180 && angle > -(27 * pi) / 180))	//this is the magic, if the player exists
		{																				//within a certain range of angles
			key = false;																//that add up to a 60 degree FOV
			return true;																//and about 20 (pixels probably?)
		}																				//also, the key is destroyed upon a keyholder seeing the player
		else																			//If not, then the enemy has not seen the player
		{																				//thus, nothing happens
			return false;																//and these comments are useless
		}
	}
	else
	{
		return false;																//Hello World!Press any key to continue...
	}
}

bool Guard::FOV(COORD2 a_player) //this is where the magic is
{
	if (flashlight == true) //while the flashlight is lit, then the enemy can spot the player
	{
		vec2 view(enemy.X - a_player.X, enemy.Y - a_player.Y);
		float magnitude = view.getMagnitude(view); //declared in vectory.cpp
		float angle = view.getAngle(view, direction); //also in vectory.cpp
		if (magnitude <= 200 && (angle < (27 * pi) 
			/ 180 && angle > -(27 * pi) / 180))	//this is the magic, if the player exists
		{										//within a certain range of angles
			return true;						//that add up to a 54 degree FOV
		}										//and about 200 pixels
		else									//also, the key is destroyed upon a keyholder seeing the player
		{										//If not, then the enemy has not seen the player
			return false;						//thus, nothing happens
		}										//and these comments are useless
	}
	else
	{
		return false;							//Hello World!Press any key to continue...
	}
}

bool Player::FOV(COORD2 a_player)
{
	if (flashlight == true)
	{
		vec2 view(player.X - a_player.X, player.Y - a_player.Y);
		float magnitude = view.getMagnitude(view); //declared in vectory.cpp
		if (magnitude <= 40)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
		return false;
}

void KeyHolder::setCoord(float x, float y) //sets up the enemy's location based on the system's input
{
	enemy.X = x;
	enemy.Y = y;
}

COORD2 KeyHolder::getCoord() const //returns the whole enemy coordinate, might not be needed
{
	return enemy;
}

float KeyHolder::getX() const	//returns only the enemy's X value
{							//believe me, it's more efficient
	return enemy.X;
}

float KeyHolder::getY() const //returns only the enemy's Y value location
{							//trust
	return enemy.Y;
}

void KeyHolder::setDirection(float x, float y) //sets the direction, based on what is set by the system
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

Guard::Guard(float x, float y)
{
	flashlight = true;
	key = false;
	setCoord(x, y);
}

Player::Player() //the player will never have a true flashlight, but could have a true key, depending on stealthiness
{
	key = false;
	flashlight = false;
	EMP = 1;
}

Player::~Player()
{
	//do absolutely NOTHING here. EVER!!!
}

void Player::setCoord(float x, float y) //assigns the Coordinates of the player using a custom structure
{
	player.X = x;
	player.Y = y;
}

void Player::pickPocket(KeyHolder &enemy) //allows the player to steal the key of the nearest enemy with a key
{
	if (FOV(enemy.getCoord()) == true)
	{
		if (enemy.key == true)
		{
			key = true;
			enemy.key = false;
		}
		else
		{
			return;
		}
	}
	else
	{
		return;
	}
}

void Player::useEMP(std::vector<KeyHolder*> &guards)
{
	if (EMP > 0 && !EMPuse)
	{
		for (unsigned int i = 0; i < guards.size(); i++)
		{
			guards[i]->flashlight = false;
		}
		EMPuse = true;
		EMP--;
		return;
	}
	else
	{
		return;
	}
}

void Player::openLock(bool &doorlock)
{
	if (doorlock)
	{
		doorlock = false;
		key = false;
	}
	else
	{

	}
}

void Player::addEMP(SmallElectric &device) //adds the EMP to the player depending on the location (only at techy stuff)
{
	EMP += device.getEMP();
	device.setEMP();
}


COORD2 Player::getCoord() const //returns the player's location
{
	return player;
}

int Player::getEMP()
{
	return EMP; //returns number of emps
}

void Player::setEMP(bool use)
{
	EMPuse = use;
}

bool Player::returnEMP() const
{
	return EMPuse;
}

float Player::getX() const //returns only the X value of the player's location
{						 //believe me, it IS more efficient this way
	return player.X;
}

float Player::getY() const //returns only the Y value of the location, for the reasons listed above
{						 //trust
	return player.Y;
}

bool Player::getHiding() const
{
	return hiding;
}

void Player::setHiding(bool hide)
{
	hiding = hide;
}

void Player::Hide(std::vector<HidingSpot*> spots)
{
	for (int i = 0; i < spots.size(); i++)
	{
		vec2 distance(player.X - spots[i]->getX(),
			player.Y - spots[i]->getY());
		float magnitude = distance.getMagnitude(distance);
		if (magnitude < 50)
		{
			hiding = true;
			player = spots[i]->getCOORD();
			break;
		}
		else
		{
			hiding = false;
			//make an incredible amount of stuff happen in the UI
		}
	}
}