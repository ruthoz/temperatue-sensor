#include "button.h"
#include "main.h"
#include <stdio.h>


uint32_t counter = 0;
int flagPrees = 0;

void buttonInit(BUTTON* button , GPIO_TypeDef* GPIOx , uint16_t GPIO_Pin)
{
	button->state = BUTTON_STATE_NONE;
	button->timeTickOn = 0 ;
	button->timeTickOff = 0 ;
	button->GPIOx = GPIOx;
	button->GPIO_Pin = GPIO_Pin;
}


void buttonInterrupt(BUTTON* button)
{
	uint32_t DelayTick = 0;

	if(HAL_GPIO_ReadPin(button->GPIOx, button->GPIO_Pin) == 0){
		button->timeTickOn = HAL_GetTick();
	}

	else if(HAL_GPIO_ReadPin(button->GPIOx, button->GPIO_Pin) == 1){
			button->timeTickOff = HAL_GetTick();
			DelayTick = button->timeTickOff - button->timeTickOn;

	     if(DelayTick > 500){
	       button->state = BUTTON_LONG_PRESS;
	       printf("Long \n\r");
	     }
	     else if (button->state == BUTTON_STATE) {
		   button->state = BUTTON_DOUBLE_PRESS;
		   counter = 0;
		   printf("Double \n\r");
	     }
	     else{
		   button->state = BUTTON_STATE;
	     }
	}
}

void buttonOnTimerInterrupt (BUTTON* button)
{
	if (button->state == BUTTON_STATE) {
		counter++;
		if(counter > 200 ){
			button->state = BUTTON_STATE_PRESS;
			counter = 0;
			printf("One \n\r");
		}
	}
}

StateButon Button_checkState(BUTTON* button)
{
	return button->state;
}