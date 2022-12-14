/*
 * App.h
 *
 *  Created on: Oct 13, 2022
 *      Author: student
 */

#ifndef INC_APP_H_
#define INC_APP_H_

#include "main.h"


typedef struct ApplicationInfo_{
	uint16_t magicNamber;
	uint32_t version;
	uint8_t appType;
	uint32_t crc;
	uint8_t flag;
}ApplicationInfo;


void printAppVer(const ApplicationInfo* app);



#endif /* INC_APP_H_ */
