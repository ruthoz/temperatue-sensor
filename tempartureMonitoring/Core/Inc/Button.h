/*
 * Button.h
 *
 *  Created on: 17 Nov 2022
 *      Author: student
 */

#include "main.h"
#include <stdint.h>
#include <stdio.h>

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

typedef enum StateButon_
{
	BUTTON_STATE_NONE,
	BUTTON_STATE_WAITH,
	BUTTON_STATE_PRESS,
	BUTTON_LONG_PRESS,
	BUTTON_DOUBLE_PRESS,
}StateButton;

class Button {
private:
	StateButton _state;
	uint32_t _timeTickOn;
	uint32_t _timeTickOff;
	GPIO_TypeDef* _GPIOx;
	uint16_t _GPIO_Pin;
	uint32_t _counter;
public:


	Button(GPIO_TypeDef* GPIOx , uint16_t GPIO_Pin);
    ~Button(){};
    void interrupt();
    StateButton getState();
    uint32_t getCounter();
    void setState(StateButton state);
    void plusCounter();
    void resetCounter();

};


#endif /* INC_BUTTON_H_ */
