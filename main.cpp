#include "spritelib/spritelib.h"

#include <fstream>
#include <streambuf>
#include <vector>
#include <iostream>
#include "Characters.h"
#include "World Collision.h"
#include "timer.h"

using namespace spritelib;

//enum for animations
enum animation {
	EMP, PICKPOCKET, NOTHING
};

//initial animation
animation playeranim = NOTHING;

//various timer objects
SecondsTimer enemy1Turn, transitionTimer, EMPTimer;


//vector containers for platforms and ledges
std::vector<World_Collision*> platform;
std::vector<World_Collision*> ledges;

//vector container for guards
std::vector<KeyHolder*> guards;

//various sprites for game
Sprite mainCharacter, guard1, guard2, guard3, guard4, guard5, keyholder1, backGround, mainM, level, levelTwo, levelThree, eye, health, EMPicon, Chest, EMPterminal, useEMP, spotlight, spotlight2, keyIcon, keyGuard;
//door related sprites
Sprite doorNotice, door;
float dx = 935, dy = 289;
//sprites for flashlights, hidingscreen and control scheme
Sprite Flashlight, Flashlight2, Flashlight3, Flashlight4, hideScreen, controlScheme;
Sprite tab;
//variable for lives
int lives = 3;

//hidingspots
float hx1 = 770, hy1 = 40;
float hx2 = 1110, hy2 = 40;
float hx3 = 642, hy3 = 371;
float hx4 = 783, hy4 = 412;
float hx5 = 783, hy5 = 452;

//chest location
float chx = 1225, chy = 599.4;
//player object
Player player;
float x = 120.0f, y = 15.0f, h = 15, w = 0;

//keyholder object
KeyHolder keyhold1;
float kx = 638, ky = 72;
//enemy with flashlight objects
Guard enemy1, enemy2, enemy4, enemy5;
float ex, ey;
float ex2 = 275, ey2 = 366;
float ex3 = 935, ey3 = 395;
float ex5 = 1231, ey5 = 40;
float ex6 = 493, ey6 = 370;
float ex8 = 985, ey8 = 412;
float ex9 = 545, ey9 = 453;
//enemy with no flashlight object
Guard2 enemy3;
float ex4 = 450, ey4 = 158;
float ex7 = 800, ey7 = 190;
//spotlight objects
Spotlight spotLight1, spotLight2;
float sx = 293, sy = 434;
float sx2, sy2;
//terminal objects
SmallElectric terminal1(290, 276.3, 1);
float tx = 490, ty = 140;

//level booleans
bool mainMenu = true;
bool level1 = false;
bool level2 = false;
bool level3 = false;
bool won = false;

//bool for chest opening and key being taken
bool open = false, taken = false;

//world collision platforms and variables
World_Collision wall0, wall1, wall2, platform1, platform2, platform3, platform4, platform5, platform6, platform7, platform8, platform9, platform10, platform11, platform12, platform13;
float w0x, w0y, w0w, w0h;
float w1x, w1y, w1w, w1h;
float w2x, w2y, w2w, w2h;
float p1x, p1y, pw, ph;
float p2x, p2y, p2w, p2h;
float p3x, p3y, p3w, p3h;
float p4x, p4y, p4w, p4h;
float p5x, p5y, p5w, p5h;
float p6x, p6y, p6w, p6h;
float p7x, p7y, p7w, p7h; 
float p8x, p8y, p8w, p8h;
float p9x, p9y, p9w, p9h;
float p10x, p10y, p10w, p10h;
float p11x, p11y, p11w, p11h;
float p12x, p12y, p12w, p12h;
float p13x, p13y, p13w, p13h;

//world collision ledges and variables
World_Collision ledge1, ledge2, ledge3, ledge4, ledge5, ledge6, ledge7, ledge8, ledge9, ledge10, ledge11, ledge12, ledge13, ledge14, ledge15;
float l1x, l1y, l1w, l1h;
float l2x, l2y, l2w, l2h;
float l3x, l3y, l3w, l3h;
float l4x, l4y, l4w, l4h;
float l5x, l5y, l5w, l5h;
float l6x, l6y, l6w, l6h;
float l7x, l7y, l7w, l7h;
float l8x, l8y, l8w, l8h;
float l9x, l9y, l9w, l9h;
float l10x, l10y, l10w, l10h;
float l11x, l11y, l11w, l11h;
float l12x, l12y, l12w, l12h;
float l13x, l13y, l13w, l13h;
float l14x, l14y, l14w, l14h;
float l15x, l15y, l15w, l15h;

//movement booleans
bool jump = false, left = false, right = false, spaceHeld = false, hiding = false;
//other booleans for misc.
bool spotted = false, dead = false, transition = false, timeEMP = false, controls = false;

//vectors for gravity and velocities
vec2 gravity(0.0f, 0.0f), velocity(0.0f, 0.0f), enemyVelocity(0.0f, 0.0f), enemy2Velocity(0.0f, 0.0f), enemy3Velocity(0.0f, 0.0f), enemy4Velocity(0.0f, 0.0f), enemy5Velocity(0.0f, 0.0f);
//various second counters
int seconds = 0, deathSeconds = 0, shootSeconds = 0;

//initial position of door
int endX = 940, endY = 290;


//keyboard function, set keys to do tasks
void KeyboardFunc(Window::Key a_key, Window::EventType a_eventType)
{
	switch (a_eventType)
	{
	case Window::EventType::KeyPressed:
	{
		if (a_key == Window::Key::W)
		{
			if (hiding)
			{
				hiding = false;
			}
		}
		if (a_key == Window::Key::S)
		{
			if (level3)
			{
				if (player.getX() <= hx1 + 10 && player.getX() >= hx1 - 10 && player.getY() <= hy1 + 20)
				{
					hiding = true;
				}
				if (player.getX() <= hx2 + 10 && player.getX() >= hx2 - 10 && player.getY() <= hy2 + 20)
				{
					hiding = true;
				}
				if (player.getX() <= hx3 + 10 && player.getX() >= hx3 - 10 && player.getY() <= hy3 + 20)
				{
					hiding = true;
				}
				if (player.getX() <= hx4 + 10 && player.getX() >= hx4 - 10 && player.getY() <= hy4 + 20)
				{
					hiding = true;
				}
				if (player.getX() <= hx5 + 10 && player.getX() >= hx5 - 10 && player.getY() <= hy5 + 20)
				{
					hiding = true;
				}
			}
		}
		if (a_key == Window::Key::A)
		{
			left = true;
		}

		if (a_key == Window::Key::D)
		{
			right = true;
		}

		if (jump == false)
		{
			if (a_key == Window::Key::Space)
			{
				spaceHeld = true;
			}
		}
		if (a_key == Window::Key::Q && !player.returnEMP())
		{
			if (player.getEMP() > 0)
			{
				playeranim = EMP;
				timeEMP = true;
			}
			
		}

		if (a_key == Window::Key::E)
		{
			if (player.getX() <= terminal1.getX() + 10 && player.getX() >= terminal1.getX() - 10)
			{
				player.addEMP(terminal1);
				taken = true;
			}
			player.pickPocket(keyhold1);

			if (player.key == true)
			{
				if (player.getX() >= endX && player.getY() >= endY && player.getY() <= endY + 20)
				{
					if (level1)
					{
						transition = true;
						y = 83;
						x = 100;
						level1 = false;
						level2 = true;
					}
					else if (level2)
					{
						transition = true;
						y = 83;
						x = 100;
						level2 = false;
						level3 = true;

					}
			}
			}
			if (player.getX() <= chx + 30 && player.getX() >= chx - 10 && player.getY() >= chy && player.getY() <= chy + 20)
			{
				open = true;
			}
			
		}
		if (a_key == Window::Key::Return)
		{
			if (dead == true)
			{
				if (lives >= 0)
				{
					spotted = false;
					y = 100;
					x = 120;
					deathSeconds = 0;
					shootSeconds = 0;
					lives -= 1;
					dead = false;
					mainCharacter.set_scale(20, 20);
				}
			}
			
		}
		if (a_key == Window::Key::Escape)
		{
			if (lives == -1)
			{
				lives -= 1;
			}
			if (won)
			{
				exit(1);
			}
			exit(1);
		}	

		if (a_key == Window::Key::Tab)
		{
			controls = true;
		}
	}
		break;
	default: 
		break;
	case Window::EventType::KeyReleased:
	{
		if (a_key == Window::Key::A)
		{
			left = false;
		}

		if (a_key == Window::Key::D)
		{
			right = false;
		}

		if (a_key == Window::Key::Q)
		{
			player.setEMP();
		}
		if (a_key == Window::Key::Space)
		{
			spaceHeld = false;
		}
		if (a_key == Window::Key::Tab)
		{
			controls = false;
		}
	}
		break;
	}
}

//check for collision function
bool checkCollide(int x, int y, int Width1, int Height1, int x2, int y2, int Width2, int Height2)
{
	if (x + Width1 < x2 || x > x2 + Width2) return false; //x axis not overlapping
	if (y + Height1 < y2 || y > y2 + Height2) return false; //y axis not overlapping

	return true; //one of the axis are overlapping
}

