/*
 * Dht.c
 */

#include "Dht.h"
#include "main.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "cmsis_os.h"
#define MAX_BITS 40
extern Dht dht;
extern osSemaphoreId_t srtartDHTdataReadingHandle;
extern osSemaphoreId_t startDataPrintingHandle;


enum DhtState
{
	DHT_STATE_NO_DATA,
	DHT_STATE_READY,
	DHT_STATE_ERROR,
	DHT_STATE_POWER_ON,
	DHT_STATE_POWER_ON_ACK,
	DHT_STATE_INIT_RESPONSE,
	DHT_STATE_RECEIVE_DATA
};

void Dht_init(Dht * dht, GPIO_TypeDef * gpioPort, uint16_t gpioPin, TIM_HandleTypeDef * timer)
{
	dht->gpioPort = gpioPort;
	dht->gpioPin = gpioPin;
	dht->timer = timer;
	dht->counter = 0;
	dht->maxCounter = 0;
	dht->state = DHT_STATE_NO_DATA;
	dht->temperature = 0.0;
	dht->humidity = 0.0;
}

static int waitWhileEqual(Dht * dht, int value, int expectedTime)
{
	// set a timeout 20% bigger than the expected time
	int timeout = expectedTime + (expectedTime) / 5;

	__HAL_TIM_SET_COUNTER(dht->timer, 0);
	while (HAL_GPIO_ReadPin(dht->gpioPort, dht->gpioPin) == value) {
		if (__HAL_TIM_GET_COUNTER(dht->timer) > timeout) {
			// too much time in the state
			return false;
		}
	}

	return true;
}

static void setGpioOutput(Dht * dht)
{
	GPIO_InitTypeDef gpioStruct = {0};

	gpioStruct.Pin = dht->gpioPin;
	gpioStruct.Mode = GPIO_MODE_OUTPUT_PP;
	gpioStruct.Pull = GPIO_NOPULL;
	gpioStruct.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(dht->gpioPort, &gpioStruct);
	HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
}

static void setGpioInput(Dht * dht)
{
	GPIO_InitTypeDef gpioStruct = {0};

	gpioStruct.Pin = dht->gpioPin;
	gpioStruct.Mode = GPIO_MODE_INPUT;
	gpioStruct.Pull = GPIO_NOPULL;
	gpioStruct.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(dht->gpioPort, &gpioStruct);
	HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
}

static void setGpioExti(Dht * dht)
{
	GPIO_InitTypeDef gpioStruct = {0};

	gpioStruct.Pin = dht->gpioPin;
	gpioStruct.Mode = GPIO_MODE_IT_FALLING;
	gpioStruct.Pull = GPIO_PULLUP;

	HAL_GPIO_Init(dht->gpioPort, &gpioStruct);
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
}

int Dht_read(Dht * dht)
{
	setGpioOutput(dht);

	HAL_TIM_Base_Start(dht->timer);
	__HAL_TIM_SET_COUNTER(dht->timer, 0);

	// switch the sensor on by putting the line in '0'
	HAL_GPIO_WritePin(dht->gpioPort, dht->gpioPin, 0);
	while (__HAL_TIM_GET_COUNTER(dht->timer) < 19000);

	HAL_GPIO_WritePin(dht->gpioPort, dht->gpioPin, 1);

	// start listening
	setGpioInput(dht);

	// wait for response 20-40us
	if (!waitWhileEqual(dht, 1, 40)) {
		return HAL_ERROR;
	}

	// DHT should keep in low for 80us
	if (!waitWhileEqual(dht, 0, 80)) {
		return HAL_ERROR;
	}

	// DHT should keep in high for 80us
	if (!waitWhileEqual(dht, 1, 80)) {
		return HAL_ERROR;
	}

	// DHT start send data bits

	uint8_t data[5] = { 0 };
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 8; j++) {

			// DHT keeps in low for 50us before each bit
			if (!waitWhileEqual(dht, 0, 60)) {
				return HAL_ERROR;
			}

			// DHT sends bit keeping line in high maximum 70us
			if (!waitWhileEqual(dht, 1, 70)) {
				return HAL_ERROR;
			}

			data[i] <<= 1;

			// 26-28us for '0' and 70us for '1', so 50us is a good split time
			if (__HAL_TIM_GET_COUNTER(dht->timer) > 50) {
				data[i] |= 1;
			}
		}
	}

	uint8_t checksum = data[0] + data[1] + data[2] + data[3];
	if (checksum != data[4]) {
		return HAL_ERROR;
	}

	dht->humidity = (double)data[0] + ((double)data[1]) / 10;
	dht->temperature = (double)data[2] + ((double)data[3]) / 10;

	//printf("Humidity: %d.%d, temp: %d.%d\r\n", (int)data[0], (int)data[1], (int)data[2], (int)data[3]);

	// wait while DHT return to high
	if (!waitWhileEqual(dht, 0, 100)) {
		return HAL_ERROR;
	}

	HAL_TIM_Base_Stop(dht->timer);

	return HAL_OK;
}

