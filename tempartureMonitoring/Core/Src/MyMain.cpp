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
#include "RTC.h"
#include "File.h"

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
Rtc rtc(&hi2c1, 0xD0);
DateTime dateTime;
File logFile("log.txt");
File warningFile("warning.txt");
static char logBuffer[100];

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
/////////////////////////////////////////////////////////////


void sendLog(){
	rtc.getTime(&dateTime);
	sprintf(logBuffer,"date time : %02d:%02d:%02d-%d-%02d/%02d/%02d temperature: %f \r\n",
				dateTime.hours, dateTime.min, dateTime.sec, dateTime.weekDay,
				dateTime.day, dateTime.month, dateTime.year,
				dht.getTemperature() );
	logFile.write(logBuffer);
}


void sendWarning(const char* message){
	rtc.getTime(&dateTime);
	sprintf(logBuffer,"date time : %02d:%02d:%02d-%d-%02d/%02d/%02d temperature: %f - %s \r\n",
					dateTime.hours, dateTime.min, dateTime.sec, dateTime.weekDay,
					dateTime.day, dateTime.month, dateTime.year,
					dht.getTemperature() , message );
	warningFile.write(logBuffer);
}

//////////////////////////////////////////////////////////////////////////
extern "C" void StartsendLogTask(void *argument)
{
  /* USER CODE BEGIN StartsendLogTask */
  /* Infinite loop */
  while(1)
  {
	// Wheat and send log all seconds
	osDelay(60000);
	sendLog();
  }
  /* USER CODE END StartsendLogTask */
}

extern "C" void StartManagerTask(void *argument)
{
  /* USER CODE BEGIN StartManagerTask */
	logFile.initSDCard();
	flash.read();
	stateTemp stateOfTemp = NORMAL_TEMPRATURE;
	/* Infinite loop */
	while(1)
	{

	//////////NORMAL TEMPERATURE///////////////////////
	if(dht.getTemperature() < Temprature.warningTemp){
			if(stateOfTemp==CRITICAL_TEMPRATURE){
						ledB.off();
						buzzer.off();
						stateOfTemp = NORMAL_TEMPRATURE;
			}
			else if(stateOfTemp==WARNING_TEMPRATURE &&
						dht.getTemperature() < (Temprature.warningTemp-3)){
						ledB.off();
						stateOfTemp = NORMAL_TEMPRATURE;
			}
	}
	///////////CRITICAL TEMPERATURE/////////////////////
	else if(dht.getTemperature() > Temprature.criticalTemp){
		if(stateOfTemp!=CRITICAL_TEMPRATURE){
		ledB.blink();
		buzzer.on();
		stateOfTemp = CRITICAL_TEMPRATURE;
		sendWarning("WARNING! THE TEMPERTURE IS CRITICAL!");
		}
	}
	//////////WARNING TEMPERATURE///////////////////////
	else{
		if(stateOfTemp==NORMAL_TEMPRATURE){
			ledB.on();
			stateOfTemp = WARNING_TEMPRATURE;
			sendWarning("WARNING! THE TEMPERTURE IS ABOVE NORMAL!");
		}
		else if(stateOfTemp==CRITICAL_TEMPRATURE &&
			dht.getTemperature() < (Temprature.criticalTemp-3)){
			buzzer.off();
			ledB.on();
			stateOfTemp = WARNING_TEMPRATURE;
			sendWarning("WARNING! THE TEMPERTURE IS ABOVE NORMAL!");
		}
	}

	osDelay(1);
  }
  /* USER CODE END StartManagerTask */
}





