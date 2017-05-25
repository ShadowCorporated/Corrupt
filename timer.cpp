#include "timer.h"

SecondsTimer::SecondsTimer()
{
	//default
}
//setup the countdown
void SecondsTimer::countDown() 
{
	start = clock();
}
//return the total seconds passed
unsigned long SecondsTimer::secondsPassed() 
{
	return ((unsigned long)clock() - start) / CLOCKS_PER_SEC;
}

void SecondsTimer::resetSeconds()
{
	start = 0;
	countDown();
}

SecondsTimer::~SecondsTimer()
{
	//default
}