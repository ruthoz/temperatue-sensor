/*
 * MyMain.cpp
 *
 *  Created on: Nov 20, 2022
 *      Author: student
 */

#include "MyMain.h"
#include "main.h"
#include "Led.h"
#include "Button.h"
#include "DHT.h"
#include "Flash.h"
#include "CliCommand.h"
#include "CliContainer.h"
#include <Communication.h>
#include "cmsis_os.h"

extern Button button;
extern Led ledB;
extern Dht dht;
extern Flash flash;
extern UART_HandleTypeDef huart2;

//////////////////////////////////////////////////////////////
extern "C" int _write(int fd, char* ptr, int len)
{
	HAL_UART_Transmit(&huart2, (uint8_t*)ptr, len, HAL_MAX_DELAY);
	return len;
}
//////////////////////////////////////////////////////////////


extern "C" void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	button.interrupt();
}


thresholdTemp Temprature;
/* USER CODE END Header_StartManagerTask */
extern "C" void StartManagerTask(void *argument)
{
  /* USER CODE BEGIN StartManagerTask */

	flash.read(&Temprature);
  /* Infinite loop */
	while(1)
	{
	if(dht.getTempperature() > Temprature.criticalTemp){
		ledB.blink();
	}
	else{
		ledB.off();
	}
	osDelay(1000);
  }
  /* USER CODE END StartManagerTask */
}


