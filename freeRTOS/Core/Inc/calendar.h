/*
 * calender.h
 *
 *  Created on: Jun 30, 2022
 *      Author: student
 */

#ifndef SRC_CALENDER_H_
#define SRC_CALENDER_H_

#include "main.h"
#include <stdint.h>

typedef struct _calendar
{
	int seconds;
	int seconds10;
	int minutes;
	int minutes10;
	int hours;
	int hours10;
	int days;
	int date;
	int date10;
	int month;
	int month10;
	int year;
	int year10;

}CALENDAR;


int DecToBin (int dec);

#endif /* SRC_CALENDER_H_ */
