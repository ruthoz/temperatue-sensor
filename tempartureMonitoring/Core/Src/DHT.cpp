/*
 * DHT.cpp
 *
 *  Created on: Nov 16, 2022
 *      Author: student
 */

#include <DHT.h>
#include <stdio.h>
#include "cmsis_os.h"

#define MAX_BITS 40
extern TIM_HandleTypeDef htim16;

extern Dht dht;

int Dht::waitWhileEqual(int value, int expectedTime)
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

void Dht::setGpioOutput()
{
	GPIO_InitTypeDef gpioStruct = {0};

	gpioStruct.Pin = _gpioPin;
	gpioStruct.Mode = GPIO_MODE_OUTPUT_PP;
	gpioStruct.Pull = GPIO_NOPULL;
	gpioStruct.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(_gpioPort, &gpioStruct);
	HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
}

void Dht::setGpioInput()
{
	GPIO_InitTypeDef gpioStruct = {0};

	gpioStruct.Pin = _gpioPin;
	gpioStruct.Mode = GPIO_MODE_INPUT;
	gpioStruct.Pull = GPIO_NOPULL;
	gpioStruct.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(_gpioPort, &gpioStruct);
	HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
}

int Dht::read()
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
	reciveData();
	return 1;

}

int Dht::reciveData()
{
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

double Dht::getHumidty()
{
	return _humidity;
}

double Dht::getTemperature()
{
	return _temperature;
}


/* USER CODE END Header_StartDhtTask */
extern "C" void StartDhtTask()
{
  /* USER CODE BEGIN StartDhtTask */
  /* Infinite loop */
  while(1)
  {
	dht.read();
    osDelay(1000);
  }
  /* USER CODE END StartDhtTask */
}
