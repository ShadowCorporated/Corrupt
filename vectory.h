#pragma once

class vec2
{
public:
	vec2(float vx, float vy);
	float getMagnitude() const;
	float getAngle(vec2 vector, vec2 direction);
	vec2();
	~vec2();
	float x;
	float y;
private:
	float magnitude;
};