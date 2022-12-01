/*
 * Buzzer.cpp
 *
 *  Created on: 17 Nov 2022
 *      Author: student
 */

#include <Buzzer.h>

extern TIM_HandleTypeDef htim3;
extern Buzzer buzzer;


void Buzzer::on(){
	_state = MUSIC_ON;
	HAL_TIM_Base_Start_IT(_timer);
	HAL_TIM_PWM_Start_IT(_timer, TIM_CHANNEL_1);
}

void Buzzer::off(){
	_state = MUSIC_OFF;
	HAL_TIM_Base_Stop_IT(_timer);
	HAL_TIM_PWM_Stop_IT(_timer, TIM_CHANNEL_1);
}
