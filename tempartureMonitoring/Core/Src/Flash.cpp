/*
 * Flash.cpp
 *
 *  Created on: 17 Nov 2022
 *      Author: student
 */

#include "Flash.h"


Flash flash;
void Flash::erase()
{
	uint32_t pageError;
	FLASH_EraseInitTypeDef basicFlash;

	basicFlash.TypeErase = FLASH_TYPEERASE_PAGES;
	basicFlash.Banks = FLASH_BANK_2;
	basicFlash.Page = _page;
	basicFlash.NbPages = 1;

	HAL_FLASH_Unlock();

	HAL_FLASHEx_Erase(&basicFlash, &pageError);
}

void Flash::writh(void* data)
{
	erase();

	int size = sizeof(data);
	for(int i = 0; i < size; i += sizeof(uint64_t)){
			uint64_t Data = *(uint64_t *)(data+i);
			HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, (uint32_t)_flashAdd+i, Data);
	}
}

void Flash::read( thresholdTemp* buffer)
{
	buffer = (thresholdTemp *)(_flashAdd);
}






