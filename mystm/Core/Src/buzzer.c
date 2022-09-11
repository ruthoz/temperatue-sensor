#include <Buzzer.h>
#include "MainTimer.h"

extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim3;

int note []={ 390, 340, 303, 286, 255, 227, 202};
int noteJonatan []= {255 , 303,  303,  286, 340, 340, 390, 340, 303, 286, 255, 255, 255, 255 , 303,  303,  286, 340, 340 ,390, 303, 255, 255,390};
int periodeJonatan[]={250, 250,  500,  250, 250, 500, 250, 250, 250, 250, 500, 250, 250, 250,  250,  500,  250, 250, 500, 250, 250, 250 ,500,250};

void Buzzer_init(Buzzer* buzzer)
{
	buzzer->state = MUSIC_OFF;
	buzzer->sizeOfMusic = (sizeof(noteJonatan) / sizeof(noteJonatan[0]));
	buzzer->currentNote= 0;
	buzzer->counter = 0;
	buzzer->maxCount = periodeJonatan[0];
}

void Buzzer_playNote(Buzzer* buzzer)
{
	__HAL_TIM_SET_COUNTER(&htim3,0);
	__HAL_TIM_SET_AUTORELOAD(&htim3, noteJonatan[buzzer->currentNote]);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, (noteJonatan[buzzer->currentNote]/2));
}

void Buzzer_playNextNote(Buzzer* buzzer)
{
	buzzer->currentNote++;
	if(buzzer->currentNote >= buzzer->sizeOfMusic){
		buzzer->currentNote = 0;
	}
	buzzer->maxCount = periodeJonatan [buzzer->currentNote];
	Buzzer_playNote(buzzer);
}

void Buzzer_onTimerInterrupt(void* obj)
{
	Buzzer * buzzer = (Buzzer*)obj;
	if(buzzer->state == MUSIC_ON){
		buzzer->counter++;
		if(buzzer->counter >= buzzer->maxCount){
			Buzzer_playNextNote(buzzer);
			buzzer->counter = 0;
		}
	}

}

void Buzzer_on(Buzzer* buzzer){
	MainTimer_registerCallback(Buzzer_onTimerInterrupt , buzzer);
	buzzer->state = MUSIC_ON;
	HAL_TIM_Base_Start_IT(&htim3);
	HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_1);
	Buzzer_playNote(buzzer);
}

void Buzzer_off(Buzzer* buzzer){
	MainTimer_unRegisterCallback(Buzzer_onTimerInterrupt , buzzer);
	buzzer->state = MUSIC_OFF;
	HAL_TIM_Base_Stop_IT(&htim3);
	HAL_TIM_PWM_Stop_IT(&htim3, TIM_CHANNEL_1);
}


