/*
 * flash.h
 *
 *  Created on: Sep 6, 2022
 *      Author: student
 */

#ifndef INC_FLASH_H_
#define INC_FLASH_H_

#include "main.h"
#include <stdint.h>

typedef enum FlashState
{
	FLASH_STATE_NONE,
	FLASH_STATE_ERASE,
	FLASH_STATE_WRITE,
}FlashState;

typedef struct _Flash
{
	FlashState flashState;
	uint32_t flashAdd;
	uint32_t page;
	int pageOfSet;
	int dataIndex;
}Flash;

void Flash_init(Flash* flash);
void Flash_erase(Flash* flash);
void Flash_writh(Flash* flash, uint32_t flashAdd, void* data, uint32_t dataSize);
void Flash_freeWrith(Flash* flash);
void flash_onTimerInterrupt(Flash* flash);

#endif /* INC_FLASH_H_ */
