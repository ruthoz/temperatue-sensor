/*
 * Led.cpp
 *
 *  Created on: Nov 16, 2022
 *      Author: student
 */

#include "Led.h"
#include <stdio.h>

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
	_state = STATE_BLINKING,
	HAL_GPIO_TogglePin(_GPIOx, _GPIO_Pin);
}
