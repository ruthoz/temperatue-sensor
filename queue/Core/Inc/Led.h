

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
	int delay;

}Led;

typedef struct LedStatus_
{
	uint16_t delay;
	uint16_t brightness;
}LedStatus;

void Led_init(Led* led , GPIO_TypeDef* GPIOx , uint16_t GPIO_Pin);
void Led_Brightness();


#endif /* INC_LED_H_ */