//movement for player along with left/right side collision checks
void Movement()
{
	//player movement info//////

	if (spotted == false)
	{
		if (left == true) //LEFT
		{
			if (dead == false)
			{
				if (transition == false)
				{
					if (hiding == false)
					{
						if (mainMenu)
							{
								//beginning wall
								if (checkCollide(x, y, w, h, wall0.getX(), wall0.getY(), wall0.getWidth(), wall0.getHeight()))
								{
									velocity.x = 0;
								}
			
								else
									velocity.x = -100.0f;
								mainCharacter.set_scale(-20, 20); //flip sprite
								mainCharacter.set_animation("anim_2");
							}
						if (level1)
						{
							//beginning wall
							if (checkCollide(x, y, w, h, wall0.getX(), wall0.getY(), wall0.getWidth(), wall0.getHeight()))
							{
								velocity.x = 0;
							}
							//right side of platforms
							else if (checkCollide(x, y, w, h, platform1.getX(), platform1.getY(), platform1.getWidth() + 4, platform1.getHeight() - 1)) 
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, platform2.getX(), platform2.getY(), platform2.getWidth() + 3, platform2.getHeight() - 1))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, platform4.getX(), platform4.getY(), platform4.getWidth() + 3, platform4.getHeight() - 1))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, platform5.getX(), platform5.getY(), platform5.getWidth() + 3, platform5.getHeight() - 1))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, platform6.getX(), platform6.getY(), platform6.getWidth() + 3, platform6.getHeight() - 1))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, platform7.getX(), platform7.getY(), platform7.getWidth() + 3, platform7.getHeight() - 1))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, platform9.getX(), platform9.getY(), platform9.getWidth() + 3, platform9.getHeight() - 1))
							{
								velocity.x = 0;
							}
							//right side of ledges
							else if (checkCollide(x, y, w, h, ledge2.getX(), ledge2.getY(), ledge2.getWidth() + 3, ledge2.getHeight() - 1))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, ledge4.getX(), ledge4.getY(), ledge4.getWidth() + 3, ledge4.getHeight() - 1))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, ledge6.getX(), ledge6.getY(), ledge6.getWidth() + 3, ledge6.getHeight() - 1))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, ledge8.getX(), ledge8.getY(), ledge8.getWidth() + 3, ledge8.getHeight() - 1))
							{
								velocity.x = 0;
							}
							else
								velocity.x = -100.0f;
							mainCharacter.set_scale(-20, 20); //flip sprite
							mainCharacter.set_animation("anim_2");
						}
						if (level2)
						{
							//right side of platforms
							if (checkCollide(x, y, w, h, wall0.getX(), wall0.getY(), wall0.getWidth(), wall0.getHeight()))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, wall1.getX(), wall1.getY(), wall1.getWidth() + 5, wall1.getHeight()))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, wall2.getX(), wall2.getY(), wall2.getWidth() + 5, wall2.getHeight()))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, platform1.getX(), platform1.getY(), platform1.getWidth() + 3, platform1.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, platform2.getX(), platform2.getY(), platform2.getWidth() + 3, platform2.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, platform3.getX(), platform3.getY(), platform3.getWidth() + 3, platform3.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, platform4.getX(), platform4.getY(), platform4.getWidth() + 3, platform4.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, platform5.getX(), platform5.getY(), platform5.getWidth() + 3, platform5.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, platform6.getX(), platform6.getY(), platform6.getWidth() + 3, platform6.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, platform7.getX(), platform7.getY(), platform7.getWidth() + 3, platform7.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, platform8.getX(), platform8.getY(), platform8.getWidth() + 3, platform8.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, platform9.getX(), platform9.getY(), platform9.getWidth() + 3, platform9.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, platform10.getX(), platform10.getY(), platform10.getWidth() + 3, platform10.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, platform11.getX(), platform11.getY(), platform11.getWidth() + 3, platform11.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, platform12.getX(), platform12.getY(), platform12.getWidth() + 3, platform12.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, ledge4.getX(), ledge4.getY(), ledge4.getWidth() + 3, ledge4.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, ledge5.getX(), ledge5.getY(), ledge5.getWidth() + 3, ledge5.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, ledge6.getX(), ledge6.getY(), ledge6.getWidth() + 3, ledge6.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, ledge7.getX(), ledge7.getY(), ledge7.getWidth() + 3, ledge7.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, ledge8.getX(), ledge8.getY(), ledge8.getWidth() + 3, ledge8.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else
								velocity.x = -100.0f;
							mainCharacter.set_scale(-20, 20); //flip sprite
							mainCharacter.set_animation("anim_2");
						}

						if (level3)
						{
							//right side of platforms
							if (checkCollide(x, y, w, h, wall0.getX(), wall0.getY(), wall0.getWidth(), wall0.getHeight()))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, wall1.getX(), wall1.getY(), wall1.getWidth() + 5, wall1.getHeight()))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, platform1.getX(), platform1.getY(), platform1.getWidth() + 3, platform1.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, platform2.getX(), platform2.getY(), platform2.getWidth() + 3, platform2.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, platform3.getX(), platform3.getY(), platform3.getWidth() + 3, platform3.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, platform4.getX(), platform4.getY(), platform4.getWidth() + 3, platform4.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, platform5.getX(), platform5.getY(), platform5.getWidth() + 3, platform5.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, platform6.getX(), platform6.getY(), platform6.getWidth() + 3, platform6.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, platform7.getX(), platform7.getY(), platform7.getWidth() + 3, platform7.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, platform8.getX(), platform8.getY(), platform8.getWidth() + 3, platform8.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, platform9.getX(), platform9.getY(), platform9.getWidth() + 3, platform9.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, platform10.getX(), platform10.getY(), platform10.getWidth() + 3, platform10.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, platform11.getX(), platform11.getY(), platform11.getWidth() + 3, platform11.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, platform12.getX(), platform12.getY(), platform12.getWidth() + 3, platform12.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, platform13.getX(), platform13.getY(), platform13.getWidth() + 3, platform13.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, ledge1.getX(), ledge1.getY(), ledge1.getWidth() + 3, ledge1.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, ledge2.getX(), ledge2.getY(), ledge2.getWidth() + 3, ledge2.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, ledge3.getX(), ledge3.getY(), ledge3.getWidth() + 3, ledge3.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, ledge4.getX(), ledge4.getY(), ledge4.getWidth() + 3, ledge4.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, ledge5.getX(), ledge5.getY(), ledge5.getWidth() + 3, ledge5.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, ledge6.getX(), ledge6.getY(), ledge6.getWidth() + 3, ledge6.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, ledge7.getX(), ledge7.getY(), ledge7.getWidth() + 3, ledge7.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, ledge8.getX(), ledge8.getY(), ledge8.getWidth() + 3, ledge8.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, ledge9.getX(), ledge9.getY(), ledge9.getWidth() + 3, ledge9.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, ledge10.getX(), ledge10.getY(), ledge10.getWidth() + 3, ledge10.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, ledge11.getX(), ledge11.getY(), ledge11.getWidth() + 3, ledge11.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, ledge12.getX(), ledge12.getY(), ledge12.getWidth() + 3, ledge12.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, ledge13.getX(), ledge13.getY(), ledge13.getWidth() + 3, ledge13.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, ledge14.getX(), ledge14.getY(), ledge10.getWidth() + 3, ledge14.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w, h, ledge15.getX(), ledge15.getY(), ledge15.getWidth() + 3, ledge15.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else
								velocity.x = -100.0f;
							mainCharacter.set_scale(-20, 20); //flip sprite
							mainCharacter.set_animation("anim_2");
						}
					}
				}
			}
		}
		else if (right == true) //RIGHT
		{
			if (dead == false)
			{
				if (transition == false)
				{
					if (hiding == false)
					{
						if (mainMenu)
							{
								//left side of platforms
								if (checkCollide(x, y, w + 5, h, platform2.getX(), platform2.getY(), platform2.getWidth(), platform2.getHeight() - 1))
								{
									velocity.x = 0;
								}
								else
									velocity.x = 100.0f;
								mainCharacter.set_scale(20, 20); //flip sprite
								mainCharacter.set_animation("anim_2");
							}
						if (level1)
						{
							//left side of platforms
							if (checkCollide(x, y, w + 5, h, platform2.getX(), platform2.getY(), platform2.getWidth(), platform2.getHeight() - 1))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, platform4.getX(), platform4.getY(), platform4.getWidth(), platform4.getHeight() - 1))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, platform5.getX(), platform5.getY(), platform5.getWidth(), platform5.getHeight() - 1)) 
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, platform7.getX(), platform7.getY(), platform7.getWidth(), platform7.getHeight() - 1))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, platform8.getX(), platform8.getY(), platform8.getWidth(), platform8.getHeight() - 1)) 
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, platform9.getX(), platform9.getY(), platform9.getWidth(), platform9.getHeight() - 1)) 
							{
								velocity.x = 0;
							}
							//end wall
							else if (checkCollide(x, y, w + 5, h, wall1.getX(), wall1.getY(), wall1.getWidth(), wall1.getHeight() - 5))
							{
								velocity.x = 0;
							}
							//left side of ledges
							else if (checkCollide(x, y, w + 5, h, ledge1.getX(), ledge1.getY(), ledge1.getWidth(), ledge1.getHeight() - 1)) 
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, ledge3.getX(), ledge3.getY(), ledge3.getWidth(), ledge3.getHeight() - 1)) 
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, ledge5.getX(), ledge5.getY(), ledge5.getWidth(), ledge5.getHeight() - 1))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, ledge7.getX(), ledge7.getY(), ledge7.getWidth(), ledge7.getHeight() - 1))
							{
								velocity.x = 0;
							}
							else
								velocity.x = 100.0f;
							mainCharacter.set_scale(20, 20); //flip sprite
							mainCharacter.set_animation("anim_2");
						}
						if (level2)
						{
							//left side of platforms
							if (checkCollide(x, y, w + 5, h, platform3.getX(), platform3.getY(), platform3.getWidth(), platform3.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, platform2.getX(), platform2.getY(), platform2.getWidth(), platform2.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, platform4.getX(), platform4.getY(), platform4.getWidth(), platform4.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, platform5.getX(), platform5.getY(), platform5.getWidth(), platform5.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, wall1.getX(), wall1.getY(), wall1.getWidth(), wall1.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, wall2.getX(), wall2.getY(), wall2.getWidth(), wall2.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, platform6.getX(), platform6.getY(), platform6.getWidth(), platform6.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, platform7.getX(), platform7.getY(), platform7.getWidth(), platform7.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, platform8.getX(), platform8.getY(), platform8.getWidth(), platform8.getHeight() - 1))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, platform9.getX(), platform9.getY(), platform9.getWidth(), platform9.getHeight() - 1))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, platform12.getX(), platform12.getY(), platform12.getWidth(), platform12.getHeight() - 1))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, ledge1.getX(), ledge1.getY(), ledge1.getWidth(), ledge1.getHeight() - 5)) 
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, ledge2.getX(), ledge2.getY(), ledge2.getWidth(), ledge2.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, ledge3.getX(), ledge3.getY(), ledge3.getWidth(), ledge3.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, ledge5.getX(), ledge5.getY(), ledge5.getWidth(), ledge5.getHeight() - 5)) 
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, ledge6.getX(), ledge6.getY(), ledge6.getWidth(), ledge6.getHeight() - 5)) 
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, ledge7.getX(), ledge7.getY(), ledge7.getWidth(), ledge7.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, ledge8.getX(), ledge8.getY(), ledge8.getWidth(), ledge8.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else
								velocity.x = 100.0f;
							mainCharacter.set_scale(20, 20); //flip sprite
							mainCharacter.set_animation("anim_2");
						}

						if (level3)
						{
							//left side of platforms
							if (checkCollide(x, y, w + 5, h, wall1.getX(), wall1.getY(), wall1.getWidth(), wall1.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, platform1.getX(), platform1.getY(), platform1.getWidth(), platform1.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, platform2.getX(), platform2.getY(), platform2.getWidth(), platform2.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, platform3.getX(), platform3.getY(), platform3.getWidth(), platform3.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, platform4.getX(), platform4.getY(), platform4.getWidth(), platform4.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, platform5.getX(), platform5.getY(), platform5.getWidth(), platform5.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, platform6.getX(), platform6.getY(), platform6.getWidth(), platform6.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, platform7.getX(), platform7.getY(), platform7.getWidth(), platform7.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, platform8.getX(), platform8.getY(), platform8.getWidth(), platform8.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, platform9.getX(), platform9.getY(), platform9.getWidth(), platform9.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, platform10.getX(), platform10.getY(), platform10.getWidth(), platform10.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, platform11.getX(), platform11.getY(), platform11.getWidth(), platform11.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, platform12.getX(), platform12.getY(), platform12.getWidth(), platform12.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, platform13.getX(), platform13.getY(), platform13.getWidth(), platform13.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, ledge1.getX(), ledge1.getY(), ledge1.getWidth(), ledge1.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, ledge2.getX(), ledge2.getY(), ledge2.getWidth(), ledge2.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, ledge3.getX(), ledge3.getY(), ledge3.getWidth(), ledge3.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, ledge4.getX(), ledge4.getY(), ledge4.getWidth(), ledge4.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, ledge5.getX(), ledge5.getY(), ledge5.getWidth(), ledge5.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, ledge6.getX(), ledge6.getY(), ledge6.getWidth(), ledge6.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, ledge7.getX(), ledge7.getY(), ledge7.getWidth(), ledge7.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, ledge8.getX(), ledge8.getY(), ledge8.getWidth(), ledge8.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, ledge9.getX(), ledge9.getY(), ledge9.getWidth(), ledge9.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, ledge10.getX(), ledge10.getY(), ledge10.getWidth(), ledge10.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, ledge11.getX(), ledge11.getY(), ledge11.getWidth(), ledge11.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, ledge12.getX(), ledge12.getY(), ledge12.getWidth(), ledge12.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, ledge13.getX(), ledge13.getY(), ledge13.getWidth(), ledge13.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, ledge14.getX(), ledge14.getY(), ledge10.getWidth(), ledge14.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else if (checkCollide(x, y, w + 5, h, ledge15.getX(), ledge15.getY(), ledge15.getWidth(), ledge15.getHeight() - 5))
							{
								velocity.x = 0;
							}
							else
								velocity.x = 100.0f;
							mainCharacter.set_scale(20, 20); //flip sprite
							mainCharacter.set_animation("anim_2");
						}
					}
				}
			}
		}

		

		else //not moving
		{
			velocity.x = 0;
			mainCharacter.set_animation("anim_3");
		}

		
		if (spaceHeld == true) //if jumping
		{
			if (seconds < 15)
			{
				velocity.y = 145.0f; //apply velocity
				seconds += 1;
			}
		}
		else
		{
			seconds = 0;
		}

		x += velocity.x * (1.0f / 60.0f); //the player's horizontal velocity updated per frame
		y += velocity.y * (1.0f / 60.0f); //same as above but this time for vertical velocity
	}

} 

