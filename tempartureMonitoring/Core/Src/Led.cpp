/*
 * Led.cpp
 *
 *  Created on: Nov 16, 2022
 *      Author: student
 */

#include "Led.h"
#include <stdio.h>
#include "cmsis_os.h"

Led::Led(GPIO_TypeDef* GPIOx , uint16_t GPIO_Pin)
{
	_GPIOx = GPIOx;
	_GPIO_Pin = GPIO_Pin;
	_state = STATE_OFF;
}

void Led::on()
{
	_state = STATE_ON,
	HAL_GPIO_WritePin(_GPIOx, _GPIO_Pin, GPIO_PIN_SET);
}

void Led::off()
{
	_state = STATE_OFF,
	HAL_GPIO_WritePin(_GPIOx, _GPIO_Pin, GPIO_PIN_RESET);
}
void Led::blink()
{
	_state = STATE_BLINKING;
}

Led ledB(LD2_GPIO_Port , LD2_Pin );

extern "C" void startBlinkTask()
{
  /* USER CODE BEGIN startBlinkTask */
	//Led *_led = (Led*)argument ;
  /* Infinite loop */
  while(1)
  {
	if(ledB.getState() == STATE_BLINKING){
	HAL_GPIO_TogglePin(ledB.getGPIOx(), ledB.getGPIO_Pin());
	osDelay(600);
	}
	osDelay(1);
  }
  /* USER CODE END startBlinkTask */
}
