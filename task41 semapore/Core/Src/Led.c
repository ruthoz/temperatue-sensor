/*
 * Led.c
 *
 *  Created on: Sep 13, 2022
 *      Author: student
 */

#include "Led.h"
#include "cmsis_os.h"
#include <stdio.h>
#include <stdlib.h>


//static int delay = 500;


void Led_init(Led* led , GPIO_TypeDef* GPIOx , uint16_t GPIO_Pin)
{
	led->state = STATE_OFF;
	led->counter = 0 ;
	led->GPIOx = GPIOx;
	led->GPIO_Pin = GPIO_Pin;
	led->delay = 500;
}


void Entry_blinkTask(void *obj)
{
  /* USER CODE BEGIN Entry_blinkTask */
	Led *led = (Led*)obj;
  /* Infinite loop */
  for(;;)
  {
	  HAL_GPIO_TogglePin(led->GPIOx, led->GPIO_Pin);
	  osDelay(led->delay);
  }
  /* USER CODE END Entry_blinkTask */
}


void setBlinkLed(void* obj, char* param)
{
	Led *led = (Led*)obj;
	led->delay= atoi (param);
}
