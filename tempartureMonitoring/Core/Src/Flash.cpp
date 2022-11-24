/*
 * Flash.cpp
 *
 *  Created on: 17 Nov 2022
 *      Author: student
 */

#include "Flash.h"


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

void Flash::writh(void* data, size_t size)
{
	erase();
	uint64_t* Data = (uint64_t *)(data);
	for(uint64_t i = 0; i < size ; i ++){
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, (uint32_t)_flashAdd+(i*8), *(Data+i));
	}
}

void Flash::read(thresholdTemp* buffer)
{
	HAL_FLASH_Unlock();
	thresholdTemp * data = (thresholdTemp *)(_flashAdd);
	if(data->magicNum!= 0x5A5A){
		return;
	}
	buffer = (thresholdTemp *)(_flashAdd);
}






