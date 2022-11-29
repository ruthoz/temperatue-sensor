/*
 * MyMain.cpp
 *
 *  Created on: Nov 20, 2022
 *      Author: student
 */

#include "MyMain.h"
#include "Led.h"
#include "Button.h"
#include "Buzzer.h"
#include "DHT.h"
#include "cmsis_os.h"
#include "Flash.h"

extern UART_HandleTypeDef huart2;
extern TIM_HandleTypeDef htim16;
extern TIM_HandleTypeDef htim3;
extern I2C_HandleTypeDef hi2c1;

Buzzer buzzer(&htim3);
Button button(B2_GPIO_Port ,  B2_Pin);
Led ledB(LD2_GPIO_Port , LD2_Pin );
Dht dht(DHT11_GPIO_Port , DHT11_Pin, &htim16);
Flash flash;
thresholdTemp Temprature;
log log;
Rtc rtc(&hi2c1, 0xD0);

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





extern "C" void StartManagerTask(void *argument)
{
  /* USER CODE BEGIN StartManagerTask */

	flash.read(&Temprature);
	stateTemp stateOfTemp = NORMAL_TEMPRATURE;
  /* Infinite loop */
	while(1)
	{
		rtc.getTime(log.dateTime);
		log.temparature=dht.getTempperature();
		///send log to file 1

	if(dht.getTempperature() > Temprature.criticalTemp){
		if(stateOfTemp!=CRITICAL_TEMPRATURE){
		ledB.blink();
		buzzer.on();
		stateOfTemp = CRITICAL_TEMPRATURE;
		//log.state = stateOfTemp;
		// send log to file2
		}
	}
	else if(dht.getTempperature() > Temprature.warningTemp){

		if(stateOfTemp==NORMAL_TEMPRATURE){
			ledB.on();
			stateOfTemp = WARNING_TEMPRATURE;
			// send log to file2
		}
		if(stateOfTemp==CRITICAL_TEMPRATURE &&
			dht.getTempperature() > (Temprature.criticalTemp-3)){
			buzzer.off();
			ledB.on();
			stateOfTemp = WARNING_TEMPRATURE;
			// send log to file2
		}

	}
	else{
		if(stateOfTemp==CRITICAL_TEMPRATURE){
					ledB.off();
					buzzer.off();
					stateOfTemp = NORMAL_TEMPRATURE;
					// send log to file2
		}
		if(stateOfTemp==WARNING_TEMPRATURE &&
					dht.getTempperature() > (Temprature.warningTemp-3)){
					ledB.off();
					stateOfTemp = NORMAL_TEMPRATURE;
					// send log to file2
		}
	}
	osDelay(1000);
  }
  /* USER CODE END StartManagerTask */
}





