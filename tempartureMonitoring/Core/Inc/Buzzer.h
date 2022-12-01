/*
 * Buzzer.h
 *
 *  Created on: 17 Nov 2022
 *      Author: student
 */

#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_
#include "main.h"

typedef enum StateBuzzer_{
		MUSIC_ON,
		MUSIC_OFF,
}StateBuzzer;

class Buzzer {
private:
	StateBuzzer _state;
	TIM_HandleTypeDef * _timer;

public:
	Buzzer(TIM_HandleTypeDef * timer){
	_timer = timer;
	}
	~Buzzer(){};

	void on();
	void off();
	StateBuzzer getstate(){
		return _state;
	}
};

#endif /* INC_BUZZER_H_ */






