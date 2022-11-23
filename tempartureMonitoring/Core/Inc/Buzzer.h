/*
 * Buzzer.h
 *
 *  Created on: 17 Nov 2022
 *      Author: student
 */

#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_
#include "main.h"

class Buzzer {
private:
	typedef enum StateBuzzer_{
		MUSIC_ON,
		MUSIC_OFF,
	}StateBuzzer;

	TIM_HandleTypeDef * _timer;
	StateBuzzer _state;
	int _noteBuzzer[2];
	size_t _sizeOfMusic;
	uint8_t _currentNote;


public:


	Buzzer(TIM_HandleTypeDef * timer){
	_timer = timer;
	_noteBuzzer [0] = 390;
	_noteBuzzer [1] = 100;
	_state = MUSIC_OFF;
	_sizeOfMusic = (sizeof(_noteBuzzer) / sizeof(_noteBuzzer[0]));
	_currentNote= 0;
	}
	~Buzzer(){};

	void onTimerInterrupt();
	void playNextNote();
	void playNote();
	void on();
	void off();

};

#endif /* INC_BUZZER_H_ */






