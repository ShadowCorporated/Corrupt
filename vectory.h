#pragma once

class vec2
{
public:
	vec2(int vx, int vy);
	float getMagnitude(vec2 vector);
	float getAngle(vec2 vector, vec2 direction);
	vec2();
	~vec2();
	int x;
	int y;
private:
	float magnitude;
};