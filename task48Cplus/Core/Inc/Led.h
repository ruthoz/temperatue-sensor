#include "mymain.h"

#ifndef INC_LED_H_
#define INC_LED_H_


class Led {
private:
	GPIO_TypeDef* _GPIOx;
	uint16_t _GPIO_Pin;
public:
    Led(GPIO_TypeDef* GPIOx , uint16_t GPIO_Pin);
    //~Led();
    void on();
    void off();
    void blink();
};

#endif /* INC_LED_H_ */