//static void Dht_onTimerInterrupt(void * obj)
//{
//	Dht * dht = (Dht *)obj;
//
//	if (dht->state != DHT_STATE_POWER_ON) {
//		return;
//	}
//
//	dht->counter++;
//	if (dht->counter >= dht->maxCounter) {
//		dht->state = DHT_STATE_POWER_ON_ACK;
//		HAL_GPIO_WritePin(dht->gpioPort, dht->gpioPin, 1);
//		HAL_TIM_Base_Start(dht->timer);
//		__HAL_TIM_SET_COUNTER(dht->timer, 0);
//
//		setGpioExti(dht);
//
//		dht->counter = 0;
//		MainTimer_unregisterCallback(Dht_onTimerInterrupt, dht);
//	}
//}

//void Dht_readAsync(Dht * dht)
//{
//	setGpioOutput(dht);
//
//	// switch the sensor on by putting the line in '0'
//	HAL_GPIO_WritePin(dht->gpioPort, dht->gpioPin, 0);
//
//	// should be in '0' for 18-20 ms
//	MainTimer_registerCallback(Dht_onTimerInterrupt, dht);
//	dht->counter = 0;
//	dht->maxCounter = 19;
//
//	dht->state = DHT_STATE_POWER_ON;
//}

void Dht_onGpioInterrupt(Dht * dht, uint16_t pin)
{
	if (dht->gpioPin != pin) {
		return;
	}

	uint32_t timeMs = __HAL_TIM_GET_COUNTER(dht->timer);

	switch (dht->state)
	{
	case DHT_STATE_POWER_ON_ACK:
		if (timeMs > 50) {
			dht->state = DHT_STATE_ERROR;
		}
		dht->state = DHT_STATE_INIT_RESPONSE;
		break;

	case DHT_STATE_INIT_RESPONSE:
		if (timeMs > 200) {
			dht->state = DHT_STATE_ERROR;
		}

		memset(dht->data, 0, sizeof(dht->data));
		dht->bit = 0;
		dht->state = DHT_STATE_RECEIVE_DATA;

		break;

	case DHT_STATE_RECEIVE_DATA:
		{
			if (timeMs > 140) {
				dht->state = DHT_STATE_ERROR;
			}

			// 50us in low + 50 us in high (> 30 and < 70)
			int byte = dht->bit / 8;
			dht->data[byte] <<= 1;

			if (timeMs > 100) {
				// '1' is detected
				dht->data[byte] |= 1;
			}

			dht->bit++;
			if (dht->bit >= MAX_BITS) {

				uint8_t checksum = dht->data[0] + dht->data[1] +
						dht->data[2] + dht->data[3];

				if (checksum == dht->data[4]) {
					dht->state = DHT_STATE_READY;

					dht->humidity = (double)dht->data[0] + ((double)dht->data[1]) / 10;
					dht->temperature = (double)dht->data[2] + ((double)dht->data[3]) / 10;
				}
				else {
					dht->state = DHT_STATE_ERROR;
				}

				// stop timer and disable GPIO interrupts
				HAL_TIM_Base_Stop(dht->timer);
				HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
			}

		}
		break;

	default:
		// in all other states ignore the interrupt
		break;
	}

	__HAL_TIM_SET_COUNTER(dht->timer, 0);
}

int Dht_hasData(Dht * dht)
{
	int hasData = dht->state == DHT_STATE_READY;

	if (hasData) {
		// reset state to avoid multiple reads
		dht->state = DHT_STATE_NO_DATA;
	}

	return hasData;
}

double Dht_getHumidty(Dht * dht)
{
	return dht->humidity;
}

double Dht_getTempperature(Dht * dht)
{
	return dht->temperature;
}

void Entry_DhtTask(void *argument)
{
  /* USER CODE BEGIN Entry_DhtTask */
  /* Infinite loop */
  for(;;){
	osSemaphoreAcquire(srtartDHTdataReadingHandle,osWaitForever);
	Dht_read(&dht);
	osSemaphoreRelease(startDataPrintingHandle);
  }
  /* USER CODE END Entry_DhtTask */
}
