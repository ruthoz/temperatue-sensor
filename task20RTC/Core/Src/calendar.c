#include "calendar.h"
#include <stdio.h>

extern I2C_HandleTypeDef hi2c1;
uint8_t readBuff[7];
void printTime(CALENDAR* mytime)
{

  HAL_I2C_Mem_Read(&hi2c1, 208, 0, 1, readBuff, 7, 0xff);
  mytime->seconds = (readBuff[0] & 15);
  mytime->seconds10 = (readBuff[0] >> 4);
  mytime->minutes = (readBuff[1] & 15);
  mytime->minutes10 = (readBuff[1] >>4);
  mytime->hours = (readBuff[2] & 15);
  mytime->hours10 = (readBuff[2] >> 4);
  mytime->days = readBuff[3];
  mytime->date = (readBuff[4] & 15);
  mytime->date10 = (readBuff[4] >> 4);
  mytime->month = (readBuff[5] & 15);
  mytime->month10 = (readBuff[5] >> 4);
  mytime->year = (readBuff[6] & 15);
  mytime->year10 = (readBuff[6] >> 4);

  printf("year month date day hour min sec \n\r");
  printf("20%d%d:%d%d:%d%d:%d:%d%d:%d%d:%d%d \n\r" ,mytime->year10, mytime->year, mytime->month10, mytime->month, mytime->date10, mytime->date, mytime->days, mytime->hours10, mytime->hours, mytime->minutes10, mytime->minutes, mytime->seconds10, mytime->seconds);

}

int DecToBin (int dec)
{
	int right=  dec % 10;
	int left= dec / 10;

	return (left<<4| right) ;
}


