

#ifndef INC_LED_H_
#define INC_LED_H_

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

}Led;

void Led_init(Led* led , GPIO_TypeDef* GPIOx , uint16_t GPIO_Pin);
void Led_on(Led* led);
void Led_off(Led* led);
void Led_blink(Led* led, int period);
void Led_onTimerInterrupt(void * led);
void Led_setBrightness(int brightness);


#endif /* INC_LED_H_ */
