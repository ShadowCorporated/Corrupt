#include "spritelib/spritelib.h"

#include <fstream>
#include <streambuf>
#include <vector>
#include <iostream>
#include "Characters.h"
#include "World Collision.h"
#include <time.h>

using namespace spritelib;

//Sprite customShaderSprite;
//Shader vertexShader, fragmentShader;
//ShaderProgram shaderprogram;

std::vector<KeyHolder*> guards;

Sprite mainCharacter, guard1, backGround, level, eye, health, EMPicon, useEMP, spotlight;

Sprite AdditiveSprite, MultSprite;

std::vector<Sprite*> spritesAddToDraw;
std::vector<Sprite*> spritesMultToDraw;

int lives = 3;

Player player;
float x = 120.0f, y = 471.0f, h = 30, w = 0;

Guard enemy1, spotLight1;
float ex = 750, ey = 107;
float sx = 293, sy = 434;


World_Collision wall0, wall1, wall2, platform1, platform2, platform3, platform4, platform5, platform6, platform7;
float w0x = 0, w0y = 0, w0w = 90, w0h = 1280;
float w1x = 558, w1y = 172, w1w = 40, w1h = 200;
float w2x = 888, w2y = 172, w2w = 40, w2h = 200;
float p1x = 80, p1y = 0, pw = 90, ph = 471;
float p2x = 160, p2y = 0, p2w = 200, p2h = 366;
float p3x = 360, p3y = 0, p3w = 75, p3h = 472.5;
float p4x = 480, p4y = 0, p4w = 28, p4h = 502.5;
float p5x = 558, p5y = 235, p5w = 370, p5h = 1000;
float p6x = 558, p6y = 0, p6w = 370, p6h = 107;
float p7x = 650, p7y = 150.5, p7w = 200, p7h = 20;

World_Collision ledge1, ledge2, ledge3, ledge4, ledge5, ledge6;
float l1x = 345, l1y = 410, l1w = 20, l1h = 17.5;
float l2x = 465, l2y = 460, l2w = 20, l2h = 12.5;
float l3x = 540, l3y = 468, l3w = 20, l3h = 10;
float l4x = 505, l4y = 391, l4w = 25, l4h = 10;
float l5x = 540, l5y = 283, l5w = 20, l5h = 10;
float l6x = 505, l6y = 113.5, l6w = 25, l6h = 10;

World_Collision ground;
float gx = 0.0f, gy = 0.0f, gw = 1280, gh = 50;

bool jump = false, left = false, right = false, spaceHeld = false, EMP = false;
bool spotted = false, dead = false;
vec2 gravity(0.0f, -186.0f), velocity(0.0f, 0.0f), enemyVelocity(0.0f, 0.0f);

int seconds = 0, deathSeconds = 0, shootSeconds = 0;