//setup the variables of world collision objects
void SetupCollisionProperties()
{
	//create wall properties/////
	wall0.setCoord(w0x, w0y);
	wall0.setHeight(w0h);
	wall0.setWidth(w0w);

	wall1.setCoord(w1x, w1y);
	wall1.setHeight(w1h);
	wall1.setWidth(w1w);

	wall2.setCoord(w2x, w2y);
	wall2.setHeight(w2h);
	wall2.setWidth(w2w);

	//create platform properties//////
	platform1.setCoord(p1x, p1y);
	platform1.setHeight(ph);
	platform1.setWidth(pw);

	platform2.setCoord(p2x, p2y);
	platform2.setHeight(p2h);
	platform2.setWidth(p2w);

	platform3.setCoord(p3x, p3y);
	platform3.setHeight(p3h);
	platform3.setWidth(p3w);

	platform4.setCoord(p4x, p4y);
	platform4.setHeight(p4h);
	platform4.setWidth(p4w);

	platform5.setCoord(p5x, p5y);
	platform5.setHeight(p5h);
	platform5.setWidth(p5w);

	platform6.setCoord(p6x, p6y);
	platform6.setHeight(p6h);
	platform6.setWidth(p6w);

	platform7.setCoord(p7x, p7y);
	platform7.setHeight(p7h);
	platform7.setWidth(p7w);

	platform8.setCoord(p8x, p8y);
	platform8.setHeight(p8h);
	platform8.setWidth(p8w);

	platform9.setCoord(p9x, p9y);
	platform9.setHeight(p9h);
	platform9.setWidth(p9w);

	platform10.setCoord(p10x, p10y);
	platform10.setHeight(p10h);
	platform10.setWidth(p10w);

	platform11.setCoord(p11x, p11y);
	platform11.setHeight(p11h);
	platform11.setWidth(p11w);

	platform12.setCoord(p12x, p12y);
	platform12.setHeight(p12h);
	platform12.setWidth(p12w);

	platform13.setCoord(p13x, p13y);
	platform13.setHeight(p13h);
	platform13.setWidth(p13w);

	//////////////////////////////////

	//create ledge properties/////////
	ledge1.setCoord(l1x, l1y);
	ledge1.setHeight(l1h);
	ledge1.setWidth(l1w);

	ledge2.setCoord(l2x, l2y);
	ledge2.setHeight(l2h);
	ledge2.setWidth(l2w);

	ledge3.setCoord(l3x, l3y);
	ledge3.setHeight(l3h);
	ledge3.setWidth(l3w);

	ledge4.setCoord(l4x, l4y);
	ledge4.setHeight(l4h);
	ledge4.setWidth(l4w);

	ledge5.setCoord(l5x, l5y);
	ledge5.setHeight(l5h);
	ledge5.setWidth(l5w);

	ledge6.setCoord(l6x, l6y);
	ledge6.setHeight(l6h);
	ledge6.setWidth(l6w);

	ledge7.setCoord(l7x, l7y);
	ledge7.setHeight(l7h);
	ledge7.setWidth(l7w);

	ledge8.setCoord(l8x, l8y);
	ledge8.setHeight(l8h);
	ledge8.setWidth(l8w);

	ledge9.setCoord(l9x, l9y);
	ledge9.setHeight(l9h);
	ledge9.setWidth(l9w);

	ledge10.setCoord(l10x, l10y);
	ledge10.setHeight(l10h);
	ledge10.setWidth(l10w);

	ledge11.setCoord(l11x, l11y);
	ledge11.setHeight(l11h);
	ledge11.setWidth(l11w);

	ledge12.setCoord(l12x, l12y);
	ledge12.setHeight(l12h);
	ledge12.setWidth(l12w);

	ledge13.setCoord(l13x, l13y);
	ledge13.setHeight(l13h);
	ledge13.setWidth(l13w);

	ledge14.setCoord(l14x, l14y);
	ledge14.setHeight(l14h);
	ledge14.setWidth(l14w);

	ledge15.setCoord(l15x, l15y);
	ledge15.setHeight(l15h);
	ledge15.setWidth(l15w);
}

//bottom/top collision for level2
void bottomTopCollision()
{
	//platforms
	w0x = 0, w0y = 0, w0w = 54, w0h = 1280;
	w1x = 1231, w1y = 0, w1w = 49, w1h = 720;
	//w2x = 888, w2y = 172, w2w = 40, w2h = 200;
	p1x = 0, p1y = 0, pw = 163, ph = 83;
	p2x = 203, p2y = 0, p2w = 15, p2h = 83;
	p3x = 195, p3y = 0, p3w = 40, p3h = 106;
	p4x = 252, p4y = 0, p4w = 40, p4h = 133;
	p5x = 314, p5y = 0, p5w = 300, p5h = 158;
	p6x = 603, p6y = 0, p6w = 10, p6h = 210;
	p7x = 568, p7y = 188, p7w = 35, p7h = 10;
	p8x = 643, p8y = 0, p8w = 15, p8h = 243;
	p9x = 243, p9y = 273, p9w = 180, p9h = 93;
	p10x = 423, p10y = 273, p10w = 80, p10h = 62;
	p11x = 503, p11y = 273, p11w = 80, p11h = 31;
	p12x = 1029, p12y = 0, p12w = 300, p12h = 147;


	//ledges
	l1x = 583, l1y = 273, l1w = 30, l1h = 5;
	l2x = 438, l2y = 399, l2w = 102, l2h = 7;
	l3x = 587, l3y = 429, l3w = 102, l3h = 7;
	l4x = 738, l4y = 459, l4w = 102, l4h = 7;
	l5x = 913, l5y = 370, l5w = 224, l5h = 25;
	l6x = 871, l6y = 0, l6w = 30, l6h = 321;
	l7x = 923, l7y = 0, l7w = 30, l7h = 270;
	l8x = 976, l8y = 0, l8w = 30, l8h = 221;
	///////////////////////

	//spotlights
	sx = 431, sy = 193;
	sx2 = 547, sy2 = 193;
	spotlight2.set_scale(36, 30);
	spotlight2.set_center(1.0f, -0.5f);

	//door
	dx = 1216, dy = 146;
	endX = 1215, endY = 146;
	//COLLISION DETECTION IS PUT AFTER HERE///////

	
	//1st platform collision//////
	//SIDE OF PLATFORM COLLISION CHECK IN MOVEMENT FOR PLAYER
	//top of platforms
	for (int i = 0; i < platform.size(); i++)
	{
		if (checkCollide(x, y, w, h, platform[0]->getX(), platform[0]->getY() + 3, platform[0]->getWidth(), platform[0]->getHeight() - 3))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < platform[0]->getY() + platform[0]->getHeight())
			{
				y = platform[0]->getY() + platform[0]->getHeight();
			}
		}
		/*else if (checkCollide(x, y, w, h, platform[1]->getX(), platform[1]->getY(), platform[1]->getWidth(), platform[1]->getHeight()))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < platform[1]->getY() + platform[1]->getHeight())
			{
				y = platform[1]->getY() + platform[1]->getHeight();
			}
		}*/
		else if (checkCollide(x, y, w, h, platform[2]->getX(), platform[2]->getY() + 3, platform[2]->getWidth(), platform[2]->getHeight() - 3))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < platform[2]->getY() + platform[2]->getHeight())
			{
				y = platform[2]->getY() + platform[2]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, platform[3]->getX(), platform[3]->getY() + 3, platform[3]->getWidth(), platform[3]->getHeight() - 3))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < platform[3]->getY() + platform[3]->getHeight())
			{
				y = platform[3]->getY() + platform[3]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, platform[4]->getX(), platform[4]->getY() + 3, platform[4]->getWidth(), platform[4]->getHeight() - 3))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < platform[4]->getY() + platform[4]->getHeight())
			{
				y = platform[4]->getY() + platform[4]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, platform[5]->getX(), platform[5]->getY() + 3, platform[5]->getWidth(), platform[5]->getHeight() - 3))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < platform[5]->getY() + platform[5]->getHeight())
			{
				y = platform[5]->getY() + platform[5]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, platform[6]->getX(), platform[6]->getY() + 3, platform[6]->getWidth(), platform[6]->getHeight() - 3))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < platform[6]->getY() + platform[6]->getHeight())
			{
				y = platform[6]->getY() + platform[6]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, platform[7]->getX(), platform[7]->getY() + 3, platform[7]->getWidth(), platform[7]->getHeight() - 3))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < platform[7]->getY() + platform[7]->getHeight())
			{
				y = platform[7]->getY() + platform[7]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, platform[8]->getX(), platform[8]->getY() + 3, platform[8]->getWidth(), platform[8]->getHeight() - 3))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < platform[8]->getY() + platform[8]->getHeight())
			{
				y = platform[8]->getY() + platform[8]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, platform[9]->getX(), platform[9]->getY() + 3, platform[9]->getWidth(), platform[9]->getHeight() - 3))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < platform[9]->getY() + platform[9]->getHeight())
			{
				y = platform[9]->getY() + platform[9]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, platform[10]->getX(), platform[10]->getY() + 3, platform[10]->getWidth(), platform[10]->getHeight() - 3))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < platform[10]->getY() + platform[10]->getHeight())
			{
				y = platform[10]->getY() + platform[10]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, platform[11]->getX(), platform[11]->getY() + 3, platform[11]->getWidth(), platform[11]->getHeight() - 3))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < platform[11]->getY() + platform[11]->getHeight())
			{
				y = platform[11]->getY() + platform[11]->getHeight();
			}
		}
		//top of ledges
		else if (checkCollide(x, y, w, h, ledges[0]->getX(), ledges[0]->getY() + 5, ledges[0]->getWidth(), ledges[0]->getHeight() - 5))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < ledges[0]->getY() + ledges[0]->getHeight())
			{
				y = ledges[0]->getY() + ledges[0]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, ledges[1]->getX(), ledges[1]->getY() + 5, ledges[1]->getWidth(), ledges[1]->getHeight() - 5))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < ledges[1]->getY() + ledges[1]->getHeight())
			{
				y = ledges[1]->getY() + ledges[1]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, ledges[2]->getX(), ledges[2]->getY() + 5, ledges[2]->getWidth(), ledges[2]->getHeight() - 5))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < ledges[2]->getY() + ledges[2]->getHeight())
			{
				y = ledges[2]->getY() + ledges[2]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, ledges[3]->getX(), ledges[3]->getY() + 5, ledges[3]->getWidth(), ledges[3]->getHeight() - 5))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < ledges[3]->getY() + ledges[3]->getHeight())
			{
				y = ledges[3]->getY() + ledges[3]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, ledges[4]->getX(), ledges[4]->getY() + 5, ledges[4]->getWidth(), ledges[4]->getHeight() - 5))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < ledges[4]->getY() + ledges[4]->getHeight())
			{
				y = ledges[4]->getY() + ledges[4]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, ledges[5]->getX(), ledges[5]->getY() + 5, ledges[5]->getWidth(), ledges[5]->getHeight() - 5))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < ledges[5]->getY() + ledges[5]->getHeight())
			{
				y = ledges[5]->getY() + ledges[5]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, ledges[6]->getX(), ledges[6]->getY() + 5, ledges[6]->getWidth(), ledges[6]->getHeight() - 5))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < ledges[6]->getY() + ledges[6]->getHeight())
			{
				y = ledges[6]->getY() + ledges[6]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, ledges[7]->getX(), ledges[7]->getY() + 5, ledges[7]->getWidth(), ledges[7]->getHeight() - 5))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < ledges[7]->getY() + ledges[7]->getHeight())
			{
				y = ledges[7]->getY() + ledges[7]->getHeight();
			}
		}
		else
		{
			jump = true;
			gravity.y = -1000.0f;
		}

		//bottom of platforms and ledges
		if (checkCollide(x, y, w, h, platform[4]->getX(), platform[4]->getY() - 3, platform[4]->getWidth(), platform[4]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, platform[6]->getX(), platform[6]->getY() - 3, platform[6]->getWidth(), platform[6]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, platform[8]->getX(), platform[8]->getY() - 3, platform[8]->getWidth(), platform[8]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, platform[9]->getX(), platform[9]->getY() - 3, platform[9]->getWidth(), platform[9]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, platform[10]->getX(), platform[10]->getY() - 3, platform[10]->getWidth(), platform[10]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, platform[11]->getX(), platform[11]->getY() - 3, platform[11]->getWidth(), platform[11]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, ledges[0]->getX(), ledges[0]->getY() - 3, ledges[0]->getWidth(), ledges[0]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, ledges[1]->getX(), ledges[1]->getY() - 3, ledges[1]->getWidth(), ledges[1]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, ledges[2]->getX(), ledges[2]->getY() - 3, ledges[2]->getWidth(), ledges[2]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, ledges[3]->getX(), ledges[3]->getY() - 3, ledges[3]->getWidth(), ledges[3]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, ledges[4]->getX(), ledges[4]->getY() - 3, ledges[4]->getWidth(), ledges[4]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, ledges[5]->getX(), ledges[5]->getY() - 3, ledges[5]->getWidth(), ledges[5]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, ledges[6]->getX(), ledges[6]->getY() - 3, ledges[6]->getWidth(), ledges[6]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, ledges[7]->getX(), ledges[7]->getY() - 3, ledges[7]->getWidth(), ledges[7]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
	}

	//////////////////////////////
	velocity.y += gravity.y * (1.0f / 60.0f); //this equation effects the y coord of the player
											  //the velocity of the jump is effected by the gravity and updated per frame
											  //gives the jump a much smoother effect
											  //like a PARABOLA :D
	////////////////////////

	if (y < -250)
	{
		y = 83;
		x = 120;
		//lives =  lives - 1;
		dead = true;
		mainCharacter.set_scale(20, 20);
	}

}

