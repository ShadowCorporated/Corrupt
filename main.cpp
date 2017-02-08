#include "spritelib/spritelib.h"

#include <fstream>
#include <streambuf>
#include <vector>
#include <iostream>
#include "Characters.h"

using namespace spritelib;
//using namespace std;

//Sprite customShaderSprite;
//Shader vertexShader, fragmentShader;
//ShaderProgram shaderprogram;


Player player;
float x = 300.0f;
float y = 300.0f;

float gx = 0.0f;
float gy = 0.0f;

bool jump = false;
bool left = false;
bool right = false;
vec2 gravity(0.0f, -98.0f);
vec2 velocity(0.0f, 0.0f);


void KeyboardFunc(Window::Key a_key, Window::EventType a_eventType)
{
	
	//player.setCoord(x, y);
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
				velocity.y = 120.0f; //give the player a jump velocity when space is pressed
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
	}
		break;
	}

}

int main()
{
	Window& game = Window::get_game_window();
	game.init("Corrupt", 600, 400)
		.set_clear_color(0, 255, 255);

	Sprite mainCharacter;
	mainCharacter.load_sprite_image("assets/images/RighteousThief.png")
		.set_scale(128, 128)
		.set_position(player.getX(), player.getY());
		//.push_frame_row("Idle", 0, 0, )

	while (game.update(30))
	{
		game.set_keyboard_callback(KeyboardFunc);

		//draw a test "ground"
		Shapes::set_color(1.0f, 0.0f, 1.0f);
		Shapes::draw_rectangle(true, gx, gy, 600, 50);
		
		//draw a test "player:
		Shapes::set_color(0, 0, 0);
		Shapes::draw_rectangle(true, player.getX(), player.getY(), 20, 20); //use of player.getX() and getY() are from the player class and COORD
	
		mainCharacter.set_position(player.getX(), player.getY());
		if (left == true)
		{
			velocity.x = -50.0f;
		}
		else
			if (right == true)
			{
				velocity.x = 50.0f;
			}

			else
				velocity.x = 0;

		x += velocity.x * (1.0f / 30.0f); //the player's horizontal velocity updated per frame
		y += velocity.y * (1.0f / 30.0f); //same as above but this time for vertical velocity
		
		//later: world collision class neeeded so that the player stops falling
		//can then use world objects and player object to determine collision and if player stops

		//for now use y coord to determine where the player is affected by gravity
		if (y > 51)
		{
			jump = true;
			velocity.y += gravity.y * (1.0f / 30.0f); //this equation effects the y coord of the player
		//the velocity of the jump is effected by the gravity and updated per frame
		//gives the jump a much smoother effect
		//like a PARABOLA :D
		}
		else
		{
			jump = false;
			velocity.y = 0; //the vertical velocity of the player is 0 if the player is on the "ground"
			//essentially, the vertical velocity comes to an end
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
		
	}
}