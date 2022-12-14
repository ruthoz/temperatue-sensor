#include "Button.h"
#include "Buzzer.h"
#include "Clock.h"
#include "Communication.h"
#include "Led.h"
#include "MyMain.h"
#include "CLI.h"
#include "DHT11.h"
#include "MainTimer.h"
#include "Flash.h"
#include "App.h"
#include <stdio.h>

extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart2;
//version
#define MAJOR   1
#define MINOR   1<<8
#define RELEASE 3<<16
#define BUILD   5<<24

const ApplicationInfo app = {.magicNamber = 0x5A5A,
  	                         .version = MAJOR|MINOR|RELEASE|BUILD,
  	                         .appType = 1,
  	                         .flag = 0,
  	                         .crc = 0,};
Led ledR;
Led ledB;
Button button1;
Buzzer buzzer;
Clock clock1;
Dht11 TempHum;
Flash flash;


//////////////////////////////////////////////////////////////
int _write(int fd, char* ptr, int len)
{
	HAL_UART_Transmit(&huart2, (uint8_t*)ptr, len, HAL_MAX_DELAY);
	return len;
}
//////////////////////////////////////////////////////////////

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * htim)
{
	if(htim == &htim6){
		MainTimer_onTimerInterrupt();
    ////////////////led////////////////////////////////////
	//	Led_onTimerInterrupt(&ledB);
	//	Led_onTimerInterrupt(&ledR);

	//////////////clock///////////////////////////////////
	//	Clock_onTimerInterrupt(&clock1);

	/////////////buzzer//////////////////////////////////
	//	Buzzer_onTimerInterrupt(&buzzer);

	///////////button///////////////////////////////////
		Button_onTimerInterrupt(&button1);

		////////////Dht11//////////////////////////
	//Dht11_onTimerInterrupt(&TempHum);

		//////////////////////////////////////////
	//flash_onTimerInterrupt(&flash);


	}

}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == TempHum.gpioPin){
		Dht11_onGpioInterrupt(&TempHum, TempHum.gpioPin);
	}

	Button_interrupt(&button1);
}


void MyFlashInterruptHandler()
{
	if(flash.flashState==FLASH_STATE_WRITE){
		flash.flashState=FLASH_STATE_NONE;
	}
	if(flash.flashState==FLASH_STATE_ERASE){
		flash.flashState=FLASH_STATE_WRITE;
	}
}


void mainloop()
{
	HAL_TIM_Base_Start_IT(&htim6);

	MainTimer_Init();
	Led_init(&ledB , LD2_GPIO_Port , LD2_Pin );
	Led_init(&ledR , LD3_GPIO_Port , LD3_Pin );
	Buzzer_init(&buzzer);
	Clock_init(&clock1);
	Button_init(&button1, B2_GPIO_Port ,  B2_Pin);
	//Flash_init(&flash);
	Cli_init();
	Dht11_init(&TempHum);

#ifdef DEBUG
	printAppVer(&app);
#endif

	while(1){
		Dht11_hasData(&TempHum);
		if (Communication_commTask()){
			Communication_handleCommand();
		}
	}

}
