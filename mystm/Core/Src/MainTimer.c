/*
 * MainTimer.c
 *
 *  Created on: 31 Jul 2022
 *      Author: student
 */
#include "MainTimer.h"
#include <string.h>
#include <stdio.h>

static MainTimerIT MainTimer[20];
static int lastObject = 0;

void MainTimer_Init(){
	memset(MainTimer, 0 , sizeof(MainTimer));
}

void MainTimer_registerCallback(TimerHandler timerHendler, void* object)
{
	int i=0;
	while (MainTimer[i].timerHendler != 0){
		if(MainTimer[i].timerHendler == timerHendler && MainTimer[i].object == object ){
			return;
		}
		i++;
	}

	MainTimer[lastObject].timerHendler = timerHendler;
	MainTimer[lastObject].object = object;
	lastObject ++;


}

void MainTimer_unRegisterCallback(TimerHandler timerHendler, void* object)
{
	int i=0;
	while (MainTimer[i].timerHendler != 0){
		if(MainTimer[i].timerHendler == timerHendler && MainTimer[i].object == object ){
			MainTimer[i].timerHendler = MainTimer[lastObject-1].timerHendler;
			MainTimer[i].object = MainTimer[lastObject-1].object;
			MainTimer[lastObject-1].timerHendler = 0;
			MainTimer[lastObject-1].object = 0;
			lastObject--;
			break;
		}
		i++;
	}
    printf("lastObject= %d  \r\n", lastObject);
}

void MainTimer_onTimerInterrupt()
{
	int i=0;
	while (MainTimer[i].timerHendler != 0){
		MainTimer[i].timerHendler (MainTimer[i].object);
		i++;
	}
}









