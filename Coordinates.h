#pragma once

struct COORD2
{
	COORD2 operator=(const COORD2 &coord)
	{
		X = coord.X;
		Y = coord.Y;
		return *this;
	}
	float X;
	float Y;
};