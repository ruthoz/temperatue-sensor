#include <Led.h>
#include <stdio.h>
#include "MainTimer.h"

extern TIM_HandleTypeDef htim4;

void Led_init(Led* led , GPIO_TypeDef* GPIOx , uint16_t GPIO_Pin)
{
	led->state = STATE_OFF;
	led->counter = 0 ;
	led->GPIOx = GPIOx;
	led->GPIO_Pin = GPIO_Pin;
}

void Led_on(Led* led)
{
	MainTimer_unRegisterCallback(Led_onTimerInterrupt , led);
	led->state = STATE_ON;
    HAL_GPIO_WritePin(led->GPIOx, led->GPIO_Pin, 1);
}

void Led_off(Led* led)
{
	MainTimer_unRegisterCallback(Led_onTimerInterrupt , led);
	led->state = STATE_OFF;
    HAL_GPIO_WritePin(led->GPIOx, led->GPIO_Pin, 0);
}

void Led_blink(Led* led, int period)
{
	MainTimer_registerCallback(Led_onTimerInterrupt , led);
	led->state = STATE_BLINKING;
	led->period = period;
	led->counter = 0;
}

void Led_onTimerInterrupt(void * obj)
{
	Led * led = (Led *)obj;
	if(led->state == STATE_BLINKING){
		led->counter++;
		if((led->counter) >= (led->period) ){
			HAL_GPIO_TogglePin(led->GPIOx, led->GPIO_Pin);
			led->counter = 0;

		}
	}
}

void Led_setBrightness(int brightness)
{
	if(brightness > 10 || brightness < 0 )
	{
		printf("Invalid command\r\n");
		return;
	}

	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, brightness*10);
	HAL_TIM_Base_Start_IT(&htim4);
	HAL_TIM_PWM_Start_IT(&htim4, TIM_CHANNEL_1);
}
