
#include <Clock.h>
#include "MainTimer.h"

void Clock_init(Clock* clock)
{
	clock->tick = 0;
	clock->seconds = 0;
	clock->minutes =0;
	clock->hours = 0;
	clock->days = 0;
	MainTimer_registerCallback(Clock_onTimerInterrupt , clock);
}

void Clock_onTimerInterrupt(Clock* clock)
{
	clock->tick++;
	clock->seconds = clock->tick/1000;
	clock->minutes = clock->tick/60000;
	clock->hours = clock->tick/360000;
	clock->days = clock->tick/8640000;
}