//bottom/top collision for level1
void bottomTopCollision2()
{
	endX = 940, endY = 290;
	dx = 935, dy = 289;
	//platforms
	w0x = 0, w0y = 0, w0w = 100, w0h = 720;
	p1x = 0, p1y = 0, pw = 305, ph = 276;
	p2x = 356, p2y = 0, p2w = 180, p2h = 290;
	p3x = 305, p3y = 0, p3w = 55, p3h = 242;
	p4x = 589, p4y = 132, p4w = 167, p4h = 158;
	p5x = 589, p5y = 0, p5w = 36, p5h = 131;
	p6x = 589, p6y = 0, p6w = 167, p6h = 72;
	p7x = 744, p7y = 114, p7w = 12, p7h = 17;
	p8x = 810, p8y = 0, p8w = 300, p8h = 290;
	p9x = 652, p9y = 317, p9w = 45, p9h = 7;
	w1x = 950, w1y = 0, w1w = 300, w1h = 720;

	//ledges
	l1x = 795, l1y = 263, l1w = 15, l1h = 7;
	l2x = 754, l2y = 232, l2w = 15, l2h = 7;
	l3x = 795, l3y = 203, l3w = 15, l3h = 7;
	l4x = 754, l4y = 173, l4w = 15, l4h = 7;
	l5x = 795, l5y = 143, l5w = 15, l5h = 7;
	l6x = 754, l6y = 113, l6w = 15, l6h = 7;
	l7x = 795, l7y = 83, l7w = 15, l7h = 7;
	l8x = 754, l8y = 53, l8w = 15, l8h = 7;

	sx = 451, sy = 325;
	sx2 = 705, sy2 = 118;
	spotlight.set_scale(36, 30);
	spotlight.set_center(1.0f, -0.5f);
	spotlight2.set_scale(47, 40);
	spotlight2.set_center(1.0f, -0.25f);

	//SIDE OF PLATFORM COLLISION CHECK IN MOVEMENT FOR PLAYER
	//top of platforms and ledges
	for (int i = 0; i < platform.size(); i++)
	{
		if (checkCollide(x, y, w, h, platform[0]->getX(), platform[0]->getY() + 3, platform[0]->getWidth(), platform[0]->getHeight() - 3))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < platform[0]->getY() + platform[0]->getHeight())
			{
				y = platform[0]->getY() + platform[0]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, platform[1]->getX(), platform[1]->getY() + 3, platform[1]->getWidth(), platform[1]->getHeight() - 3))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < platform[1]->getY() + platform[1]->getHeight())
			{
				y = platform[1]->getY() + platform[1]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, platform[2]->getX(), platform[2]->getY() + 3, platform[2]->getWidth(), platform[2]->getHeight() - 3))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < platform[2]->getY() + platform[2]->getHeight())
			{
				y = platform[2]->getY() + platform[2]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, platform[3]->getX(), platform[3]->getY() + 3, platform[3]->getWidth(), platform[3]->getHeight() - 3))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < platform[3]->getY() + platform[3]->getHeight())
			{
				y = platform[3]->getY() + platform[3]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, platform[4]->getX(), platform[4]->getY() + 3, platform[4]->getWidth(), platform[4]->getHeight() - 3))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < platform[4]->getY() + platform[4]->getHeight())
			{
				y = platform[4]->getY() + platform[4]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, platform[5]->getX(), platform[5]->getY() + 3, platform[5]->getWidth(), platform[5]->getHeight() - 3))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < platform[5]->getY() + platform[5]->getHeight())
			{
				y = platform[5]->getY() + platform[5]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, platform[6]->getX(), platform[6]->getY() + 3, platform[6]->getWidth(), platform[6]->getHeight() - 3))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < platform[6]->getY() + platform[6]->getHeight())
			{
				y = platform[6]->getY() + platform[6]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, platform[7]->getX(), platform[7]->getY() + 3, platform[7]->getWidth(), platform[7]->getHeight() - 3))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < platform[7]->getY() + platform[7]->getHeight())
			{
				y = platform[7]->getY() + platform[7]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, platform[8]->getX(), platform[8]->getY() + 3, platform[8]->getWidth(), platform[8]->getHeight() - 3))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < platform[8]->getY() + platform[8]->getHeight())
			{
				y = platform[8]->getY() + platform[8]->getHeight();
			}
		}
		//top of ledges
		else if (checkCollide(x, y, w, h, ledges[0]->getX(), ledges[0]->getY() + 5, ledges[0]->getWidth(), ledges[0]->getHeight() - 5))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < ledges[0]->getY() + ledges[0]->getHeight())
			{
				y = ledges[0]->getY() + ledges[0]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, ledges[1]->getX(), ledges[1]->getY() + 5, ledges[1]->getWidth(), ledges[1]->getHeight() - 5))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < ledges[1]->getY() + ledges[1]->getHeight())
			{
				y = ledges[1]->getY() + ledges[1]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, ledges[2]->getX(), ledges[2]->getY() + 5, ledges[2]->getWidth(), ledges[2]->getHeight() - 5))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < ledges[2]->getY() + ledges[2]->getHeight())
			{
				y = ledges[2]->getY() + ledges[2]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, ledges[3]->getX(), ledges[3]->getY() + 5, ledges[3]->getWidth(), ledges[3]->getHeight() - 5))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < ledges[3]->getY() + ledges[3]->getHeight())
			{
				y = ledges[3]->getY() + ledges[3]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, ledges[4]->getX(), ledges[4]->getY() + 5, ledges[4]->getWidth(), ledges[4]->getHeight() - 5))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < ledges[4]->getY() + ledges[4]->getHeight())
			{
				y = ledges[4]->getY() + ledges[4]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, ledges[5]->getX(), ledges[5]->getY() + 5, ledges[5]->getWidth(), ledges[5]->getHeight() - 5))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < ledges[5]->getY() + ledges[5]->getHeight())
			{
				y = ledges[5]->getY() + ledges[5]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, ledges[6]->getX(), ledges[6]->getY() + 5, ledges[6]->getWidth(), ledges[6]->getHeight() - 5))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < ledges[6]->getY() + ledges[6]->getHeight())
			{
				y = ledges[6]->getY() + ledges[6]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, ledges[7]->getX(), ledges[7]->getY() + 5, ledges[7]->getWidth(), ledges[7]->getHeight() - 5))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < ledges[7]->getY() + ledges[7]->getHeight())
			{
				y = ledges[7]->getY() + ledges[7]->getHeight();
			}
		}
		else
		{
			jump = true;
			gravity.y = -1000.0f;
		}

		//bottom of platforms and ledges
		if (checkCollide(x, y, w, h, platform[3]->getX(), platform[3]->getY() - 3, platform[3]->getWidth(), platform[3]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, platform[6]->getX(), platform[6]->getY() - 3, platform[6]->getWidth(), platform[6]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, platform[8]->getX(), platform[8]->getY() - 3, platform[8]->getWidth(), platform[8]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, ledges[0]->getX(), ledges[0]->getY() - 3, ledges[0]->getWidth(), ledges[0]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, ledges[1]->getX(), ledges[1]->getY() - 3, ledges[1]->getWidth(), ledges[1]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, ledges[2]->getX(), ledges[2]->getY() - 3, ledges[2]->getWidth(), ledges[2]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, ledges[3]->getX(), ledges[3]->getY() - 3, ledges[3]->getWidth(), ledges[3]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, ledges[4]->getX(), ledges[4]->getY() - 3, ledges[4]->getWidth(), ledges[4]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, ledges[5]->getX(), ledges[5]->getY() - 3, ledges[5]->getWidth(), ledges[5]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, ledges[6]->getX(), ledges[6]->getY() - 3, ledges[6]->getWidth(), ledges[6]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, ledges[7]->getX(), ledges[7]->getY() - 3, ledges[7]->getWidth(), ledges[7]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
	}
	//player velocity affected by gravity per 60 frames	
	velocity.y += gravity.y * (1.0f / 60.0f);

	//if the player falls off the map
	if (y < -250)
	{
		y = 100;
		x = 120;
		//lives =  lives - 1;
		dead = true;
		mainCharacter.set_scale(20, 20);
	}

}

