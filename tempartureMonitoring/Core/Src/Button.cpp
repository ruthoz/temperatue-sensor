/*
 * Button.cpp
 *
 *  Created on: 17 Nov 2022
 *      Author: student
 */

#include "Button.h"
#include "cmsis_os.h"

extern Button button;
extern Buzzer buzzer;
extern osSemaphoreId_t stopBuzzerHandle;

Button::Button(GPIO_TypeDef* GPIOx , uint16_t GPIO_Pin)
{
	_GPIOx = GPIOx;
	_GPIO_Pin = GPIO_Pin;
	_state = BUTTON_STATE_NONE;
}

void Button::interrupt()
{
	if(HAL_GPIO_ReadPin(_GPIOx, _GPIO_Pin) == 0){
		_timeTickOn = HAL_GetTick();
	}

	else if(HAL_GPIO_ReadPin(_GPIOx, _GPIO_Pin) == 1){
		_timeTickOff = HAL_GetTick();

		if((_timeTickOff - _timeTickOn) > 500){
			_state = BUTTON_LONG_PRESS;
		}
		else{
			_state = BUTTON_STATE_PRESS;
		}
		osSemaphoreRelease(stopBuzzerHandle);
	}
}

extern "C" void StartbuttonTak()
{
  /* USER CODE BEGIN StartbuttonTak */
  /* Infinite loop */
  while(1)
  {
	osSemaphoreAcquire(stopBuzzerHandle,osWaitForever);
	buzzer.off();
    osDelay(1);
  }
  /* USER CODE END StartbuttonTak */
}


