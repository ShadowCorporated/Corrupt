#include <iostream>
#include <vector>
#include "Characters.h"

using namespace std;

int main()
{
	Guard guardOne;
	guardOne.setCoord(12.0f, 17.0f);

	KeyHolder keyDude;
	keyDude.setCoord(13.0f, 17.0f);

	vector<KeyHolder> guards;
	guards.push_back(guardOne);
	guards.push_back(keyDude);


	Player player;
	player.setCoord(12.0f, 12.0f);


	vec2 range(player.getX() - guards[1].getX(), player.getY() - guards[1].getY());
	float magnitude = range.getMagnitude(range);
	for (int i = 0; i < guards.size(); i++)
	{
		guards[i].setDirection(-1, -1);

		if (guards[i].fieldOfView(player.getCoord()))
		{
			cout << "You have been caught" << endl;
		}
		else
		{
			cout << "You are undetected" << endl;
		}
	}
}