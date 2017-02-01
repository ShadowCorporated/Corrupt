#include "spritelib/spritelib.h"

#include <fstream>
#include <streambuf>
#include <vector>
#include <iostream>
#include "Characters.h"

using namespace spritelib;
//using namespace std;

Player player;
float x = 300.0f;
float y = 300.0f;

float gx = 0.0f;
float gy = 0.0f;

bool jump = false;
vec2 gravity(0.0f, 0.0f);
vec2 velocity;

void KeyboardFunc(Window::Key a_key, Window::EventType a_eventType)
{
	vec2 left(-5.0f, 0.0f);
	vec2 right(5.0f, 0.0f);
	vec2 jump(0, 50);

	player.setCoord(x, y);
	switch (a_eventType)
	{
	case Window::EventType::KeyPressed:
	{
		velocity = vec2(0, 0);
		if (a_key == Window::Key::A)
		{
			//velocity.x = 5.0f;
		}

		if (a_key == Window::Key::D)
		{
			//velocity.x = 5.0f;
		}

		if (a_key == Window::Key::Space)
		{
			bool jump = true;
			velocity.y = 60.0f;
		}
			
	}
		break;
	case Window::EventType::KeyReleased:
	{

	}
		break;
	}

}

int main()
{
	Window& game = Window::get_game_window();
	game.init("Corrupt", 600, 400)
		.set_clear_color(0, 255, 255);

	while (game.update(60))
	{
		game.set_keyboard_callback(KeyboardFunc);

		Shapes::set_color(1.0f, 0.0f, 1.0f);
		Shapes::draw_rectangle(true, gx, gy, 600, 50);

		Shapes::set_color(0, 0, 0);
		Shapes::draw_rectangle(true, player.getX(), player.getY(), 20, 20);
	
		x += velocity.x * (1.0f / 60.0f);
		y += velocity.y * (1.0f / 60.0f);
		//if (y -1 >) {
		//	gravity.y = -98.0f;
		//	x += velocity.x * (1.0f / 60.0f);
		//	velocity.y += gravity.y * (1.0f / 60.0f);
		//	y += velocity.y * (1.0f / 60.0f);
		//}

		//46.3979

		system("cls");
		std::cout << "Y: " << y << std::endl;
		std::cout << "X: " << x << std::endl;
		std::cout << "Gravity: " << gravity.y << std::endl;
	
		player.setCoord(x, y);
		
	}
}