//bottom/top collision for level3
void bottomTopCollision3()
{
	//platforms
	w0x = 0, w0y = 0, w0w = 53, w0h = 720;
	p1x = 0, p1y = 0, pw = 151, ph = 50;
	p2x = 385, p2y = 0, p2w = 200, p2h = 140;
	p3x = 720, p3y = 0, p3w = 560, p3h = 40;
	p4x = 780, p4y = 176, p4w = 310, p4h = 14;
	p5x = 780, p5y = 176, p5w = 12, p5h = 194;
	p6x = 839, p6y = 250, p6w = 12, p6h = 155;
	p7x = 469, p7y = 356, p7w = 310, p7h = 14;
	p8x = 469, p8y = 357, p8w = 12, p8h = 74;
	p9x = 556, p9y = 398, p9w = 452, p9h = 14;
	p10x = 995, p10y = 398, p10w = 12, p10h = 74;
	p11x = 529, p11y = 439, p11w = 415, p11h = 14;
	p12x = 685, p12y = 479, p12w = 261, p12h = 14;
	p13x = 1080, p13y = 558, p13w = 300, p13h = 50;
	w1x = 1256, w1y = 0, w1w = 25, w1h = 720;

	//ledges
	l1x = 196, l1y = 73, l1w = 50, l1h = 7;
	l2x = 290, l2y = 103, l2w = 50, l2h = 7;
	l3x = 596, l3y = 99, l3w = 36, l3h = 7;
	l4x = 636, l4y = 77, l4w = 36, l4h = 7;
	l5x = 675, l5y = 55, l5w = 36, l5h = 7;
	l6x = 1242, l6y = 78, l6w = 100, l6h = 7;
	l7x = 1184, l7y = 113, l7w = 25, l7h = 7;
	l8x = 1125, l8y = 148, l8w = 25, l8h = 7;
	l9x = 791, l9y = 223, l9w = 15, l9h = 7;
	l10x = 825, l10y = 263, l10w = 15, l10h = 7;
	l11x = 791, l11y = 293, l11w = 15, l11h = 7;
	l12x = 825, l12y = 328, l12w = 15, l12h = 7;
	l13x = 862, l13y = 515, l13w = 35, l13h = 7;
	l14x = 939, l14y = 548, l14w = 35, l14h = 7;
	l15x = 1014, l15y = 578, l15w = 35, l15h = 7;

	//spotlights
	sx = 996, sy = 225;
	spotlight.set_scale(36, 30);
	spotlight.set_center(1.0f, -0.5f);

	//SIDE OF PLATFORM COLLISION CHECK IN MOVEMENT FOR PLAYER
	//top of platforms and ledges
	for (int i = 0; i < ledges.size(); i++)
	{
		if (checkCollide(x, y, w, h, platform[0]->getX(), platform[0]->getY() + 3, platform[0]->getWidth(), platform[0]->getHeight() - 3))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < platform[0]->getY() + platform[0]->getHeight())
			{
				y = platform[0]->getY() + platform[0]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, platform[1]->getX(), platform[1]->getY() + 3, platform[1]->getWidth(), platform[1]->getHeight() - 3))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < platform[1]->getY() + platform[1]->getHeight())
			{
				y = platform[1]->getY() + platform[1]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, platform[2]->getX(), platform[2]->getY() + 3, platform[2]->getWidth(), platform[2]->getHeight() - 3))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < platform[2]->getY() + platform[2]->getHeight())
			{
				y = platform[2]->getY() + platform[2]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, platform[3]->getX(), platform[3]->getY() + 3, platform[3]->getWidth(), platform[3]->getHeight() - 3))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < platform[3]->getY() + platform[3]->getHeight())
			{
				y = platform[3]->getY() + platform[3]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, platform[4]->getX(), platform[4]->getY() + 3, platform[4]->getWidth(), platform[4]->getHeight() - 3))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < platform[4]->getY() + platform[4]->getHeight())
			{
				y = platform[4]->getY() + platform[4]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, platform[5]->getX(), platform[5]->getY() + 3, platform[5]->getWidth(), platform[5]->getHeight() - 3))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < platform[5]->getY() + platform[5]->getHeight())
			{
				y = platform[5]->getY() + platform[5]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, platform[6]->getX(), platform[6]->getY() + 3, platform[6]->getWidth(), platform[6]->getHeight() - 3))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < platform[6]->getY() + platform[6]->getHeight())
			{
				y = platform[6]->getY() + platform[6]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, platform[7]->getX(), platform[7]->getY() + 3, platform[7]->getWidth(), platform[7]->getHeight() - 3))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < platform[7]->getY() + platform[7]->getHeight())
			{
				y = platform[7]->getY() + platform[7]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, platform[8]->getX(), platform[8]->getY() + 3, platform[8]->getWidth(), platform[8]->getHeight() - 3))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < platform[8]->getY() + platform[8]->getHeight())
			{
				y = platform[8]->getY() + platform[8]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, platform[9]->getX(), platform[9]->getY() + 3, platform[9]->getWidth(), platform[9]->getHeight() - 3))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < platform[9]->getY() + platform[9]->getHeight())
			{
				y = platform[9]->getY() + platform[9]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, platform[10]->getX(), platform[10]->getY() + 3, platform[10]->getWidth(), platform[10]->getHeight() - 3))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < platform[10]->getY() + platform[10]->getHeight())
			{
				y = platform[10]->getY() + platform[10]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, platform[11]->getX(), platform[11]->getY() + 3, platform[11]->getWidth(), platform[11]->getHeight() - 3))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < platform[11]->getY() + platform[11]->getHeight())
			{
				y = platform[11]->getY() + platform[11]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, platform[12]->getX(), platform[12]->getY() + 3, platform[12]->getWidth(), platform[12]->getHeight() - 3))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < platform[12]->getY() + platform[12]->getHeight())
			{
				y = platform[12]->getY() + platform[12]->getHeight();
			}
		}
		//top of ledges
		else if (checkCollide(x, y, w, h, ledges[0]->getX(), ledges[0]->getY() + 5, ledges[0]->getWidth(), ledges[0]->getHeight() - 5))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < ledges[0]->getY() + ledges[0]->getHeight())
			{
				y = ledges[0]->getY() + ledges[0]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, ledges[1]->getX(), ledges[1]->getY() + 5, ledges[1]->getWidth(), ledges[1]->getHeight() - 5))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < ledges[1]->getY() + ledges[1]->getHeight())
			{
				y = ledges[1]->getY() + ledges[1]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, ledges[2]->getX(), ledges[2]->getY() + 5, ledges[2]->getWidth(), ledges[2]->getHeight() - 5))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < ledges[2]->getY() + ledges[2]->getHeight())
			{
				y = ledges[2]->getY() + ledges[2]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, ledges[3]->getX(), ledges[3]->getY() + 5, ledges[3]->getWidth(), ledges[3]->getHeight() - 5))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < ledges[3]->getY() + ledges[3]->getHeight())
			{
				y = ledges[3]->getY() + ledges[3]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, ledges[4]->getX(), ledges[4]->getY() + 5, ledges[4]->getWidth(), ledges[4]->getHeight() - 5))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < ledges[4]->getY() + ledges[4]->getHeight())
			{
				y = ledges[4]->getY() + ledges[4]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, ledges[5]->getX(), ledges[5]->getY() + 5, ledges[5]->getWidth(), ledges[5]->getHeight() - 5))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < ledges[5]->getY() + ledges[5]->getHeight())
			{
				y = ledges[5]->getY() + ledges[5]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, ledges[6]->getX(), ledges[6]->getY() + 5, ledges[6]->getWidth(), ledges[6]->getHeight() - 5))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < ledges[6]->getY() + ledges[6]->getHeight())
			{
				y = ledges[6]->getY() + ledges[6]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, ledges[7]->getX(), ledges[7]->getY() + 5, ledges[7]->getWidth(), ledges[7]->getHeight() - 5))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < ledges[7]->getY() + ledges[7]->getHeight())
			{
				y = ledges[7]->getY() + ledges[7]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, ledges[8]->getX(), ledges[8]->getY() + 5, ledges[8]->getWidth(), ledges[8]->getHeight() - 5))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < ledges[8]->getY() + ledges[8]->getHeight())
			{
				y = ledges[8]->getY() + ledges[8]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, ledges[9]->getX(), ledges[9]->getY() + 5, ledges[9]->getWidth(), ledges[9]->getHeight() - 5))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < ledges[9]->getY() + ledges[9]->getHeight())
			{
				y = ledges[9]->getY() + ledges[9]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, ledges[10]->getX(), ledges[10]->getY() + 5, ledges[10]->getWidth(), ledges[10]->getHeight() - 5))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < ledges[10]->getY() + ledges[10]->getHeight())
			{
				y = ledges[10]->getY() + ledges[10]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, ledges[11]->getX(), ledges[11]->getY() + 5, ledges[11]->getWidth(), ledges[11]->getHeight() - 5))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < ledges[11]->getY() + ledges[11]->getHeight())
			{
				y = ledges[11]->getY() + ledges[11]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, ledges[12]->getX(), ledges[12]->getY() + 5, ledges[12]->getWidth(), ledges[12]->getHeight() - 5))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < ledges[12]->getY() + ledges[12]->getHeight())
			{
				y = ledges[12]->getY() + ledges[12]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, ledges[13]->getX(), ledges[13]->getY() + 5, ledges[13]->getWidth(), ledges[13]->getHeight() - 5))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < ledges[13]->getY() + ledges[13]->getHeight())
			{
				y = ledges[13]->getY() + ledges[13]->getHeight();
			}
		}
		else if (checkCollide(x, y, w, h, ledges[14]->getX(), ledges[14]->getY() + 5, ledges[14]->getWidth(), ledges[14]->getHeight() - 5))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < ledges[14]->getY() + ledges[14]->getHeight())
			{
				y = ledges[14]->getY() + ledges[14]->getHeight();
			}
		}
		else
		{
			jump = true;
			gravity.y = -1000.0f;
		}

		//bottom of platforms and ledges
		if (checkCollide(x, y, w, h, platform[3]->getX(), platform[3]->getY() - 3, platform[3]->getWidth(), platform[3]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, platform[4]->getX(), platform[4]->getY() - 3, platform[4]->getWidth(), platform[4]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, platform[5]->getX(), platform[5]->getY() - 3, platform[5]->getWidth(), platform[5]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, platform[6]->getX(), platform[6]->getY() - 3, platform[6]->getWidth(), platform[6]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, platform[7]->getX(), platform[7]->getY() - 3, platform[7]->getWidth(), platform[7]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, platform[8]->getX(), platform[8]->getY() - 3, platform[8]->getWidth(), platform[8]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, platform[9]->getX(), platform[9]->getY() - 3, platform[9]->getWidth(), platform[9]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, platform[10]->getX(), platform[10]->getY() - 3, platform[10]->getWidth(), platform[10]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, platform[11]->getX(), platform[11]->getY() - 3, platform[11]->getWidth(), platform[11]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, platform[12]->getX(), platform[12]->getY() - 3, platform[12]->getWidth(), platform[12]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, ledges[0]->getX(), ledges[0]->getY() - 3, ledges[0]->getWidth(), ledges[0]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, ledges[1]->getX(), ledges[1]->getY() - 3, ledges[1]->getWidth(), ledges[1]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, ledges[2]->getX(), ledges[2]->getY() - 3, ledges[2]->getWidth(), ledges[2]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, ledges[3]->getX(), ledges[3]->getY() - 3, ledges[3]->getWidth(), ledges[3]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, ledges[4]->getX(), ledges[4]->getY() - 3, ledges[4]->getWidth(), ledges[4]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, ledges[5]->getX(), ledges[5]->getY() - 3, ledges[5]->getWidth(), ledges[5]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, ledges[6]->getX(), ledges[6]->getY() - 3, ledges[6]->getWidth(), ledges[6]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, ledges[7]->getX(), ledges[7]->getY() - 3, ledges[7]->getWidth(), ledges[7]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, ledges[8]->getX(), ledges[8]->getY() - 3, ledges[8]->getWidth(), ledges[8]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, ledges[9]->getX(), ledges[9]->getY() - 3, ledges[9]->getWidth(), ledges[9]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, ledges[10]->getX(), ledges[10]->getY() - 3, ledges[10]->getWidth(), ledges[10]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, ledges[11]->getX(), ledges[11]->getY() - 3, ledges[11]->getWidth(), ledges[11]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, ledges[12]->getX(), ledges[12]->getY() - 3, ledges[12]->getWidth(), ledges[12]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, ledges[13]->getX(), ledges[13]->getY() - 3, ledges[13]->getWidth(), ledges[13]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		if (checkCollide(x, y, w, h, ledges[14]->getX(), ledges[14]->getY() - 3, ledges[14]->getWidth(), ledges[14]->getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
	}
	//player velocity affected by gravity per 60 frames	
	velocity.y += gravity.y * (1.0f / 60.0f);

	//if the player falls off the map
	if (y < -250)
	{
		y = 100;
		x = 120;
		//lives =  lives - 1;
		dead = true;
		mainCharacter.set_scale(20, 20);
	}

}

void bottomTopCollision4()
{
	
	//platforms
	w0x = 0, w0y = 0, w0w = 70, w0h = 720;
	p1x = 0, p1y = 0, pw = 225, ph = 15;
	p2x = 160, p2y = 0, p2w = 200, p2h = 720;

	//SIDE OF PLATFORM COLLISION CHECK IN MOVEMENT FOR PLAYER
	//top of platforms and ledges
	for (int i = 0; i < platform.size(); i++)
	{
		if (checkCollide(x, y, w, h, platform[0]->getX(), platform[0]->getY() + 3, platform[0]->getWidth(), platform[0]->getHeight() - 3))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < platform[0]->getY() + platform[0]->getHeight())
			{
				y = platform[0]->getY() + platform[0]->getHeight();
			}
		}
		else
		{
			jump = true;
			gravity.y = -1000.0f;
		}
	}
	//player velocity affected by gravity per 60 frames	
	velocity.y += gravity.y * (1.0f / 60.0f);

	//if the player falls off the map
	if (y < -250)
	{
		y = 100;
		x = 120;
		//lives =  lives - 1;
		dead = true;
		mainCharacter.set_scale(20, 20);
	}

}

