#include "Led.h"
#include "main.h"
#include <stdio.h>

Led::Led(GPIO_TypeDef* GPIOx , uint16_t GPIO_Pin)
{
	_GPIOx = GPIOx;
	_GPIO_Pin = GPIO_Pin;
}

void Led::on()
{
	HAL_GPIO_WritePin(_GPIOx, _GPIO_Pin, GPIO_PIN_SET);
}

void Led::off()
{
	HAL_GPIO_WritePin(_GPIOx, _GPIO_Pin, GPIO_PIN_RESET);
}

void Led::blink()
{
	HAL_GPIO_TogglePin(_GPIOx, _GPIO_Pin);
	HAL_Delay(1000);
}


