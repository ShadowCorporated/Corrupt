#include "vectory.h"
#include <cmath>

vec2::vec2(float vx, float vy)
{
	x = vx;
	y = vy;
}

vec2::vec2()
{

}

float vec2::getMagnitude() const
{
	float X = x * x;
	float Y = y * y;
	float calc = X + Y;
	calc = sqrt(calc);
	return calc;
}

float vec2::getAngle(vec2 vector, vec2 direction)
{
	float dotproduct = (vector.x * direction.x) + (vector.y * direction.y);
	float mag1 = vector.getMagnitude();
	float mag2 = direction.getMagnitude();
	float angle = acos(dotproduct / (mag1 * mag2));
	return angle;
}

vec2::~vec2()
{

}