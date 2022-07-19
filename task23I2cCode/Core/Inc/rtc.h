

#ifndef INC_RTC_H_
#define INC_RTC_H_

#include "main.h"
#include <stdint.h>


void setCode( uint32_t MainCode);
int getCode( uint32_t pass);
void rtcOnTimerInterrupt();
int timeOfEror(int counterTimeEror);
void setClock();
uint8_t timeInSec();
void lockSystem5min();
void lockOrOpen();
#endif /* INC_RTC_H_ */
