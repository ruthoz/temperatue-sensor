

#include "main.h"

#ifndef INC_RTC_H_
#define INC_RTC_H_

typedef struct DateTime_{
		int sec;
		int min;
		int hours;
		int weekDay;
		int day;
		int month;
		int year;
	} DateTime;

class Rtc {
private:
	I2C_HandleTypeDef * _hi2c;
	uint8_t _devAddr;

	int bcdToInt(uint8_t bcd);
	uint8_t intToBcd(int value, int minVal, int maxVal);

public:
	Rtc(I2C_HandleTypeDef * hi2c, uint32_t devAddr){
		_hi2c = hi2c;
		_devAddr = devAddr;
	};
	~Rtc(){};

	void getTime(DateTime* dateTime);
	void setTime(DateTime* dateTime);

};

#endif /* INC_RTC_H_ */