//draw/update sprites
void drawUpdate()
{
	backGround.draw();
	if (mainMenu)
	{
		mainM.draw();
	}
	if (level1)
	{
		levelTwo.draw();
		door.draw();
	}
	if (level2)
	{
		level.draw();
		door.draw();
	}
	if (level3)
	{
		levelThree.draw();
	}
	door.set_position(dx, dy);
	if (taken == false)
	{
		EMPterminal.set_frame(0);
	}
	else if (taken == true)
	{
		EMPterminal.set_frame(1);
	}

	EMPterminal.set_position(terminal1.getX(), terminal1.getY());
	if (level3)
	{
		EMPterminal.draw();
	}
	//update sprite(s) position per frame//////
	mainCharacter.set_position(player.getX(), player.getY());
	guard1.set_position(enemy1.getX(), enemy1.getY());
	guard2.set_position(enemy2.getX(), enemy2.getY());
	guard3.set_position(enemy3.getX(), enemy3.getY());
	guard4.set_position(enemy4.getX(), enemy4.getY());
	guard5.set_position(enemy5.getX(), enemy5.getY());
	keyholder1.set_position(keyhold1.getX(), keyhold1.getY());
	useEMP.set_position(player.getX(), player.getY());
	if (level1)
	{
		if (enemy1Turn.secondsPassed() <= 5)
		{
			Flashlight.set_position(enemy1.getX() - 4, enemy1.getY() - 3);
		}
		else
		{
			Flashlight.set_position(enemy1.getX() + 4, enemy1.getY() - 3);
		}
	}
	else if (level2)
	{ 
		if (enemyVelocity.x < 0)
		{
			Flashlight.set_position(enemy1.getX() - 4, enemy1.getY() - 3);
		}
		else
		{
			Flashlight.set_position(enemy1.getX() + 4, enemy1.getY() - 3);
		}
		if (enemy2Velocity.x < 0)
		{
			Flashlight2.set_position(enemy2.getX() - 4, enemy2.getY() - 3);
		}
		else
		{
			Flashlight2.set_position(enemy2.getX() + 4, enemy2.getY() - 3);
		}
	}
	else if (level3)
	{
		if (enemyVelocity.x < 0)
		{
			Flashlight.set_position(enemy1.getX() - 4, enemy1.getY() - 3);
		}
		else
		{
			Flashlight.set_position(enemy1.getX() + 4, enemy1.getY() - 3);
		}
		if (enemy2Velocity.x < 0)
		{
			Flashlight2.set_position(enemy2.getX() - 4, enemy2.getY() - 3);
		}
		else
		{
			Flashlight2.set_position(enemy2.getX() + 4, enemy2.getY() - 3);
		}
		if (enemy4Velocity.x < 0)
		{
			Flashlight3.set_position(enemy4.getX() - 4, enemy4.getY() - 3);
		}
		else
		{
			Flashlight3.set_position(enemy4.getX() + 4, enemy4.getY() - 3);
		}
		if (enemy5Velocity.x < 0)
		{
			Flashlight4.set_position(enemy5.getX() - 4, enemy5.getY() - 3);
		}
		else
		{
			Flashlight4.set_position(enemy5.getX() + 4, enemy5.getY() - 3);
		}
	}
	///////////////////////////////////////////
	//draw sprite(s) per frame//////
	switch (playeranim)
	{
	case NOTHING:
		if(hiding == false)
			mainCharacter.draw();
		mainCharacter.next_frame(); //update animation frames
		break;
	case EMP:
		useEMP.set_animation("throw");
		useEMP.draw();
		if (left == true)
		{
			useEMP.set_scale(-20, 20);
		}
		else if (right == true)
		{
			useEMP.set_scale(20, 20);
		}
		if (useEMP.get_curr_frame() == 25)
		{
			player.useEMP(guards);
		}
		if (useEMP.get_curr_frame() >= 34)
		{
			playeranim = NOTHING;
			useEMP.set_frame(0);
		}
		else
		{
			useEMP.next_frame();
		}
	}
		
	guard3.draw();

	//SHADER, USED FOR LIGHTING////////////
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	spotlight.set_position(spotLight1.getX() + 10, spotLight1.getY());
	spotlight2.set_position(spotLight2.getX() + 10, spotLight2.getY());
	if (spotLight1.flashlight)
	{
		spotlight.draw();
		if (spotted == false)
		{
			Flashlight.draw();
			Flashlight2.draw();
			Flashlight3.draw();
			Flashlight4.draw();
		}
	}
	if (spotLight2.flashlight)
	{
		spotlight2.draw();
	}
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	guard1.draw();
	guard2.draw();
	guard4.draw();
	guard5.draw();
	if (level1)
	{
		keyholder1.draw();
		if (player.key == false)
		{
			keyGuard.draw();
		}
	}
	if (spotted == true) //if player is spotted
	{
		//set animation to shoot
		guard1.set_animation("guardShoot"); 
		guard2.set_animation("guardShoot");
		guard3.set_animation("guardShoot");
		guard4.set_animation("guardShoot");
		guard5.set_animation("guardShoot");
		keyholder1.set_animation("guardShoot");
		mainCharacter.set_animation("anim_0");
		y += velocity.y * (1.0f / 60.0f);
		if (deathSeconds < 45)
		{
			mainCharacter.set_frame(0);
			deathSeconds += 1;
		}
		else
		{
			mainCharacter.set_frame(18);
		}

		shootSeconds += 1;

		if (shootSeconds > 90)
		{
			spotted = false;
			dead = true;
		}

	}
	guard1.next_frame(); //update animation frames
	guard2.next_frame();
	guard3.next_frame();
	guard4.next_frame();
	guard5.next_frame();
	keyholder1.next_frame();
						 ///////////////////////////////

	if (level3)
	{
		Chest.draw();
	}
	Chest.set_animation("open");

	if (open == false)
	{
		Chest.set_frame(0);
	}
	else if (open == true)
	{
		if (Chest.get_curr_frame() < 78)
			Chest.next_frame();
		else
		{
			Chest.set_frame(79);
			won = true;
		}
	}

}

//load sprites
void loadSprites()
{
	//background textures
	backGround.load_sprite_image("assets/images/backGround.png")
		.set_position(0, 0);

	mainM.load_sprite_image("assets/images/Main Menu.png")
		.set_position(0, 0);

	level.load_sprite_image("assets/images/Level_1-2.png")
		.set_position(0, 0)
		.set_scale(1280, 720);

	levelTwo.load_sprite_image("assets/images/Level_1-1.png")
		.set_position(0, 0)
		.set_scale(1280, 720);

	levelThree.load_sprite_image("assets/images/Level_2-1.png")
		.set_position(0, 0)
		.set_scale(1280, 720);

	//UI textures
	eye.load_sprite_image("assets/images/EyeVisible.png")
		.set_sprite_frame_size(1024, 1024, false)
		.set_position(1100, 575)
		.set_scale(200, 200)
		.push_frame("eye", 0, 0)
		.push_frame("eye", 0, 1024);
	eye.set_animation("eye");

	health.load_sprite_image("assets/images/Health UI.png")
		.set_sprite_frame_size(256, 256, false)
		.set_position(10, 600)
		.set_scale(150, 150)
		.push_frame("health", 0, 0)
		.push_frame("health1", 256, 0)
		.push_frame("health2", 512, 0)
		.push_frame("health3", 768, 0)
		.set_animation("health");

	EMPicon.load_sprite_image("assets/images/EMP.png")
		.set_position(-10, 550)
		.set_scale(100, 100);

	keyIcon.load_sprite_image("assets/images/Key.png")
		.set_position(-10, 480)
		.set_scale(100, 100);

	doorNotice.load_sprite_image("assets/images/doorNotice.png")
		.set_position(0, 0);

	hideScreen.load_sprite_image("assets/images/hideScreen.png")
		.set_position(0, 0);

	tab.load_sprite_image("assets/images/TAB.png")
		.set_position(0, 0);

	controlScheme.load_sprite_image("assets/images/Controls.png")
		.set_position(0, 0);

	//door
	door.load_sprite_image("assets/images/Door.png");
	//chest
	Chest.load_sprite_image("assets/images/Opening Chest.png")
		.set_sprite_frame_size(128, 128, false)
		.set_position(1225, 599.4)
		.set_scale(30, 30);

	//key the guard holds
	keyGuard.load_sprite_image("assets/images/Key.png")
		.set_scale(8, 8)
		.set_center(0.5, 0.0);

	for (int r = 7; r > -1; r--)
	{
		unsigned int row = 128 * r;
		Chest.push_frame_row("open", 0, row, 128, 0, 10);
	}

	//terminal sprites
	EMPterminal.load_sprite_image("assets/images/terminal.png")
		.set_sprite_frame_size(32, 32)
		.set_scale(15, 15)
		.push_frame("terminal", 0, 32)
		.push_frame("terminal", 0, 0)
		.set_animation("terminal")
		.set_position(terminal1.getX(), terminal1.getY());
		
	//create player sprite
	mainCharacter.load_sprite_image("assets/images/RighteousThiefAnim.png")
		.set_sprite_frame_size(96, 96, false)
		.set_scale(20, 20)
		.set_position(player.getX(), player.getY())
		.set_center(0.5, 0.0); //SET X TO MIDDLE TO ALLOW SPRITE TO FLIP
							   //grab the rows of the spritesheet
	for (int r = 0; r < 4; r++)
	{
		std::string pid = "anim_" + std::to_string(r);
		unsigned int row = 96 * r;
		mainCharacter.push_frame_row(pid, 0, row, 96, 0, 28);
	}
	mainCharacter.set_animation("anim_1");
	mainCharacter.push_frame_row("jump", 0, 96, 96, 0, 14);
	mainCharacter.push_frame_row("fall", 1344, 96, 96, 0, 14);

	useEMP.load_sprite_image("assets/images/EMP throw.png")
		.set_sprite_frame_size(64, 64, false)
		.set_scale(20, 20)
		.set_position(player.getX(), player.getY())
		.set_center(0.5, 0.0);
	for (int r = 6; r > -1; r--)
	{
		unsigned int row = 64 * r;
		useEMP.push_frame_row("throw", 0, row, 64, 0, 5);
	}
	useEMP.set_animation("throw");

	//create guard sprite
	guard1.load_sprite_image("assets/images/UNITYEnemyAnim.png")
		.set_sprite_frame_size(96, 96, false)
		.set_scale(20, 20)
		.set_position(enemy1.getX(), enemy1.getY())
		.set_center(0.5, 0.0); //SET X TO MIDDLE TO ALLOW SPRITE TO FLIP
							   //grab the rows of the spritesheet
	for (int r = 3; r < 7; r++)
	{
		unsigned int row = 96 * r;
		guard1.push_frame_row("guardWalk", 0, row, 96, 0, 14);
	}
	guard1.set_animation("guardWalk");

	for (int r = 2; r >= 0; r--)
	{
		unsigned int row = 96 * r;
		guard1.push_frame_row("guardShoot", 0, row, 96, 0, 14);
	}

	//create 2nd guard sprite
	guard2.load_sprite_image("assets/images/UNITYEnemyAnim.png")
		.set_sprite_frame_size(96, 96, false)
		.set_scale(20, 20)
		.set_position(enemy2.getX(), enemy2.getY())
		.set_center(0.5, 0.0); //SET X TO MIDDLE TO ALLOW SPRITE TO FLIP
							   //grab the rows of the spritesheet
	for (int r = 3; r < 7; r++)
	{
		unsigned int row = 96 * r;
		guard2.push_frame_row("guardWalk", 0, row, 96, 0, 14);
	}
	guard2.set_animation("guardWalk");

	for (int r = 2; r >= 0; r--)
	{
		unsigned int row = 96 * r;
		guard2.push_frame_row("guardShoot", 0, row, 96, 0, 14);
	}

	//create 3rd guard sprite
	guard3.load_sprite_image("assets/images/UNITYEnemyAnim.png")
		.set_sprite_frame_size(96, 96, false)
		.set_scale(20, 20)
		.set_position(enemy2.getX(), enemy2.getY())
		.set_center(0.5, 0.0); //SET X TO MIDDLE TO ALLOW SPRITE TO FLIP
							   //grab the rows of the spritesheet
	for (int r = 3; r < 7; r++)
	{
		unsigned int row = 96 * r;
		guard3.push_frame_row("guardWalk", 0, row, 96, 0, 14);
	}
	guard3.set_animation("guardWalk");

	for (int r = 2; r >= 0; r--)
	{
		unsigned int row = 96 * r;
		guard3.push_frame_row("guardShoot", 0, row, 96, 0, 14);
	}

	//create 5th guard sprite
	guard4.load_sprite_image("assets/images/UNITYEnemyAnim.png")
		.set_sprite_frame_size(96, 96, false)
		.set_scale(20, 20)
		.set_position(enemy2.getX(), enemy2.getY())
		.set_center(0.5, 0.0); //SET X TO MIDDLE TO ALLOW SPRITE TO FLIP
							   //grab the rows of the spritesheet
	for (int r = 3; r < 7; r++)
	{
		unsigned int row = 96 * r;
		guard4.push_frame_row("guardWalk", 0, row, 96, 0, 14);
	}
	guard4.set_animation("guardWalk");

	for (int r = 2; r >= 0; r--)
	{
		unsigned int row = 96 * r;
		guard4.push_frame_row("guardShoot", 0, row, 96, 0, 14);
	}

	//create 5th guard sprite
	guard5.load_sprite_image("assets/images/UNITYEnemyAnim.png")
		.set_sprite_frame_size(96, 96, false)
		.set_scale(20, 20)
		.set_position(enemy2.getX(), enemy2.getY())
		.set_center(0.5, 0.0); //SET X TO MIDDLE TO ALLOW SPRITE TO FLIP
							   //grab the rows of the spritesheet
	for (int r = 3; r < 7; r++)
	{
		unsigned int row = 96 * r;
		guard5.push_frame_row("guardWalk", 0, row, 96, 0, 14);
	}
	guard5.set_animation("guardWalk");

	for (int r = 2; r >= 0; r--)
	{
		unsigned int row = 96 * r;
		guard5.push_frame_row("guardShoot", 0, row, 96, 0, 14);
	}
	//create 1st KeyHolder sprite
	keyholder1.load_sprite_image("assets/images/UNITYKeyHolderAnim.png")
		.set_sprite_frame_size(40, 40, false)
		.set_scale(20, 20)
		.set_position(keyhold1.getX(), keyhold1.getY())
		.set_center(0.5, 0.0); //SET X TO MIDDLE TO ALLOW SPRITE TO FLIP
							   //grab the rows of the spritesheet
	for (int r = 3; r < 7; r++)
	{
		unsigned int row = 40 * r;
		keyholder1.push_frame_row("guardWalk", 0, row, 40, 0, 14);
	}
	keyholder1.set_animation("guardWalk");

	for (int r = 2; r >= 0; r--)
	{
		unsigned int row = 40 * r;
		keyholder1.push_frame_row("guardShoot", 0, row, 40, 0, 14);
	}

	//flashlight sprites
	Flashlight.load_sprite_image("assets/images/Flashlight.png")
		.set_scale(200, 80)
		.set_center(1.0f, 0.0f)
		.set_position(enemy1.getX() + 5, enemy1.getY() - 5);

	Flashlight2.load_sprite_image("assets/images/Flashlight.png")
		.set_scale(200, 80)
		.set_center(1.0f, 0.0f)
		.set_position(enemy2.getX() + 5, enemy2.getY() - 5);

	Flashlight3.load_sprite_image("assets/images/Flashlight.png")
		.set_scale(200, 80)
		.set_center(1.0f, 0.0f)
		.set_position(enemy1.getX() + 5, enemy1.getY() - 5);

	Flashlight4.load_sprite_image("assets/images/Flashlight.png")
		.set_scale(200, 80)
		.set_center(1.0f, 0.0f)
		.set_position(enemy2.getX() + 5, enemy2.getY() - 5);

	//spotlight sprites
	spotlight.load_sprite_image("assets/images/Flashlight.png")
		.set_scale(70, 60)
		.set_center(1.0f, 0.0f)
		.set_rotation(90)
		.set_position(spotLight1.getX(), spotLight1.getY());

	spotlight2.load_sprite_image("assets/images/Flashlight.png")
		.set_scale(70, 60)
		.set_center(1.0f, 0.0f)
		.set_rotation(90)
		.set_position(spotLight1.getX(), spotLight1.getY());

}

