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
}StateButon;

typedef struct _button
{
	StateButon state;
	uint32_t timeTickOn;
	uint32_t timeTickOff;
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;

}BUTTON;

void buttonInit(BUTTON* button , GPIO_TypeDef* GPIOx , uint16_t GPIO_Pin);
void buttonInterrupt(BUTTON* button);
void buttonOnTimerInterrupt (BUTTON* button);
StateButon Button_checkState(BUTTON* button);

#endif /* INC_BUTTON_H_ */
