

#ifndef INC_DHT_H_
#define INC_DHT_H_

#include "main.h"

typedef struct Dht_
{
	GPIO_TypeDef * gpioPort;
	uint16_t gpioPin;
	TIM_HandleTypeDef * timer;
	int counter;
	int maxCounter;
	int state;
	uint8_t data[5];
	int bit;
	double temperature;
	double humidity;
} Dht;

// sync read
int Dht_read(Dht * dht);

// async read
void Dht_readAsync(Dht * dht);
//void Dht_onGpioInterrupt(Dht * dht, uint16_t pin);
int Dht_hasData(Dht * dht);

// shared between sync and async
void Dht_init(Dht * dht, GPIO_TypeDef * gpioPort, uint16_t gpioPin, TIM_HandleTypeDef * timer);
double Dht_getHumidty(Dht * dht);
double Dht_getTempperature(Dht * dht);

#endif /* INC_DHT_H_ */



