/*
 * Led.h
 *
 *  Created on: Sep 13, 2022
 *      Author: student
 */

#ifndef SRC_LED_H_
#define SRC_LED_H_

#include "main.h"
typedef enum LedState_
{
	STATE_OFF,
	STATE_ON,
	STATE_BLINKING,
}LedState;

typedef struct Led_
{
	LedState state;
	int counter;
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
	int period;
	int delay;

}Led;

void Led_init(Led* led , GPIO_TypeDef* GPIOx , uint16_t GPIO_Pin);
void setBlinkLed(void* obj, char* param);

#endif /* SRC_LED_H_ */
