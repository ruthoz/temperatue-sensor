
#include "mymain.h"
#include "Led.h"
#include "main.h"
#include "Button.h"
#include "CliCommand.h"
#include "CliContainer.h"
#include <Communication.h>

extern TIM_HandleTypeDef htim6;
Button button(B2_GPIO_Port ,  B2_Pin);
CliContainer CliContainer;
Led ledR(LD3_GPIO_Port , LD3_Pin );
Led ledB(LD2_GPIO_Port , LD2_Pin );

extern "C" void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * htim)
{
	if(htim == &htim6){
	///////////button///////////////////////////////////
		button.onTimerInterrupt();
	}

}

extern "C" void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	button.interrupt();
}


extern "C" void mainloop() {
	CliInit();
	ledB.on();
	while(1){
		if (Communication_commTask()){
				  Communication_handleCommand();
		}
		if(button.checkState() == BUTTON_LONG_PRESS){
			ledB.off();
		}
		if(button.checkState() == BUTTON_DOUBLE_PRESS){
			ledR.off();
		}
	}
}



