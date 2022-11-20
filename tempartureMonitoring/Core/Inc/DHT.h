#include "main.h"
#include "TimerTask.h"
#include "MainTimer.h"

#ifndef INC_DHT_H_
#define INC_DHT_H_


class Dht : public TimerTask {
private:

	enum DhtState{
		DHT_STATE_NO_DATA,
		DHT_STATE_READY,
		DHT_STATE_ERROR,
		DHT_STATE_POWER_ON,
		DHT_STATE_POWER_ON_ACK,
		DHT_STATE_INIT_RESPONSE,
		DHT_STATE_RECEIVE_DATA
	};

	GPIO_TypeDef * _gpioPort;
	uint16_t _gpioPin;
	TIM_HandleTypeDef * _timer;
	int _counter;
	int _maxCounter;
	int _state;
	uint8_t _data[5];
	int _bit;
	double _temperature;
	double _humidity;

public:
	Dht( GPIO_TypeDef* gpioPort, uint16_t gpioPin, TIM_HandleTypeDef * timer){
		_gpioPort = gpioPort;
		_gpioPin = gpioPin;
		_timer = timer;
		_counter = 0;
		_maxCounter = 0;
		_state = DHT_STATE_NO_DATA;
		_temperature = 0.0;
		_humidity = 0.0;
	}
	~Dht(){};
	// sync read
	int read();

	// async read
	void readAsync();
	void timerFunc() override;
	//void onGpioInterrupt(uint16_t pin);
	int hasData();

	int waitWhileEqual(int value, int expectedTime);
	void setGpioOutput();
	void setGpioInput();
	void setGpioExti();

	// shared between sync and async
	double getHumidty();
	double getTempperature();
};

#endif /* INC_DHT_H_ */




