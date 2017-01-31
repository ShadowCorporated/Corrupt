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

float vec2::getMagnitude(vec2 vector)
{
	vector.x *= vector.x;
	vector.y *= vector.y;
	float calc = vector.x + vector.y;
	calc = sqrt(calc);
	return calc;
}

float vec2::getAngle(vec2 vector, vec2 direction)
{
	float dotproduct = (vector.x * direction.x) + (vector.y * direction.y);
	float mag1 = vector.getMagnitude(vector);
	float mag2 = direction.getMagnitude(direction);
	float angle = acos(dotproduct / (mag1 * mag2));
	return angle;
}

vec2::~vec2()
{

}