#include "main.h"


#ifndef SRC_LED_H_
#define SRC_LED_H_

typedef enum LedState{
		STATE_OFF,
		STATE_ON,
		STATE_BLINKING,
}LedState;

class Led{

private:
	LedState _state;
	GPIO_TypeDef* _GPIOx;
	uint16_t _GPIO_Pin;

public:
	Led(){};
    Led(GPIO_TypeDef* GPIOx , uint16_t GPIO_Pin);
    ~Led(){};

    void on();
    void off();
    void blink();

    GPIO_TypeDef* getGPIOx(){
    	return _GPIOx;
   }

    uint16_t getGPIO_Pin(){
        return _GPIO_Pin;
   }

    LedState getState(){
    	return _state;
   }
};

#endif /* SRC_LED_H_ */
