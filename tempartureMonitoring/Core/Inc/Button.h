/*
 * Button.h
 *
 *  Created on: 17 Nov 2022
 *      Author: student
 */

#include "main.h"
#include <stdint.h>
#include "TimerTask.h"

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

typedef enum StateButon_
{
	BUTTON_STATE_NONE,
	BUTTON_STATE,
	BUTTON_STATE_PRESS,
	BUTTON_LONG_PRESS,
	BUTTON_DOUBLE_PRESS,
}StateButton;

class Button : public TimerTask {
private:
	StateButton state;
	uint32_t timeTickOn;
	uint32_t timeTickOff;
	GPIO_TypeDef* _GPIOx;
	uint16_t _GPIO_Pin;
public:


	Button(GPIO_TypeDef* GPIOx , uint16_t GPIO_Pin);
    //~Button();
    void interrupt();
    StateButton checkState();
    void timerFunc() override;

};


#endif /* INC_BUTTON_H_ */
