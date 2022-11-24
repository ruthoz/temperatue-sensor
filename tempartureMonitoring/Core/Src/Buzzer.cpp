/*
 * Buzzer.cpp
 *
 *  Created on: 17 Nov 2022
 *      Author: student
 */

#include <Buzzer.h>
extern TIM_HandleTypeDef htim3;
extern Buzzer buzzer;

void Buzzer::onTimerInterrupt()
{
	if(_state == MUSIC_ON){
		playNextNote();
	}
}

void Buzzer::playNextNote()
{
	_currentNote++;
	if(_currentNote >= _sizeOfMusic){
		_currentNote = 0;
	}
	playNote();
}

void Buzzer::playNote()
{
	__HAL_TIM_SET_COUNTER(_timer,0);
	__HAL_TIM_SET_AUTORELOAD(_timer, _noteBuzzer[_currentNote]);
	__HAL_TIM_SET_COMPARE(_timer, TIM_CHANNEL_1, (_noteBuzzer[_currentNote]/2));
}


void Buzzer::on(){
	_state = MUSIC_ON;
	HAL_TIM_Base_Start_IT(_timer);
	HAL_TIM_PWM_Start_IT(_timer, TIM_CHANNEL_1);
	playNote();
}

void Buzzer::off(){
	_state = MUSIC_OFF;
	HAL_TIM_Base_Stop_IT(_timer);
	HAL_TIM_PWM_Stop_IT(_timer, TIM_CHANNEL_1);
}
