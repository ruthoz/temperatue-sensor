/*
 * MyMain.cpp
 *
 *  Created on: Nov 20, 2022
 *      Author: student
 */

#include "MyMain.h"
#include "Led.h"
#include "main.h"
#include "Button.h"
#include "CliCommand.h"
#include "CliContainer.h"
#include <Communication.h>
#include "cmsis_os.h"

extern Button button;
extern Led ledB;
extern UART_HandleTypeDef huart2;

//////////////////////////////////////////////////////////////
extern "C" int _write(int fd, char* ptr, int len)
{
	HAL_UART_Transmit(&huart2, (uint8_t*)ptr, len, HAL_MAX_DELAY);
	return len;
}
//////////////////////////////////////////////////////////////



thresholdTemp Temprature;

extern "C" void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	button.interrupt();
}


//extern "C" void mainloop() {

//
//	while(1){
//
//		if(button.checkState() == BUTTON_LONG_PRESS){
//			ledB.off();
//		}
//		if(button.checkState() == BUTTON_DOUBLE_PRESS){
//			ledB.on();
//		}
//	}
//}

/* USER CODE END Header_StartManagerTask */
extern "C" void StartManagerTask(void *argument)
{
  /* USER CODE BEGIN StartManagerTask */

  /* Infinite loop */
  while(1)
  {

    osDelay(300);
  }
  /* USER CODE END StartManagerTask */
}


