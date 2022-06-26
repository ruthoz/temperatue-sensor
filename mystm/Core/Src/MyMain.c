#include "MyMain.h"
#include "led.h"
#include "button.h"
#include "buzzer.h"
#include "clock.h"
#include <stdio.h>

extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart2;

LED ledR;
LED ledB;
BUTTON button1;
BUZZER buzzer;
CLOCK clock1;

int _write(int fd, char* ptr, int len)
{
	HAL_UART_Transmit(&huart2, (uint8_t*)ptr, len, HAL_MAX_DELAY);
	return len;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * htim)
{
	if(htim == &htim6){
    ////////////////led////////////////////////////////////
	  ledOnTimerInterrupt(&ledB);
	  ledOnTimerInterrupt(&ledR);

	//////////////clock//////////////////////////////////
	  clockOnTimerInterrupt(&clock1);

	/////////////buzzer/////////////////////////////////
	  buzzerOnTimerInterrupt(&buzzer);

	///////////button//////////////////////////////////
	  buttonOnTimerInterrupt (&button1);

	}


}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	buttonInterrupt(&button1);
//	if(buzzer.state == MUSIC_OFF){
//	    	buzzer.state = MUSIC_ON;
//			HAL_TIM_Base_Start_IT(&htim3);
//			HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_1);
//			playNote(&buzzer);
//		}
//		else{
//			buzzer.state = MUSIC_OFF;
//			HAL_TIM_Base_Stop_IT(&htim3);
//			HAL_TIM_PWM_Stop_IT(&htim3, TIM_CHANNEL_1);
//		}


}


void mainloop()
{
	HAL_TIM_Base_Start_IT(&htim6);

	ledInit(&ledB , LD2_GPIO_Port , LD2_Pin );
	ledInit(&ledR , LD3_GPIO_Port , LD3_Pin );
	buzzerInit(&buzzer);
	clockInit(&clock1);
	buttonInit(&button1, B2_GPIO_Port ,  B2_Pin);
	StateButon sw1State;

	while(1)
	{
		sw1State = Button_checkState(&button1);

		if(sw1State != BUTTON_STATE_NONE){
		   switch(sw1State)
		  {
		     case BUTTON_STATE_PRESS:
			 printf("STATE \n\r"); break;

		     case BUTTON_LONG_PRESS:
			 printf("LONG \n\r"); break;

		     case BUTTON_DOUBLE_PRESS:
			 printf("DOBULE \n\r"); break;
		  }
		   sw1State = BUTTON_STATE_NONE;
		}



	}

}