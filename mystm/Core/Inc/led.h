

#ifndef INC_LED_H_
#define INC_LED_H_

#include "main.h"

typedef enum LEDstate_
{
	STATE_OFF,
	STATE_ON,
	STATE_BLINKING,
}LED_STATE;

typedef struct _led
{
	LED_STATE state;
	int counter;
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
	int period;

}LED;

void ledInit(LED* led , GPIO_TypeDef* GPIOx , uint16_t GPIO_Pin);
void ledOn(LED* led);
void ledOff(LED* led);
void ledBlink(LED* led, int period);
void ledOnTimerInterrupt(LED* led);
void setBrightness(int brightness);
void ledOnPeriodicTask(LED* led);


#endif /* INC_LED_H_ */
