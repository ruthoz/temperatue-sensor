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
#include "MainTimer.h"

extern TIM_HandleTypeDef htim6;
Button button(B2_GPIO_Port ,  B2_Pin);
CliContainer CliContainer;
//Led ledB(LD2_GPIO_Port , LD2_Pin );
MainTimer mainTimer;

extern "C" void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * htim)
{
	if(htim == &htim6){
	///////////button///////////////////////////////////
		mainTimer.callTimerFunc();
	}

}

extern "C" void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	button.interrupt();
}


//extern "C" void mainloop() {
//	CliInit();
//
//	while(1){
//		if (Communication_commTask()){
//				  Communication_handleCommand();
//		}
//		if(button.checkState() == BUTTON_LONG_PRESS){
//			ledB.off();
//		}
//		if(button.checkState() == BUTTON_DOUBLE_PRESS){
//			ledB.on();
//		}
//	}
//}




