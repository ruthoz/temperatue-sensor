#include <Button.h>
#include "main.h"
#include <stdio.h>


uint32_t counter = 0;

/////////////////////////////////////////////////////////////////////////

void Button_init(Button* button , GPIO_TypeDef* GPIOx , uint16_t GPIO_Pin)
{
	button->state = BUTTON_STATE_NONE;
	button->timeTickOn = 0 ;
	button->timeTickOff = 0 ;
	button->GPIOx = GPIOx;
	button->GPIO_Pin = GPIO_Pin;
}


void Button_interrupt(Button* button)
{
	uint32_t delayTick = 0;

	if(HAL_GPIO_ReadPin(button->GPIOx, button->GPIO_Pin) == 0){
		button->timeTickOn = HAL_GetTick();
	}

	else if(HAL_GPIO_ReadPin(button->GPIOx, button->GPIO_Pin) == 1){
			button->timeTickOff = HAL_GetTick();
			delayTick = button->timeTickOff - button->timeTickOn;

	     if(delayTick > 500){
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
		   //MainTimer_registerCallback(Button_onTimerInterrupt , button);
	     }
	}
}

void Button_onTimerInterrupt(void* obj)
{
	Button* button = (Button *)obj;
	if (button->state == BUTTON_STATE) {
		counter++;
		if(counter > 200 ){
			button->state = BUTTON_STATE_PRESS;
			counter = 0;
			printf("One \n\r");
		}
	}
}

StateButton Button_checkState(Button* button)
{
	return button->state;
}
