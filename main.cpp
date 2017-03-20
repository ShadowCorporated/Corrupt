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
std::vector<HidingSpot*> spots;

Sprite mainCharacter, guard1, backGround, eye, health, EMPicon;

Sprite AdditiveSprite, MultSprite;

std::vector<Sprite*> spritesAddToDraw;
std::vector<Sprite*> spritesMultToDraw;

Player player;
float x = 300.0f, y = 50.0f;

Guard enemy1;
float ex = 1100, ey = 50;

World_Collision platform1;
float p1x = 400, p1y = 150, pw = 200, ph = 20;

World_Collision ground;
float gx = 0.0f, gy = 0.0f, gw = 1280, gh = 50;

bool jump = false, left = false, right = false, spaceHeld = false;
vec2 gravity(0.0f, -186.0f), velocity(0.0f, 0.0f), enemyVelocity(0.0f, 0.0f);

int seconds = 0;

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
			player.useEMP(guards);
		}
		else if (a_key != Window::Key::Q)
		{
			player.setEMP();
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

	//background textures
	backGround.load_sprite_image("assets/images/CorruptBackground.png")
		.set_position(0, 0);

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
		.push_frame_row("health", 0, 0, 256, 256, 4)
		.set_animation("health");

	EMPicon.load_sprite_image("assets/images/EMP.png")
		.set_position(-10, 550)
		.set_scale(100, 100);


	//create player sprite
	mainCharacter.load_sprite_image("assets/images/RighteousThiefAnim.png")
		.set_sprite_frame_size(128, 128, false)
		.set_scale(80, 80)
		.set_position(player.getX(), player.getY())
		.set_center(0.5, 0.0); //SET X TO MIDDLE TO ALLOW SPRITE TO FLIP
	//grab the rows of the spritesheet
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
	//grab the rows of the spritesheet
	for (int r = 0; r < 8; r++)
	{
		unsigned int row = 128 * r;
		guard1.push_frame_row("guardWalk", 0, row, 128, 0, 7);
	}
	guard1.set_animation("guardWalk");

	AdditiveSprite.load_sprite_image("assets/images/Flashlight.png")
		.set_scale(200, 80)
		.set_center(1.0f, 0.0f)
		.set_position(enemy1.getX() + 5, enemy1.getY() - 5);

	/*MultSprite.load_sprite_image("assets/images/Flashlight.png")
		.set_scale(128, 128)
		.set_center(0.5f, 0.5f)
		.set_position(600.0f, 216.0f);*/
	//ground properties
	ground.setCoord(gx, gy);
	ground.setHeight(gh);
	ground.setWidth(gw);

	//create platform properties//////
	platform1.setCoord(p1x, p1y);
	platform1.setHeight(ph);
	platform1.setWidth(pw);
	//////////////////////////////////

	guards.push_back(&enemy1);

	//GAME LOOP, 60 FRAMES
	//EVERYTHING UPDATES IN HERE
	while (game.update(60))
	{
		//CAMERA SETTINGS/////////
		float width = 1280.0f * 0.5f;
		float height = 720.0f * 0.5f;
		float cx = x - 200.0f, cy = y - 20.0f;
		/////////////////////////

		//CLAMP THE MAX AND MIN OF CAMERA COORDS////////
		cx = std::max(0.0f, std::min(x - 200.0f, 1280.0f - width));
		cy = std::max(0.0f, std::min(y - 200.0f, 720.0f - height));
		////////////////////////////////////////////////

		//NOW SET THE CAMERA/////////////////////
		game.set_ortho_window(cx, cy, width, height);
		////////////////////////////////////////

		//get keyboard function per frame
		game.set_keyboard_callback(KeyboardFunc);
		//guards.push_back(enemy1); //<- move this out of while loop later
		//draw a test "ground"
		Shapes::set_color(1.0f, 0.0f, 1.0f);
		Shapes::draw_rectangle(true, ground.getX(), ground.getY(), ground.getWidth(), ground.getHeight());

		//draw the first platform
		Shapes::draw_rectangle(true, platform1.getX(), platform1.getY(), platform1.getWidth(), platform1.getHeight());
		
		backGround.draw();
		//update sprite(s) position per frame//////
		mainCharacter.set_position(player.getX(), player.getY());
		guard1.set_position(enemy1.getX(), enemy1.getY());
		for (int i = 0; i < guards.size(); i++)
		{
			if (guards[i]->flashlight == true)
			{
				if (enemyVelocity.x < 0)
				{
					AdditiveSprite.set_position(enemy1.getX() - 8, enemy1.getY() - 10);
				}
				else
				{
					AdditiveSprite.set_position(enemy1.getX() + 8, enemy1.getY() - 10);
				}
			}
		}
		///////////////////////////////////////////
		//draw sprite(s) per frame//////
		mainCharacter.draw();
		mainCharacter.next_frame(); //update animation frames
		//SHADER, USED FOR LIGHTING////////////
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);

		for (int i = 0; i < guards.size(); i++)
		{
			if (guards[i]->flashlight == true)
			{
				AdditiveSprite.draw();
			}
		}
		/*glBlendFunc(GL_DST_COLOR, GL_ZERO);
		MultSprite.draw();*/
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//MultSprite.set_position(sinf(Window::get_game_window().get_delta_time() * 0.1f) * 100.0f + 400.0f, 200.0f);
		///////////////////////////////////////
		guard1.draw();
		guard1.next_frame(); //update animation frames
		///////////////////////////////

		//player movement info//////
		if (left == true) //LEFT
		{
			//right side of platform
			if (checkCollide(x, y, 0, 70, platform1.getX() + 190, platform1.getY(), platform1.getWidth() - 180, platform1.getHeight() - 5))
			{
				velocity.x = 0;
			}
			else if (x < 5)
			{
				velocity.x = 0;
			}
			
			else
				velocity.x = -150.0f;
			mainCharacter.set_scale(-80, 80); //flip sprite
			mainCharacter.set_animation("anim_1");
		}
		else
			if (right == true) //RIGHT
			{
				//left side of platform
				if (checkCollide(x, y, 15, 70, platform1.getX(), platform1.getY() + 5, platform1.getWidth() - 180, platform1.getHeight() - 10))
				{
					velocity.x = 0;
				}
				else if (x > 1275)
				{
					velocity.x = 0;
				}
				else
					velocity.x = 150.0f;
				mainCharacter.set_scale(80, 80); //flip sprite
				mainCharacter.set_animation("anim_1");
			}

			else //not moving
			{
				velocity.x = 0;
				mainCharacter.set_animation("anim_2");
			}

		
		if (spaceHeld == true)
		{
			if (seconds < 30)
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
		/////////////////////////////

		//1st enemy pathing info//////
		if (enemy1.getX() >= 1100)
		{
			enemyVelocity.x = -100.0f; //LEFT
			guard1.set_scale(-80, 80); //flip sprite
			AdditiveSprite.set_scale(200, 80); //flip flashlight
			enemy1.setDirection(1, 0);
			//guard1.set_animation("guardWalk");
		}
		if (enemy1.getX() <= 900)
		{
			enemyVelocity.x = 100.0f; //RIGHT
			guard1.set_scale(80, 80); //flip sprite
			AdditiveSprite.set_scale(-200, 80); //flip flashlight
			enemy1.setDirection(-1, 0);
			//guard1.set_animation("guardWalk");
		}

		ex += enemyVelocity.x * (1.0f / 60.0f); //the enemy's horizontal velocity updated per frame
		ey += enemyVelocity.y * (1.0f / 60.0f); //same as above but this time for vertical velocity
		///////////////////////

		//COLLISION DETECTION IS PUT AFTER HERE///////

		//to do: need to solve floating point precision errors so objects don't sink into one another

		//1st platform collision//////
		//SIDE OF PLATFORM COLLISION CHECK IN MOVEMENT FOR PLAYER
		//top of platform
		if (checkCollide(x, y, 0, 70, platform1.getX(), platform1.getY() + 10, platform1.getWidth(), platform1.getHeight() - 10))
		{
			jump = false;
			velocity.y = 0;
			gravity.y = 0;
			if (y < 170)
			{
				y = 170;
			}
		}
		else
		{
			jump = true;
			gravity.y = -1000.0f;
		}
		
		//bottom of platform
		if (checkCollide(x, y, 0, 70, platform1.getX(), platform1.getY(), platform1.getWidth(), platform1.getHeight() - 5))
		{
			spaceHeld = false;
			y -= 0.3;
			velocity.y = 0;
		}
		//////////////////////////////

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
		std::cout << "EMP: " << player.getEMP() << std::endl;
		//now this is important
		//we actually have to update the player position per frame or nothing will happen unless we are hitting a key
		//so simply just set the coord of the player using the x and y variables
		player.setCoord(x, y);
		//back up at the drawing of the player, the getX() and getY() will return the updated numbers, so the rectangle will retain these coords
		//As I like to say, easy peasy lemon squeezy
		
		//update first enemy position per frame
		enemy1.setCoord(ex, ey);

		//UI ELEMENTS//////////////////////////
		game.set_ortho_window(0.0f, 0.0f, 1280.0f, 720.0f); //reset ortho matrix for UI elements

		Text::set_color(1.0f, 1.0f, 1.0f);
		eye.draw();
		health.draw();
		EMPicon.draw();
		if (enemy1.FOV(player.getCoord()))
		{
			//text::draw_string("!", "TimesNewRoman", 1200, 640, 3.0f);
			//Text::draw_string("Visible", "FFF", 1150, 690, 0.75f);
			eye.set_frame(0);
		}
		else
		{
			//Text::draw_string("Hidden", "FFF", 1150, 690, 0.75f);
			eye.set_frame(1);
		}
		///////////////////////////////////////

	}
}