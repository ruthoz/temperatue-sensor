/*
 * Button.h
 *
 *  Created on: 17 Nov 2022
 *      Author: student
 */

#include "main.h"
#include "Buzzer.h"
#include <stdint.h>
#include <stdio.h>

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

typedef enum StateButon_
{
	BUTTON_STATE_NONE,
	BUTTON_STATE_PRESS,
	BUTTON_LONG_PRESS,
}StateButton;

class Button {
private:
	StateButton _state;
	uint32_t _timeTickOn;
	uint32_t _timeTickOff;
	GPIO_TypeDef* _GPIOx;
	uint16_t _GPIO_Pin;
public:


	Button(GPIO_TypeDef* GPIOx , uint16_t GPIO_Pin);
    ~Button(){};

    void interrupt();
    StateButton getState(){
    	return _state;
    }

};


#endif /* INC_BUTTON_H_ */
