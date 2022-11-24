/*
 * MyMain.h
 *
 *  Created on: Nov 20, 2022
 *      Author: student
 */

#ifndef INC_MYMAIN_H_
#define INC_MYMAIN_H_

#include "main.h"


struct thresholdTemp
{
		uint16_t criticalTemp = 70;
		uint16_t warningTemp = 50;
		uint16_t  magicNum = 0x5A5A;
};

typedef enum _stateTemp{
		CRITICAL_TEMPRATURE,
		WARNING_TEMPRATURE,
		NORMAL_TEMPRATURE,
}stateTemp;



#endif /* INC_MYMAIN_H_ */
