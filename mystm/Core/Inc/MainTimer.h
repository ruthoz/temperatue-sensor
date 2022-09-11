/*
 * MainTimer.h
 *
 *  Created on: 31 Jul 2022
 *      Author: student
 */

#ifndef INC_MAINTIMER_H_
#define INC_MAINTIMER_H_

#include "main.h"
#include <stdint.h>

typedef void(*TimerHandler)(void*);

typedef struct MainTimerIT_
{
	TimerHandler timerHendler;
	void* object;
}MainTimerIT;

void MainTimer_registerCallback();
void MainTimer_Init();
void MainTimer_unRegisterCallback(TimerHandler timerHendler, void* object);
void MainTimer_onTimerInterrupt();

#endif /* INC_MAINTIMER_H_ */