//enemy location/pathing info
void enemyInfo()
{
	//1st enemy pathing info//////
	if (level1)
	{
		ex = 674, ey = 290;
		if (enemy1Turn.secondsPassed() <= 5)
		{
			enemyVelocity.x = -0.0f; //LEFT
			if (spotted == false)
			{
				guard1.set_scale(-20, 20); //flip sprite
				Flashlight.set_scale(50, 20); //flip flashlight
				enemy1.setDirection(1, 0);
				guard1.set_animation("guardWalk");
				guard1.set_frame(30);
			}
		}
		else if (enemy1Turn.secondsPassed() > 5)
		{
			enemyVelocity.x = 0.0f; //RIGHT
			if (spotted == false)
			{
				guard1.set_scale(20, 20); //flip sprite
				Flashlight.set_scale(-50, 20); //flip flashlight
				enemy1.setDirection(-1, 0);
				guard1.set_animation("guardWalk");
				guard1.set_frame(30);
			}
		}
		if (spotted == false)
		{
			ex += enemyVelocity.x * (1.0f / 60.0f); //the enemy's horizontal velocity updated per frame
			ey += enemyVelocity.y * (1.0f / 60.0f); //same as above but this time for vertical velocity
		}

		if (enemy1Turn.secondsPassed() <= 5)
		{
			enemyVelocity.x = -0.0f; //LEFT
			if (spotted == false)
			{
				keyholder1.set_animation("guardWalk");
				keyholder1.set_frame(30);
				keyhold1.setDirection(1, 0);
				keyholder1.set_scale(-20, 20); //flip sprite
				keyGuard.set_position(keyhold1.getX() + 3, keyhold1.getY() - 1);
				keyGuard.set_scale(-8, 8);
			}
		}
		else if (enemy1Turn.secondsPassed() > 5)
		{
			enemyVelocity.x = 0.0f; //RIGHT
			if (spotted == false)
			{
				keyholder1.set_animation("guardWalk");
				keyholder1.set_frame(30);
				keyhold1.setDirection(-1, 0);
				keyholder1.set_scale(20, 20); //flip sprite
				keyGuard.set_position(keyhold1.getX() - 3, keyhold1.getY() - 1);
				keyGuard.set_scale(8, 8);
			}
		}
		if (spotted == false)
		{
			kx += enemyVelocity.x * (1.0f / 60.0f); //the enemy's horizontal velocity updated per frame
			ky += enemyVelocity.y * (1.0f / 60.0f); //same as above but this time for vertical velocity
		}
	}
	else if (level2)
	{
		if (enemy1.getX() >= 400)
		{
			enemyVelocity.x = -50.0f; //LEFT
			guard1.set_scale(-20, 20); //flip sprite
			Flashlight.set_scale(50, 20); //flip flashlight
			enemy1.setDirection(1, 0);
			guard1.set_animation("guardWalk");
		}
		else if (enemy1.getX() <= 270)
		{
			enemyVelocity.x = 50.0f; //RIGHT
			guard1.set_scale(20, 20); //flip sprite
			Flashlight.set_scale(-50, 20); //flip flashlight
			enemy1.setDirection(-1, 0);
			guard1.set_animation("guardWalk");
		}

		if (spotted == false)
		{
			ex2 += enemyVelocity.x * (1.0f / 60.0f); //the enemy's horizontal velocity updated per frame
			ey2 += enemyVelocity.y * (1.0f / 60.0f); //same as above but this time for vertical velocity
		}

		//2nd enemy pathing info
		if (enemy2.getX() >= 1115)
		{
			enemy2Velocity.x = -50.0f; //LEFT
			guard2.set_scale(-20, 20); //flip sprite
			Flashlight2.set_scale(50, 20); //flip flashlight
			enemy2.setDirection(1, 0);
			guard2.set_animation("guardWalk");
		}
		else if (enemy2.getX() <= 930)
		{
			enemy2Velocity.x = 50.0f; //RIGHT
			guard2.set_scale(20, 20); //flip sprite
			Flashlight2.set_scale(-50, 20); //flip flashlight
			enemy2.setDirection(-1, 0);
			guard2.set_animation("guardWalk");
		}
		if (spotted == false)
		{
			ex3 += enemy2Velocity.x * (1.0f / 60.0f); //the enemy's horizontal velocity updated per frame
			ey3	+= enemy2Velocity.y * (1.0f / 60.0f); //same as above but this time for vertical velocity
		}
		//3rd enemy pathing info
		if (enemy3.getX() >= 580)
		{
			enemy3Velocity.x = -50.0f; //LEFT
			guard3.set_scale(-20, 20); //flip sprite
			enemy3.setDirection(1, 0);
			guard3.set_animation("guardWalk");
		}
		else if (enemy3.getX() <= 370)
		{
			enemy3Velocity.x = 50.0f; //RIGHT
			guard3.set_scale(20, 20); //flip sprite
			enemy3.setDirection(-1, 0);
			guard3.set_animation("guardWalk");
		}
		if (spotted == false)
		{
			ex4 += enemy3Velocity.x * (1.0f / 60.0f); //the enemy's horizontal velocity updated per frame
			ey4 += enemy3Velocity.y * (1.0f / 60.0f); //same as above but this time for vertical velocity
		}


	}
	else if (level3)
	{
		if (enemy1.getX() >= 1235)
		{
			enemyVelocity.x = -50.0f; //LEFT
			guard1.set_scale(-20, 20); //flip sprite
			Flashlight.set_scale(50, 20); //flip flashlight
			enemy1.setDirection(1, 0);
			guard1.set_animation("guardWalk");
		}
		else if (enemy1.getX() <= 1000)
		{
			enemyVelocity.x = 50.0f; //RIGHT
			guard1.set_scale(20, 20); //flip sprite
			Flashlight.set_scale(-50, 20); //flip flashlight
			enemy1.setDirection(-1, 0);
			guard1.set_animation("guardWalk");
		}

		if (spotted == false)
		{
			ex5 += enemyVelocity.x * (1.0f / 60.0f); //the enemy's horizontal velocity updated per frame
			ey5 += enemyVelocity.y * (1.0f / 60.0f); //same as above but this time for vertical velocity
		}

		//2nd enemy pathing info
		if (enemy2.getX() >= 680)
		{
			enemy2Velocity.x = -50.0f; //LEFT
			guard2.set_scale(-20, 20); //flip sprite
			Flashlight2.set_scale(50, 20); //flip flashlight
			enemy2.setDirection(1, 0);
			guard2.set_animation("guardWalk");
		}
		else if (enemy2.getX() <= 490)
		{
			enemy2Velocity.x = 50.0f; //RIGHT
			guard2.set_scale(20, 20); //flip sprite
			Flashlight2.set_scale(-50, 20); //flip flashlight
			enemy2.setDirection(-1, 0);
			guard2.set_animation("guardWalk");
		}
		if (spotted == false)
		{
			ex6 += enemy2Velocity.x * (1.0f / 60.0f); //the enemy's horizontal velocity updated per frame
			ey6 += enemy2Velocity.y * (1.0f / 60.0f); //same as above but this time for vertical velocity
		}
		//3rd enemy pathing info
		if (enemy3.getX() >= 1075)
		{
			enemy3Velocity.x = -50.0f; //LEFT
			guard3.set_scale(-20, 20); //flip sprite
			enemy3.setDirection(1, 0);
			guard3.set_animation("guardWalk");
		}
		else if (enemy3.getX() <= 795)
		{
			enemy3Velocity.x = 50.0f; //RIGHT
			guard3.set_scale(20, 20); //flip sprite
			enemy3.setDirection(-1, 0);
			guard3.set_animation("guardWalk");
		}
		if (spotted == false)
		{
			ex7 += enemy3Velocity.x * (1.0f / 60.0f); //the enemy's horizontal velocity updated per frame
			ey7 += enemy3Velocity.y * (1.0f / 60.0f); //same as above but this time for vertical velocity
		}
		//4th enemy pathing info
		if (enemy4.getX() >= 990)
		{
			enemy4Velocity.x = -50.0f; //LEFT
			guard4.set_scale(-20, 20); //flip sprite
			Flashlight3.set_scale(50, 20); //flip flashlight
			enemy4.setDirection(1, 0);
			guard4.set_animation("guardWalk");
		}
		else if (enemy4.getX() <= 630)
		{
			enemy4Velocity.x = 50.0f; //RIGHT
			guard4.set_scale(20, 20); //flip sprite
			Flashlight3.set_scale(-50, 20); //flip flashlight
			enemy4.setDirection(-1, 0);
			guard4.set_animation("guardWalk");
		}
		if (spotted == false)
		{
			ex8 += enemy4Velocity.x * (1.0f / 60.0f); //the enemy's horizontal velocity updated per frame
			ey8 += enemy4Velocity.y * (1.0f / 60.0f); //same as above but this time for vertical velocity
		}
		//5th enemy pathing info
		if (enemy5.getX() >= 870)
		{
			enemy5Velocity.x = -50.0f; //LEFT
			guard5.set_scale(-20, 20); //flip sprite
			Flashlight4.set_scale(50, 20); //flip flashlight
			enemy5.setDirection(1, 0);
			guard5.set_animation("guardWalk");
		}
		else if (enemy5.getX() <= 540)
		{
			enemy5Velocity.x = 50.0f; //RIGHT
			guard5.set_scale(20, 20); //flip sprite
			Flashlight4.set_scale(-50, 20); //flip flashlight
			enemy5.setDirection(-1, 0);
			guard5.set_animation("guardWalk");
		}
		if (spotted == false)
		{
			ex9 += enemy5Velocity.x * (1.0f / 60.0f); //the enemy's horizontal velocity updated per frame
			ey9 += enemy5Velocity.y * (1.0f / 60.0f); //same as above but this time for vertical velocity
		}
	}
	///////////////////////
}