//keyboard function, set keys to do tasks
void KeyboardFunc(Window::Key a_key, Window::EventType a_eventType)
{
	switch (a_eventType)
	{
	case Window::EventType::KeyPressed:
	{
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
				//velocity.y = 250.0f; //give the player a jump velocity when space is pressed
				//later: add a bool to check if the player is on ground (only then can he jump) exclusion would be double jump
				//^to do this the world collision class will be needed so we can check if a player is on any object coords/width of the world class
				spaceHeld = true;
			}
		}
		if (a_key == Window::Key::Q && !player.returnEMP())
		{
			EMP = true;
			player.useEMP(guards);
		}
		else if (a_key != Window::Key::Q)
		{
			player.setEMP();
		}
		if (a_key == Window::Key::Return)
		{
			if (spotted == true)
			{
				spotted = false;
				y = 471;
				x = 120;
				deathSeconds = 0;
				shootSeconds = 0;
				//lives - 1;
				dead = true;
				mainCharacter.set_scale(40, 40);
			}
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
			EMP = false;
		}

		if (a_key == Window::Key::Space)
		{
			spaceHeld = false;
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

void Movement()
{
	//player movement info//////

	if (spotted == false)
	{
		if (left == true) //LEFT
		{
			//right side of platforms
			if (checkCollide(x, y, w, h, wall0.getX(), wall0.getY(), wall0.getWidth(), wall0.getHeight())) //first wall
			{
				velocity.x = 0;
			}
			else if (checkCollide(x, y, w, h, wall1.getX(), wall1.getY(), wall1.getWidth() + 5, wall1.getHeight())) //first wall
			{
				velocity.x = 0;
			}
			else if (checkCollide(x, y, w, h, wall2.getX(), wall2.getY(), wall2.getWidth() + 5, wall2.getHeight())) //second wall
			{
				velocity.x = 0;
			}
			else if (checkCollide(x, y, w, h, platform1.getX(), platform1.getY(), platform1.getWidth() + 10, platform1.getHeight() - 5)) //second wall
			{
				velocity.x = 0;
			}
			else if (checkCollide(x, y, w, h, platform3.getX(), platform3.getY(), platform3.getWidth() + 10, platform3.getHeight() - 5)) //third wall
			{
				velocity.x = 0;
			}
			else if (checkCollide(x, y, w, h, platform4.getX(), platform4.getY(), platform4.getWidth() + 3, platform4.getHeight() - 5)) //fourth wall
			{
				velocity.x = 0;
			}
			else if (checkCollide(x, y, w, h, platform7.getX(), platform7.getY(), platform7.getWidth() + 10, platform7.getHeight() - 5)) //seventh wall
			{
				velocity.x = 0;
			}
			else if (checkCollide(x, y, w, h, ledge4.getX(), ledge4.getY(), ledge4.getWidth() + 10, ledge4.getHeight() - 5)) //third wall
			{
				velocity.x = 0;
			}
			else
				velocity.x = -100.0f;
			mainCharacter.set_scale(-40, 40); //flip sprite
			mainCharacter.set_animation("anim_2");
		}
		else if (right == true) //RIGHT
		{
			//left side of platforms
			if (checkCollide(x, y, w + 5, h, platform3.getX(), platform3.getY(), platform3.getWidth(), platform3.getHeight() - 5)) //third wall
			{
				velocity.x = 0;
			}
			else if (checkCollide(x, y, w + 5, h, platform4.getX(), platform4.getY(), platform4.getWidth(), platform4.getHeight() - 5)) //fourth wall
			{
				velocity.x = 0;
			}
			else if (checkCollide(x, y, w + 5, h, platform5.getX(), platform5.getY(), platform5.getWidth(), platform5.getHeight() - 5)) //fifth wall
			{
				velocity.x = 0;
			}
			else if (checkCollide(x, y, w + 5, h, wall1.getX(), wall1.getY(), wall1.getWidth(), wall1.getHeight() - 5)) //fifth wall
			{
				velocity.x = 0;
			}
			else if (checkCollide(x, y, w + 5, h, wall2.getX(), wall2.getY(), wall2.getWidth(), wall2.getHeight() - 5)) //fifth wall
			{
				velocity.x = 0;
			}
			else if (checkCollide(x, y, w + 5, h, platform6.getX(), platform6.getY(), platform6.getWidth(), platform6.getHeight() - 5)) //sixth wall
			{
				velocity.x = 0;
			}
			else if (checkCollide(x, y, w + 5, h, platform7.getX(), platform7.getY(), platform7.getWidth(), platform7.getHeight() - 5)) //seventh wall
			{
				velocity.x = 0;
			}
			else if (checkCollide(x, y, w + 5, h, ledge1.getX(), ledge1.getY(), ledge1.getWidth(), ledge1.getHeight() - 5)) //first ledge
			{
				velocity.x = 0;
			}
			else if (checkCollide(x, y, w + 5, h, ledge2.getX(), ledge2.getY(), ledge2.getWidth(), ledge2.getHeight() - 5)) //second ledge
			{
				velocity.x = 0;
			}
			else if (checkCollide(x, y, w + 5, h, ledge3.getX(), ledge3.getY(), ledge3.getWidth(), ledge3.getHeight() - 5)) //third ledge
			{
				velocity.x = 0;
			}
			else if (checkCollide(x, y, w + 5, h, ledge5.getX(), ledge5.getY(), ledge5.getWidth(), ledge5.getHeight() - 5)) //fifth ledge
			{
				velocity.x = 0;
			}
			else
				velocity.x = 100.0f;
			mainCharacter.set_scale(40, 40); //flip sprite
			mainCharacter.set_animation("anim_2");
		}

		else //not moving
		{
			velocity.x = 0;
			mainCharacter.set_animation("anim_3");
		}


		if (spaceHeld == true)
		{
			if (seconds < 15)
			{
				velocity.y = 250.0f;
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

void SetupCollisionProperties()
{
	//ground properties
	ground.setCoord(gx, gy);
	ground.setHeight(gh);
	ground.setWidth(gw);

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
}

void bottomTopCollision()
{
	///////////////////////

	//COLLISION DETECTION IS PUT AFTER HERE///////

	//to do: need to solve floating point precision errors so objects don't sink into one another

	//1st platform collision//////
	//SIDE OF PLATFORM COLLISION CHECK IN MOVEMENT FOR PLAYER
	//top of platforms
	if (checkCollide(x, y, w, h, platform1.getX(), platform1.getY(), platform1.getWidth(), platform1.getHeight()))
	{
		jump = false;
		velocity.y = 0;
		gravity.y = 0;
		if (y < 471)
		{
			y = 471;
		}
	}
	else if (checkCollide(x, y, w, h, platform2.getX(), platform2.getY(), platform2.getWidth(), platform2.getHeight()))
	{
		jump = false;
		velocity.y = 0;
		gravity.y = 0;
		if (y < 366)
		{
			y = 366;
		}
	}
	else if (checkCollide(x, y, w, h, platform3.getX(), platform3.getY(), platform3.getWidth(), platform3.getHeight()))
	{
		jump = false;
		velocity.y = 0;
		gravity.y = 0;
		if (y < 472.5)
		{
			y = 472.5;
		}
	}
	else if (checkCollide(x, y, w, h, platform4.getX(), platform4.getY(), platform4.getWidth(), platform4.getHeight()))
	{
		jump = false;
		velocity.y = 0;
		gravity.y = 0;
		if (y < 502.5)
		{
			y = 502.5;
		}
	}
	else if (checkCollide(x, y, w, h, platform6.getX(), platform6.getY(), platform6.getWidth(), platform6.getHeight()))
	{
		jump = false;
		velocity.y = 0;
		gravity.y = 0;
		if (y < 107)
		{
			y = 107;
		}
	}
	else if (checkCollide(x, y, w, h, ledge1.getX(), ledge1.getY() + 5, ledge1.getWidth(), ledge1.getHeight() - 5))
	{
		jump = false;
		velocity.y = 0;
		gravity.y = 0;
		if (y < 427.5)
		{
			y = 427.5;
		}
	}
	else if (checkCollide(x, y, w, h, ledge2.getX(), ledge2.getY(), ledge2.getWidth(), ledge2.getHeight()))
	{
		jump = false;
		velocity.y = 0;
		gravity.y = 0;
		if (y < 472.5)
		{
			y = 472.5;
		}
	}
	else if (checkCollide(x, y, w, h, ledge3.getX(), ledge3.getY() + 5, ledge3.getWidth(), ledge3.getHeight()))
	{
		jump = false;
		velocity.y = 0;
		gravity.y = 0;
		if (y < 478)
		{
			y = 478;
		}
	}
	else if (checkCollide(x, y, w, h, ledge4.getX(), ledge4.getY(), ledge4.getWidth(), ledge4.getHeight()))
	{
		jump = false;
		velocity.y = 0;
		gravity.y = 0;
		if (y < 401)
		{
			y = 401;
		}
	}
	else if (checkCollide(x, y, w, h, ledge5.getX(), ledge5.getY(), ledge5.getWidth(), ledge5.getHeight()))
	{
		jump = false;
		velocity.y = 0;
		gravity.y = 0;
		if (y < 293)
		{
			y = 293;
		}
	}
	else if (checkCollide(x, y, w, h, ledge6.getX(), ledge6.getY(), ledge6.getWidth(), ledge6.getHeight()))
	{
		jump = false;
		velocity.y = 0;
		gravity.y = 0;
		if (y < 123.5)
		{
			y = 123.5;
		}
	}
	else if (checkCollide(x, y, w, h, platform7.getX(), platform7.getY() + 5, platform7.getWidth(), platform7.getHeight() - 5))
	{
		jump = false;
		velocity.y = 0;
		gravity.y = 0;
		if (y < 170.5)
		{
			y = 170.5;
		}
	}
	else
	{
		jump = true;
		gravity.y = -1000.0f;
	}

	//bottom of platforms
	if (checkCollide(x, y, w, h, ledge1.getX(), ledge1.getY() - 3, ledge1.getWidth(), ledge1.getHeight() - 5))
	{
		spaceHeld = false;
		y -= 0.3;
		velocity.y = 0;
	}
	if (checkCollide(x, y, w, h, ledge3.getX(), ledge3.getY() - 3, ledge3.getWidth(), ledge3.getHeight() - 5))
	{
		spaceHeld = false;
		y -= 0.3;
		velocity.y = 0;
	}
	if (checkCollide(x, y, w, h, wall1.getX(), wall1.getY(), wall1.getWidth(), wall1.getHeight() - 195)) //first wall
	{
		spaceHeld = false;
		y -= 0.3;
		velocity.y = 0;
	}
	if (checkCollide(x, y, w, h, wall2.getX(), wall2.getY(), wall2.getWidth(), wall2.getHeight() - 195)) //first wall
	{
		spaceHeld = false;
		y -= 0.3;
		velocity.y = 0;
	}
	if (checkCollide(x, y, w, h, platform5.getX(), platform5.getY() - 3, platform5.getWidth(), platform5.getHeight() - 5))
	{
		spaceHeld = false;
		y -= 0.3;
		velocity.y = 0;
	}
	if (checkCollide(x, y, w, h, platform7.getX(), platform7.getY() - 3, platform7.getWidth(), platform7.getHeight() - 5))
	{
		spaceHeld = false;
		y -= 0.3;
		velocity.y = 0;
	}
	//////////////////////////////

	/*
	//ground collision//////
	if (checkCollide(x, y, 0, 70, ground.getX(), ground.getY(), ground.getWidth(), ground.getHeight()))
	{
	jump = false;
	velocity.y = 0; //the vertical velocity of the player is 0 if the player is on the "ground"
	//essentially, the vertical velocity comes to an end
	if(y < 50) //STOP PLAYER FROM SINKING IN GROUND
	{
	y = 50; //position correctiveness
	}
	}
	else
	{*/
	//jump = true; //THIS WAS MAKING IT SO YOU COULDN'T JUMP ON PLATFORM, SO AVOID THIS
	velocity.y += gravity.y * (1.0f / 30.0f); //this equation effects the y coord of the player
											  //the velocity of the jump is effected by the gravity and updated per frame
											  //gives the jump a much smoother effect
											  //like a PARABOLA :D

											  ////////////////////////

	if (y < -250)
	{
		y = 472;
		x = 120;
		//lives =  lives - 1;
		dead = true;
		mainCharacter.set_scale(40, 40);
	}

}

void drawUpdate()
{
	backGround.draw();
	level.draw();
	//update sprite(s) position per frame//////
	mainCharacter.set_position(player.getX(), player.getY());
	guard1.set_position(enemy1.getX(), enemy1.getY());
	useEMP.set_position(player.getX(), player.getY());
	if (enemyVelocity.x < 0)
	{
		AdditiveSprite.set_position(enemy1.getX() - 4, enemy1.getY() - 5);
	}
	else
	{
		AdditiveSprite.set_position(enemy1.getX() + 4, enemy1.getY() - 5);
	}
	///////////////////////////////////////////
	//draw sprite(s) per frame//////
	if (EMP == false)
	{
		mainCharacter.draw();
		mainCharacter.next_frame(); //update animation frames
		useEMP.set_frame(0);
	}
	if (EMP == true)
	{
		useEMP.draw();
		useEMP.next_frame();
	}
	//SHADER, USED FOR LIGHTING////////////
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	spotlight.set_position(spotLight1.getX() + 10, spotLight1.getY());
	if (enemy1.flashlight && spotLight1.flashlight)
	{
		spotlight.draw();
		if (spotted == false)
			AdditiveSprite.draw();
	}
	/*glBlendFunc(GL_DST_COLOR, GL_ZERO);
	MultSprite.draw();*/
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//MultSprite.set_position(sinf(Window::get_game_window().get_delta_time() * 0.1f) * 100.0f + 400.0f, 200.0f);
	///////////////////////////////////////
	guard1.draw();
	guard1.next_frame(); //update animation frames
						 ///////////////////////////////

}

void loadSprites()
{
	//background textures
	backGround.load_sprite_image("assets/images/backGround.png")
		.set_position(0, 0);

	level.load_sprite_image("assets/images/level design 1.png")
		.set_position(0, 0)
		.set_scale(1280, 900);

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


	//create player sprite
	mainCharacter.load_sprite_image("assets/images/RighteousThiefAnim.png")
		.set_sprite_frame_size(96, 96, false)
		.set_scale(40, 40)
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
		.set_scale(40, 40)
		.set_position(player.getX(), player.getY())
		.set_center(0.5, 0.0);
	for (int r = 6; r > 0; r--)
	{
		unsigned int row = 64 * r;
		useEMP.push_frame_row("throw", 0, row, 64, 0, 5);
	}
	useEMP.set_animation("throw");

	//create guard sprite
	guard1.load_sprite_image("assets/images/UNITYEnemyAnim.png")
		.set_sprite_frame_size(96, 96, false)
		.set_scale(40, 40)
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

	AdditiveSprite.load_sprite_image("assets/images/Flashlight.png")
		.set_scale(200, 80)
		.set_center(1.0f, 0.0f)
		.set_position(enemy1.getX() + 5, enemy1.getY() - 5);

	spotlight.load_sprite_image("assets/images/Flashlight.png")
		.set_scale(70, 60)
		.set_center(1.0f, 0.0f)
		.set_rotation(90)
		.set_position(spotLight1.getX(), spotLight1.getY());

	/*MultSprite.load_sprite_image("assets/images/Flashlight.png")
	.set_scale(128, 128)
	.set_center(0.5f, 0.5f)
	.set_position(600.0f, 216.0f);*/


}

void enemyInfo()
{
	//1st enemy pathing info//////

	if (enemy1.getX() >= 825)
	{
		enemyVelocity.x = -50.0f; //LEFT
		guard1.set_scale(-40, 40); //flip sprite
		AdditiveSprite.set_scale(100, 40); //flip flashlight
		enemy1.setDirection(1, 0);
		guard1.set_animation("guardWalk");
	}
	if (enemy1.getX() <= 675)
	{
		enemyVelocity.x = 50.0f; //RIGHT
		guard1.set_scale(40, 40); //flip sprite
		AdditiveSprite.set_scale(-100, 40); //flip flashlight
		enemy1.setDirection(-1, 0);
		guard1.set_animation("guardWalk");
	}

	if (spotted == false)
	{
		ex += enemyVelocity.x * (1.0f / 60.0f); //the enemy's horizontal velocity updated per frame
		ey += enemyVelocity.y * (1.0f / 60.0f); //same as above but this time for vertical velocity
	}

	///////////////////////
}

void UIElements()
{
	Text::set_color(1.0f, 1.0f, 1.0f);
	eye.draw();
	health.draw();

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
	EMPicon.draw();
	if (enemy1.FOV(player.getCoord()))
	{
		//text::draw_string("!", "TimesNewRoman", 1200, 640, 3.0f);
		//Text::draw_string("Visible", "FFF", 1150, 690, 0.75f);
		eye.set_frame(0);
		spotted = true;
	}
	else if (spotLight1.FOV(player.getCoord()))
	{
		eye.set_frame(0);
	}
	else
	{
		//Text::draw_string("Hidden", "FFF", 1150, 690, 0.75f);
		eye.set_frame(1);
	}
	///////////////////////////////////////

}


//main function aka the boss
int main()
{
	Window& game = Window::get_game_window();
	game.init("Corrupt", 1280, 720)
		//.set_screen_size(128, 72)
		.set_clear_color(0, 255, 255);
	Text::load_font("assets/FFFFORWA.TTF", "FFF");

	//sf::Music lul;

	//lul.openFromFile("assets/sound/mgs_encounter.wav");

	//load sprites/textures/////
	loadSprites();
	////////////////////////////
	
	//initialize collision object properties////////
	SetupCollisionProperties();
	////////////////////////////////////////////////

	guards.push_back(&enemy1);
	guards.push_back(&spotLight1);

	
	//GAME LOOP, 60 FRAMES
	//EVERYTHING UPDATES IN HERE
	while (game.update(60))
	{
		if (dead == true)
		{
			lives -= 1;
			dead = false;
		}
		//CAMERA SETTINGS/////////
		float width = 1280.0f * 0.5f;
		float height = 720.0f * 0.5f;
		float cx = x - 200.0f, cy = y - 20.0f;
		/////////////////////////

		//CLAMP THE MAX AND MIN OF CAMERA COORDS////////
		cx = std::max(0.0f, std::min(x - 200.0f, 1280.0f - width));
		cy = std::max(0.0f, std::min(y - 100.0f, 720.0f - height));
		////////////////////////////////////////////////

		//NOW SET THE CAMERA/////////////////////
		game.set_ortho_window(cx, cy, (width - 100), (height - 100));
		////////////////////////////////////////

		//get keyboard function per frame
		game.set_keyboard_callback(KeyboardFunc);
		//guards.push_back(enemy1); //<- move this out of while loop later
		//draw and update sprites//////
		drawUpdate();
		///////////////////////////////

		//player movement info//////
		Movement();
		////////////////////////////

		//collision info///////
		bottomTopCollision();
		///////////////////////

		//enemy pathing info//////
		enemyInfo();
		///////////////////////

		
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

		if (spotted == true)
		{
			guard1.set_animation("guardShoot"); //animation doesn't reset, need to fix this
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
			
			if (shootSeconds > 35)
			{
				guard1.set_frame(20);
			}
				
		}
		
		
		//debugging info
		//not needed in final version but useful for now
		system("cls");
		std::cout << "Y: " << y << std::endl;
		std::cout << "X: " << x << std::endl;
		std::cout << "Gravity: " << gravity.y << std::endl;
		std::cout << "Velocity: " << velocity.x << std::endl;
		std::cout << "EMP: " << player.getEMP() << std::endl;

		//now this is important
		//we actually have to update the player position per frame or nothing will happen unless we are hitting a key
		//so simply just set the coord of the player using the x and y variables
		player.setCoord(x, y);
		//back up at the drawing of the player, the getX() and getY() will return the updated numbers, so the rectangle will retain these coords
		//As I like to say, easy peasy lemon squeezy
		
		//update first enemy position per frame
		enemy1.setCoord(ex, ey);
		spotLight1.setCoord(sx, sy);
		spotLight1.setDirection(0.25, 1);

		//UI ELEMENTS//////////////////////////
		game.set_ortho_window(0.0f, 0.0f, 1280.0f, 720.0f); //reset ortho matrix for UI elements

		UIElements();
		///////////////////////////////////////

	}
}