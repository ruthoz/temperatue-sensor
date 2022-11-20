/*
 * Button.cpp
 *
 *  Created on: 17 Nov 2022
 *      Author: student
 */

#include "Button.h"
#include "main.h"

extern MainTimer mainTimer;


Button::Button(GPIO_TypeDef* GPIOx , uint16_t GPIO_Pin)
{
	_GPIOx = GPIOx;
	_GPIO_Pin = GPIO_Pin;
	_counter = 0;
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
			_counter = 0;
			printf("Double \n\r");
			mainTimer.deleteTimerTask(this);
		}
		else{
			state = BUTTON_STATE;
			mainTimer.addTimerTask(this);
		}
	}
}
void Button:: timerFunc()
{
	if (state == BUTTON_STATE) {
		_counter++;
		if(_counter > 200 ){
			state = BUTTON_STATE_PRESS;
			_counter = 0;
			printf("One \n\r");
			mainTimer.deleteTimerTask(this);
		}
	}
}

StateButton Button::checkState(){
	return state;
}
