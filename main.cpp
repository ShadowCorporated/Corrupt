#include <iostream>
#include <vector>
#include "Characters.h"

using namespace std;

int main()
{
	Guard guardOne;
	guardOne.setCoord(12, 17);
	KeyHolder keyDude;
	keyDude.setCoord(13, 17);
	vector<KeyHolder> guards;
	guards.push_back(guardOne);
	guards.push_back(keyDude);
	Player player;
	player.setCoord(12, 12);
	vec2 range(player.getX() - guards[1].getX(), player.getY() - guards[1].getY());
	float magnitude = range.getMagnitude(range);
	for (int i = 0; i < guards.size(); i++)
	{
		guards[i].setDirection(-1, -1);

		guards[i].fieldOfView(player.getCoord());
	}
}