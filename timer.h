#pragma once
#include <time.h>

class SecondsTimer {
public:

	//default constructor
	SecondsTimer();
	//begin counting seconds
	void countDown();
	//get the seconds passed
	unsigned long secondsPassed();
	//reset the timer
	void resetSeconds();
	//default deconstructor
	~SecondsTimer();
private:
	unsigned long start;
};
