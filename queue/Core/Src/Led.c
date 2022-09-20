#include <Led.h>
#include <stdio.h>
#include "cmsis_os.h"

extern TIM_HandleTypeDef htim2;
extern osMessageQueueId_t brightnessQueueHandle;
LedStatus ledState;

//void Led_init(Led* led , GPIO_TypeDef* GPIOx , uint16_t GPIO_Pin)
//{
//	led->state = STATE_OFF;
//	led->counter = 0 ;
//	led->GPIOx = GPIOx;
//	led->GPIO_Pin = GPIO_Pin;
//	led->delay = 1000;
//}


void Entry_blinkTask(void *obj)
{
  /* USER CODE BEGIN Entry_blinkTask */
  HAL_TIM_Base_Start_IT(&htim2);
  HAL_TIM_PWM_Start_IT(&htim2, TIM_CHANNEL_1);
  LedStatus msg;
  uint16_t brightness = 10;
  uint16_t delay = 500;
  osStatus_t status;
  /* Infinite loop */
  for(;;)
  {
	  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 0);
	  status = osMessageQueueGet(brightnessQueueHandle, &msg, 0, delay);
	  if (status == osOK) {
		  brightness = msg.brightness;
		  delay = msg.delay;
	  }
	  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, brightness*10);
	  osDelay(delay);

  }
  /* USER CODE END Entry_blinkTask */
}
