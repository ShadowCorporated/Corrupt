#include <iostream>
#include <vector>
#include <Windows.h>
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

	SmallElectric satellite;
	satellite.setCOORD(12.0f, 13.0f);
	satellite.setEMP(1);

	BigElectric curcuit;
	curcuit.setCOORD(13.0f, 13.0f);
	curcuit.setEMP(2);


	Player player;
	player.setCoord(12.0f, 12.0f);


	vec2 range(player.getX() - guards[1].getX(), player.getY() - guards[1].getY());
	float magnitude = range.getMagnitude(range);
	while (true)
	{
		system("cls");
		for (unsigned int i = 0; i < guards.size(); i++)
		{
			vec2 range(player.getX() - guards[1].getX(), player.getY() - guards[1].getY());
			float magnitude = range.getMagnitude(range);

			guards[i].setDirection(0, 1);

			if (guards[i].fieldOfView(player.getCoord()))
			{
				cout << "You have been caught" << endl;
			}
			else
			{
				cout << "You are undetected" << endl;
			}
		}
		if (GetAsyncKeyState('Q'))
		{
			player.useEMP(guards);
		}
		else if (GetAsyncKeyState('E'))
		{
			player.addEMP(curcuit);
			player.addEMP(satellite);
		}
		else if (GetAsyncKeyState(VK_ESCAPE))
		{
			break;
		}

		if (player.returnEMP() == true)
		{
			player.setEMP((player.getEMP() - 1));
			player.setEMP(false);
		}

		cout << "EMP: " << player.getEMP() << endl;
	}

	return 0;
}