/*
 * DHT.cpp
 *
 *  Created on: Nov 16, 2022
 *      Author: student
 */

#include <DHT.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>



#define MAX_BITS 40


int DHT::waitWhileEqual(int value, int expectedTime)
{
	// set a timeout 20% bigger than the expected time
	uint32_t timeout = expectedTime + (expectedTime) / 5;

	__HAL_TIM_SET_COUNTER(_timer, 0);
	while (HAL_GPIO_ReadPin(_gpioPort, _gpioPin) == value) {
		if (__HAL_TIM_GET_COUNTER(_timer) > timeout) {
			// too much time in the state
			return false;
		}
	}

	return true;
}

void DHT::setGpioOutput()
{
	GPIO_InitTypeDef gpioStruct = {0};

	gpioStruct.Pin = _gpioPin;
	gpioStruct.Mode = GPIO_MODE_OUTPUT_PP;
	gpioStruct.Pull = GPIO_NOPULL;
	gpioStruct.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(_gpioPort, &gpioStruct);
	HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
}

void DHT::setGpioInput()
{
	GPIO_InitTypeDef gpioStruct = {0};

	gpioStruct.Pin = _gpioPin;
	gpioStruct.Mode = GPIO_MODE_INPUT;
	gpioStruct.Pull = GPIO_NOPULL;
	gpioStruct.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(_gpioPort, &gpioStruct);
	HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
}

void DHT::setGpioExti()
{
	GPIO_InitTypeDef gpioStruct = {0};

	gpioStruct.Pin = _gpioPin;
	gpioStruct.Mode = GPIO_MODE_IT_FALLING;
	gpioStruct.Pull = GPIO_PULLUP;

	HAL_GPIO_Init(_gpioPort, &gpioStruct);
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
}

int DHT::read()
{
	setGpioOutput();

	HAL_TIM_Base_Start(_timer);
	__HAL_TIM_SET_COUNTER(_timer, 0);

	// switch the sensor on by putting the line in '0'
	HAL_GPIO_WritePin(_gpioPort,_gpioPin, GPIO_PIN_RESET);
	while (__HAL_TIM_GET_COUNTER(_timer) < 19000);

	HAL_GPIO_WritePin(_gpioPort,_gpioPin, GPIO_PIN_SET);

	// start listening
	setGpioInput();

	// wait for response 20-40us
	if (!waitWhileEqual( 1, 40)) {
		return HAL_ERROR;
	}

	// DHT should keep in low for 80us
	if (!waitWhileEqual(0, 80)) {
		return HAL_ERROR;
	}

	// DHT should keep in high for 80us
	if (!waitWhileEqual(1, 80)) {
		return HAL_ERROR;
	}

	// DHT start send data bits

	uint8_t data[5] = { 0 };
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 8; j++) {

			// DHT keeps in low for 50us before each bit
			if (!waitWhileEqual( 0, 60)) {
				return HAL_ERROR;
			}

			// DHT sends bit keeping line in high maximum 70us
			if (!waitWhileEqual( 1, 70)) {
				return HAL_ERROR;
			}

			data[i] <<= 1;

			// 26-28us for '0' and 70us for '1', so 50us is a good split time
			if (__HAL_TIM_GET_COUNTER(_timer) > 50) {
				data[i] |= 1;
			}
		}
	}

	uint8_t checksum = data[0] + data[1] + data[2] + data[3];
	if (checksum != data[4]) {
		return HAL_ERROR;
	}

	_humidity = (double)data[0] + ((double)data[1]) / 10;
	_temperature = (double)data[2] + ((double)data[3]) / 10;

	//printf("Humidity: %d.%d, temp: %d.%d\r\n", (int)data[0], (int)data[1], (int)data[2], (int)data[3]);

	// wait while DHT return to high
	if (!waitWhileEqual( 0, 100)) {
		return HAL_ERROR;
	}

	HAL_TIM_Base_Stop(_timer);

	return HAL_OK;
}

//static void DHT::onTimerInterrupt(void * obj)
//{
//	Dht * dht = (Dht *)obj;
//
//	if (_state != DHT_STATE_POWER_ON) {
//		return;
//	}
//
//	_counter++;
//	if (_counter >= _maxCounter) {
//		_state = DHT_STATE_POWER_ON_ACK;
//		HAL_GPIO_WritePin(_gpioPort, _gpioPin, 1);
//		HAL_TIM_Base_Start(_timer);
//		__HAL_TIM_SET_COUNTER(_timer, 0);
//
//		setGpioExti(this);
//
//		dht->counter = 0;
//		MainTimer_unregisterCallback(Dht_onTimerInterrupt, this);
//	}
//}

void DHT::readAsync()
{
	setGpioOutput();

	// switch the sensor on by putting the line in '0'
	HAL_GPIO_WritePin(_gpioPort, _gpioPin, GPIO_PIN_RESET);

	// should be in '0' for 18-20 ms
	//MainTimer_registerCallback(Dht_onTimerInterrupt);
	_counter = 0;
	_maxCounter = 19;

	_state = DHT_STATE_POWER_ON;
}

void DHT::onGpioInterrupt(uint16_t pin)
{
	if (_gpioPin != pin) {
		return;
	}

	uint32_t timeMs = __HAL_TIM_GET_COUNTER(_timer);

	switch (_state)
	{
	case DHT_STATE_POWER_ON_ACK:
		if (timeMs > 50) {
			_state = DHT_STATE_ERROR;
		}
		_state = DHT_STATE_INIT_RESPONSE;
		break;

	case DHT_STATE_INIT_RESPONSE:
		if (timeMs > 200) {
			_state = DHT_STATE_ERROR;
		}

		memset(_data, 0, sizeof(_data));
		_bit = 0;
		_state = DHT_STATE_RECEIVE_DATA;

		break;

	case DHT_STATE_RECEIVE_DATA:
		{
			if (timeMs > 140) {
				_state = DHT_STATE_ERROR;
			}

			// 50us in low + 50 us in high (> 30 and < 70)
			int byte = _bit / 8;
			_data[byte] <<= 1;

			if (timeMs > 100) {
				// '1' is detected
				_data[byte] |= 1;
			}

			_bit++;
			if (_bit >= MAX_BITS) {

				uint8_t checksum = _data[0] + _data[1] +
						_data[2] + _data[3];

				if (checksum == _data[4]) {
					_state = DHT_STATE_READY;

					_humidity = (double)_data[0] + ((double)_data[1]) / 10;
					_temperature = (double)_data[2] + ((double)_data[3]) / 10;
				}
				else {
					_state = DHT_STATE_ERROR;
				}

				// stop timer and disable GPIO interrupts
				HAL_TIM_Base_Stop(_timer);
				HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
			}

		}
		break;

	default:
		// in all other states ignore the interrupt
		break;
	}

	__HAL_TIM_SET_COUNTER(_timer, 0);
}

int DHT::hasData()
{
	int hasData = _state == DHT_STATE_READY;

	if (hasData) {
		// reset state to avoid multiple reads
		_state = DHT_STATE_NO_DATA;
	}

	return hasData;
}

double DHT::getHumidty()
{
	return _humidity;
}

double DHT::getTempperature()
{
	return _temperature;
}