//drawing of UI elements
void UIElements()
{
	Text::set_color(1.0f, 1.0f, 1.0f);
	eye.draw();
	health.draw();
	tab.draw();

	if (lives == 3)
	{
		health.set_animation("health");
	}
	if (lives == 2)
	{
		health.set_animation("health1");
	}
	if (lives == 1)
	{
		health.set_animation("health2");
	}
	if (lives == 0)
	{
		health.set_animation("health3");
	}
	if (player.getEMP() > 0)
	{
		EMPicon.draw();
	}
	if (player.key)
	{
		keyIcon.draw();
	}
	for (int i = 0; i < guards.size(); i++)
	{
		if (hiding == false)
		{
			if (guards[0]->FOV(player.getCoord()))
			{
				eye.set_frame(0);
				if (guards[0]->weapon == true)
				{
					spotted = true;
				}
			}
			else if (guards[1]->FOV(player.getCoord()))
			{
				eye.set_frame(0);
				if (guards[1]->weapon == true)
				{
					spotted = true;
				}
			}
			else if (guards[2]->FOV(player.getCoord()))
			{
				eye.set_frame(0);
				if (guards[2]->weapon == true)
				{
					spotted = true;
				}
			}
			else if (guards[3]->FOV(player.getCoord()))
			{
				eye.set_frame(0);
				if (guards[3]->weapon == true)
				{
					spotted = true;
				}
			}
			else if (guards[4]->FOV(player.getCoord()))
			{
				eye.set_frame(0);
				if (guards[4]->weapon == true)
				{
					spotted = true;
				}
			}
			else if (guards[5]->FOV(player.getCoord()))
			{
				eye.set_frame(0);
				if (guards[5]->weapon == true)
				{
					spotted = true;
				}
			}
			else
			{
				//Text::draw_string("Hidden", "FFF", 1150, 690, 0.75f);
				eye.set_frame(1);
			}
		}
	}
	//USE THIS FOR ENEMIES WITHOUT FLASHLIGHTS
	if (spotLight1.FOV(player.getCoord()) || spotLight2.FOV(player.getCoord()))
	{ 
		if (enemy3.FOV(player.getCoord()))
			spotted = true;
	}

	if (spotLight2.FOV(player.getCoord()))
	{
		if (keyhold1.FOV(player.getCoord()))
			spotted = true;
	}

	if (hiding)
	{

	}

	///////////////////////////////////////

}

//reset lighting
void resetEMP(std::vector<KeyHolder*> &guardo)
{
	for (int i = 0; i < guardo.size(); i++)
	{
		guardo[i]->flashlight = true;
	}
}

//main function aka the boss
int main()
{
	Window& game = Window::get_game_window();
	game.init("Corrupt", 1280, 720, false)
		.set_clear_color(0, 255, 255);
	Text::load_font("assets/FFFFORWA.TTF", "FFF");

	//setup timers
	enemy1Turn.countDown();
	if (transition)
	{
		transitionTimer.countDown();
	}
	EMPTimer.countDown();

	//load sprites/textures/////
	loadSprites();
	////////////////////////////

	//push back guards
	guards.push_back(&spotLight1);
	guards.push_back(&spotLight2);
	guards.push_back(&enemy1);
	guards.push_back(&enemy2);
	guards.push_back(&enemy4);
	guards.push_back(&enemy5);

	//push back platforms
	platform.push_back(&platform1);
	platform.push_back(&platform2);
	platform.push_back(&platform3);
	platform.push_back(&platform4);
	platform.push_back(&platform5);
	platform.push_back(&platform6);
	platform.push_back(&platform7);
	platform.push_back(&platform8);
	platform.push_back(&platform9);
	platform.push_back(&platform10);
	platform.push_back(&platform11);
	platform.push_back(&platform12);
	platform.push_back(&platform13);

	//push back ledges
	ledges.push_back(&ledge1);
	ledges.push_back(&ledge2);
	ledges.push_back(&ledge3);
	ledges.push_back(&ledge4);
	ledges.push_back(&ledge5);
	ledges.push_back(&ledge6);
	ledges.push_back(&ledge7);
	ledges.push_back(&ledge8);
	ledges.push_back(&ledge9);
	ledges.push_back(&ledge10);
	ledges.push_back(&ledge11);
	ledges.push_back(&ledge12);
	ledges.push_back(&ledge13);
	ledges.push_back(&ledge14);
	ledges.push_back(&ledge15);

	//GAME LOOP, 60 FRAMES
	//EVERYTHING UPDATES IN HERE
	while (game.update(60))
	{
		//reset timers
		if (enemy1Turn.secondsPassed() == 11)
		{
			enemy1Turn.resetSeconds();
		}
		if (transition == false)
		{
			if (transitionTimer.secondsPassed() > 1)
			{
				transitionTimer.resetSeconds();
			}
		}
		if (timeEMP == false)
		{
			if (EMPTimer.secondsPassed() > 1)
			{
				EMPTimer.resetSeconds();
			}
		}

		//CAMERA SETTINGS/////////
		float width = 1280.0f * 0.5f;
		float height = 720.0f * 0.5f;
		float cx, cy;
		/////////////////////////

		//CLAMP THE MAX AND MIN OF CAMERA COORDS////////
		cx = std::max(0.0f, std::min(x - 200.0f, 1280.0f - 400));
		cy = std::max(0.0f, std::min(y - 115.0f, 720.0f - 250));
		////////////////////////////////////////////////

		//NOW SET THE CAMERA/////////////////////
		game.set_ortho_window(cx, cy, 400, 200);
		////////////////////////////////////////

		//get keyboard function per frame
		game.set_keyboard_callback(KeyboardFunc);

		//draw and update sprites//////
		drawUpdate();
		///////////////////////////////

		//player movement info//////
		Movement();
		////////////////////////////

		//collision info///////
		if (mainMenu)
		{
			bottomTopCollision4();
			if (x >= 155)
			{
				mainMenu = false;
				level1 = true;
			}
			else if (x <= 71)
			{
				exit(1);
			}
		}
		else if (level1)
			bottomTopCollision2();
		else if (level2)
		{
			bottomTopCollision();
		}
		else if (level3)
		{
			bottomTopCollision3();
		}
		///////////////////////

		//initialize collision object properties////////
		SetupCollisionProperties();
		////////////////////////////////////////////////

		//enemy pathing info//////
		enemyInfo();
		///////////////////////

		
		//jumping animation
		if (spotted == false)
		{
			if (jump == true)
			{
				if (velocity.y > 0)
					mainCharacter.set_animation("jump");
				else
					mainCharacter.set_animation("fall");
			}
		}

		//now this is important
		//we actually have to update the player position per frame or nothing will happen unless we are hitting a key
		//so simply just set the coord of the player using the x and y variables
		player.setCoord(x, y);
		//back up at the drawing of the player, the getX() and getY() will return the updated numbers, so the rectangle will retain these coords
		//As I like to say, easy peasy lemon squeezy
		
		//update enemy positions per frame
		if (level1) //level 1
		{
			keyhold1.setCoord(kx, ky);
			enemy1.setCoord(ex, ey);
			enemy2.setCoord(-100, 0);
			enemy3.setCoord(-100, 0);
			enemy4.setCoord(-100, 0);
			enemy5.setCoord(-100, 0);
			spotLight2.setCoord(sx2, sy2);
		}
		else if (level2) //level2
		{
			enemy5.setCoord(-150, 0);
			enemy4.setCoord(-150, 0);
			enemy3.setCoord(ex4, ey4);
			enemy2.setCoord(ex3, ey3);
			enemy1.setCoord(ex2, ey2);
			keyhold1.setCoord(-150, 0);
			spotLight2.setCoord(sx2, sy2);
		}
		else if (level3) //level3
		{
			enemy5.setCoord(ex9, ey9);
			enemy4.setCoord(ex8, ey8);
			enemy3.setCoord(ex7, ey7);
			enemy2.setCoord(ex6, ey6);
			enemy1.setCoord(ex5, ey5);
			spotLight2.setCoord(-100, 0);
			terminal1.setCOORD(tx, ty);
		}
		else if (mainMenu)
		{
			enemy5.setCoord(1000, 0);
			enemy4.setCoord(1000, 0);
			enemy3.setCoord(1000, 0);
			enemy2.setCoord(1000, 0);
			enemy1.setCoord(1000, 0);
			spotLight2.setCoord(1000, 0);
			//terminal1.setCOORD(tx, ty);
		}
		spotLight1.setCoord(sx, sy);
		spotLight1.setDirection(0.4, 1);
		spotLight2.setDirection(0.35, 1);

		//UI ELEMENTS//////////////////////////
		game.set_ortho_window(0.0f, 0.0f, 1280.0f, 720.0f); //reset ortho matrix for UI elements

		UIElements();
		/////////////////////// ////////////////

		//TRANSITION///////////////////////////
		Shapes rect;
		if (transition == true)
		{
			rect.draw_rectangle(true, 0, 0, 1280, 720, 0);
			rect.set_color(0, 0, 0);
			Text::set_color(1, 1, 1);
			Text::draw_string("Loading...", "FFF", 340, 340, 3);
			if (transitionTimer.secondsPassed() >= 3)
			{
				transition = false;
				transitionTimer.resetSeconds();
			}
		}
		//TIME EMP
		if (timeEMP == true)
		{
			if (EMPTimer.secondsPassed() >= 5)
			{
				timeEMP = false;
				EMPTimer.resetSeconds();
				resetEMP(guards);
			}
		}
		//NOITCE IF PLAYER DOESNT HAVE KEY AND APPROACHES DOOR
		if (player.key == false)
		{
			if (player.getX() >= endX - 5 && player.getY() >= endY && player.getY() <= endY + 20)
			{
				doorNotice.draw();
			}
		}

		//make the screen darker if hiding
		if (hiding)
		{
			hideScreen.draw();
			velocity.x = 0;
		}

		//if pressing tab
		if (controls)
		{
			controlScheme.draw();
		}

		//state if dead
		if (lives >= 0)
		{
			if (dead == true)
			{
				rect.draw_rectangle(true, 0, 0, 1280, 720, 0);
				rect.set_color(0, 0, 0);
				Text::set_color(1, 1, 1);
				Text::draw_string("A life was lost...", "FFF", 140, 340, 3);
				Text::draw_string("Press Enter", "FFF", 500, 200, 1);
				resetEMP(guards);
			}
		}
		else if (lives == -1)
		{
			rect.draw_rectangle(true, 0, 0, 1280, 720, 0);
			rect.set_color(0, 0, 0);
			Text::set_color(1, 1, 1);
			Text::draw_string("GAME OVER", "FFF", 275, 340, 3);
			Text::draw_string("Press Escape", "FFF", 500, 200, 1);
		}
		else if (lives == -2)
		{
			exit(1);
		}

		//state if won
		if (won)
		{
			rect.draw_rectangle(true, 0, 0, 1280, 720, 0);
			rect.set_color(0, 0, 0);
			Text::set_color(1, 1, 1);
			Text::draw_string("You reclaimed the Corrupted Funds!", "FFF", 290, 440, 1);
			Text::draw_string("Thank you for playing our demo/prototype!", "FFF", 250, 340, 1);
			Text::draw_string("Press Escape", "FFF", 500, 150, 1);
		}
		
	}


}