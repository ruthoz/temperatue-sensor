/*
 * Button.cpp
 *
 *  Created on: 17 Nov 2022
 *      Author: student
 */

#include "Button.h"
#include "cmsis_os.h"

Button button(B2_GPIO_Port ,  B2_Pin);

Button::Button(GPIO_TypeDef* GPIOx , uint16_t GPIO_Pin)
{
	_GPIOx = GPIOx;
	_GPIO_Pin = GPIO_Pin;
	_counter = 0;
	_state = BUTTON_STATE_NONE;
}

void Button::interrupt()
{
	uint32_t delayTick = 0;

	if(HAL_GPIO_ReadPin(_GPIOx, _GPIO_Pin) == 0){
		_timeTickOn = HAL_GetTick();
	}

	else if(HAL_GPIO_ReadPin(_GPIOx, _GPIO_Pin) == 1){
		_timeTickOff = HAL_GetTick();
		delayTick = _timeTickOff - _timeTickOn;

		if(delayTick > 500){
			_state = BUTTON_LONG_PRESS;
		       // printf("Long \n\r");
		}
		else if (_state == BUTTON_STATE_WAITH) {
			_state = BUTTON_DOUBLE_PRESS;
			_counter = 0;
			//printf("Double \n\r");
		}
		else{
			_state = BUTTON_STATE_WAITH;
		}
	}
}

StateButton Button::getState(){
	return _state;
}

uint32_t Button::getCounter(){
	return _counter;
}

void Button::setState(StateButton state){
	_state = state;
}

void Button::resetCounter(){
	_counter = 0;
}

void Button::plusCounter(){
	_counter++;
}

extern "C" void StartbuttonTak()
{
  /* USER CODE BEGIN StartbuttonTak */
  /* Infinite loop */
  while(1)
  {
	if (button.getState() == BUTTON_STATE_WAITH) {
		button.plusCounter();
	  	if(button.getCounter() > 200 ){
	  		button.setState(BUTTON_STATE_PRESS);
   	  	    button.resetCounter();
		    //printf("One \n\r");
	  	}
	}
    osDelay(1);
  }
  /* USER CODE END StartbuttonTak */
}


