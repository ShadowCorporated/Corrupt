#include "spritelib/spritelib.h"

#include <fstream>
#include <streambuf>
#include <vector>
#include <iostream>
#include "Characters.h"
#include "World Collision.h"

using namespace spritelib;

//Sprite customShaderSprite;
//Shader vertexShader, fragmentShader;
//ShaderProgram shaderprogram;

Sprite mainCharacter, guard1;

Player player;
float x = 300.0f, y = 50.0f;

Guard enemy1;
float ex = 1100, ey = 50;

World_Collision platform1;
float p1x = 400, p1y = 150, pw = 200, ph = 20;

World_Collision ground;
float gx = 0.0f, gy = 0.0f, gw = 1280, gh = 50;

bool jump = false, left = false, right = false;
vec2 gravity(0.0f, -186.0f), velocity(0.0f, 0.0f), enemyVelocity(0.0f, 0.0f);


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
				velocity.y = 250.0f; //give the player a jump velocity when space is pressed
				//later: add a bool to check if the player is on ground (only then can he jump) exclusion would be double jump
				//^to do this the world collision class will be needed so we can check if a player is on any object coords/width of the world class
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

		if (a_key == Window::Key::Space)
		{
			//nothing right now
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

//main function aka the boss
int main()
{
	Window& game = Window::get_game_window();
	game.init("Corrupt", 1280, 720)
		.set_clear_color(0, 255, 255);

	//create player sprite
	mainCharacter.load_sprite_image("assets/images/RighteousThiefAnim.png")
		.set_sprite_frame_size(128, 128, false)
		.set_scale(80, 80)
		.set_position(player.getX(), player.getY())
		.set_center(0.5, 0.0); //SET X TO MIDDLE TO ALLOW SPRITE TO FLIP
	for (int r = 0; r < 3; r++)
		{
			std::string pid = "anim_" + std::to_string(r);
			unsigned int row = 128 * r;
			mainCharacter.push_frame_row(pid , 0, row, 128, 0, 28);
		}
	mainCharacter.set_animation("anim_2");

	//create guard sprite
	guard1.load_sprite_image("assets/images/UNITYEnemyAnim.png")
		.set_sprite_frame_size(128, 128, false)
		.set_scale(80, 80)
		.set_position(enemy1.getX(), enemy1.getY())
		.set_center(0.5, 0.0); //SET X TO MIDDLE TO ALLOW SPRITE TO FLIP

	for (int r = 0; r < 4; r++)
	{
		unsigned int row = 128 * r;
		guard1.push_frame_row("guardWalk", 0, row, 128, 0, 7);
	}
	guard1.set_animation("guardWalk");

	//ground properties
	ground.setCoord(gx, gy);
	ground.setHeight(gh);
	ground.setWidth(gw);

	//create platform properties//////
	platform1.setCoord(p1x, p1y);
	platform1.setHeight(ph);
	platform1.setWidth(pw);
	//////////////////////////////////

	//GAME LOOP, 30 FRAMES
	//EVERYTHING UPDATES IN HERE
	while (game.update(30))
	{
		//get keyboard function per frame
		game.set_keyboard_callback(KeyboardFunc);

		//draw a test "ground"
		Shapes::set_color(1.0f, 0.0f, 1.0f);
		Shapes::draw_rectangle(true, ground.getX(), ground.getY(), ground.getWidth(), ground.getHeight());

		//draw the first platform
		Shapes::draw_rectangle(true, platform1.getX(), platform1.getY(), platform1.getWidth(), platform1.getHeight());
		
		//update sprite(s) position per frame//////
		mainCharacter.set_position(player.getX(), player.getY());
		guard1.set_position(enemy1.getX(), enemy1.getY());
		///////////////////////////////////////////
		//draw sprite(s) per frame//////
		mainCharacter.draw();
		mainCharacter.next_frame();
		guard1.draw();
		guard1.next_frame();
		///////////////////////////////

		//player movement info//////
		if (left == true) //LEFT
		{
			velocity.x = -100.0f;
			mainCharacter.set_scale(-80, 80); //flip sprite
			mainCharacter.set_animation("anim_1");
		}
		else
			if (right == true) //RIGHT
			{
				velocity.x = 100.0f;
				mainCharacter.set_scale(80, 80); //flip sprite
				mainCharacter.set_animation("anim_1");
			}

			else //not moving
			{
				velocity.x = 0;
				mainCharacter.set_animation("anim_2");
			}

		x += velocity.x * (1.0f / 30.0f); //the player's horizontal velocity updated per frame
		y += velocity.y * (1.0f / 30.0f); //same as above but this time for vertical velocity
		/////////////////////////////

		//1st enemy pathing info//////
		if (enemy1.getX() >= 1100)
		{
			enemyVelocity.x = -100.0f; //LEFT
			guard1.set_scale(-80, 80); //flip sprite
			//guard1.set_animation("guardWalk");
		}
		if (enemy1.getX() <= 900)
		{
			enemyVelocity.x = 100.0f; //RIGHT
			guard1.set_scale(80, 80); //flip sprite
			//guard1.set_animation("guardWalk");
		}

		ex += enemyVelocity.x * (1.0f / 30.0f); //the enemy's horizontal velocity updated per frame
		ey += enemyVelocity.y * (1.0f / 30.0f); //same as above but this time for vertical velocity
		///////////////////////

		//COLLISION DETECTION IS PUT AFTER HERE///////

		//to do: need to solve floating point precision errors so objects don't sink into one another

		//1st platform collision//////
		//top of platform
		if (checkCollide(x, y, 0, 70, platform1.getX(), platform1.getY() + 10, platform1.getWidth(), platform1.getHeight() - 10))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
		}
		else
		{
			jump = true;
			gravity.y = -186.0f;
		}
		//bottom of platform
		if (checkCollide(x, y, 0, 70, platform1.getX(), platform1.getY(), platform1.getWidth(), platform1.getHeight() - 5))
		{
			velocity.y = 0;
		}
		//////////////////////////////

		//ground collision//////
		if (checkCollide(x, y, 0, 70, ground.getX(), ground.getY(), ground.getWidth(), ground.getHeight()))
		{
			jump = false;
			velocity.y = 0; //the vertical velocity of the player is 0 if the player is on the "ground"
							//essentially, the vertical velocity comes to an end
		}
		else
		{
			//jump = true; //THIS WAS MAKING IT SO YOU COULDN'T JUMP ON PLATFORM, SO AVOID THIS
			velocity.y += gravity.y * (1.0f / 30.0f); //this equation effects the y coord of the player
													  //the velocity of the jump is effected by the gravity and updated per frame
													  //gives the jump a much smoother effect
													  //like a PARABOLA :D
		}
		////////////////////////

		if (jump == true)
		{
			mainCharacter.set_animation("anim_0");
		}
		
		
		//debugging info
		//not needed in final version but useful for now
		system("cls");
		std::cout << "Y: " << y << std::endl;
		std::cout << "X: " << x << std::endl;
		std::cout << "Gravity: " << gravity.y << std::endl;
		std::cout << "Velocity: " << velocity.x << std::endl;
	
		//now this is important
		//we actually have to update the player position per frame or nothing will happen unless we are hitting a key
		//so simply just set the coord of the player using the x and y variables
		player.setCoord(x, y);
		//back up at the drawing of the player, the getX() and getY() will return the updated numbers, so the rectangle will retain these coords
		//As I like to say, easy peasy lemon squeezy
		
		//update first enemy position per frame
		enemy1.setCoord(ex, ey);
	}
}