#include "main.h"

#ifndef SRC_LED_H_
#define SRC_LED_H_



class Led {
private:

	typedef enum LedState_
	{
		STATE_OFF,
		STATE_ON,
		STATE_BLINKING,
	}LedState;

	LedState _state;
	GPIO_TypeDef* _GPIOx;
	uint16_t _GPIO_Pin;

public:
    Led(GPIO_TypeDef* GPIOx , uint16_t GPIO_Pin);
    ~Led(){};

    void on();
    void off();
    void blink();
};

#endif /* SRC_LED_H_ */
