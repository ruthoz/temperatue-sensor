/*
 * button.h
 *
 *  Created on: Jun 14, 2022
 *      Author: student
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"
#include <stdint.h>

typedef enum StateButon_
{
	BUTTON_STATE_NONE,
	BUTTON_STATE,
	BUTTON_STATE_PRESS,
	BUTTON_LONG_PRESS,
	BUTTON_DOUBLE_PRESS,
}StateButton;

typedef struct _Button
{
	StateButton state;
	uint32_t timeTickOn;
	uint32_t timeTickOff;
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;

}Button;

void Button_init(Button* button , GPIO_TypeDef* GPIOx , uint16_t GPIO_Pin);
void Button_interrupt(Button* button);
void Button_onTimerInterrupt (Button* button);
StateButton Button_checkState(Button* button);

#endif /* INC_BUTTON_H_ */
