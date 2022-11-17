/*
 * Button.cpp
 *
 *  Created on: 17 Nov 2022
 *      Author: student
 */

#include "Button.h"
#include "main.h"
#include <stdio.h>
uint32_t counter = 0;

Button::Button(GPIO_TypeDef* GPIOx , uint16_t GPIO_Pin)
{
	_GPIOx = GPIOx;
	_GPIO_Pin = GPIO_Pin;
}

void Button::interrupt()
{
	uint32_t delayTick = 0;

	if(HAL_GPIO_ReadPin(_GPIOx, _GPIO_Pin) == 0){
		timeTickOn = HAL_GetTick();
	}

	else if(HAL_GPIO_ReadPin(_GPIOx, _GPIO_Pin) == 1){
		timeTickOff = HAL_GetTick();
		delayTick = timeTickOff - timeTickOn;

		if(delayTick > 500){
			state = BUTTON_LONG_PRESS;
		    printf("Long \n\r");
		}
		else if (state == BUTTON_STATE) {
			state = BUTTON_DOUBLE_PRESS;
			counter = 0;
			printf("Double \n\r");
		}
		else{
			state = BUTTON_STATE;
			   //MainTimer_registerCallback(Button_onTimerInterrupt , button);
		}
	}
}
void Button:: timerFunc()
{
	if (state == BUTTON_STATE) {
		counter++;
		if(counter > 200 ){
			state = BUTTON_STATE_PRESS;
			counter = 0;
			printf("One \n\r");
		}
	}
}

StateButton Button::checkState(){
	return state;
}
