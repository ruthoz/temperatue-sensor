/*
 * Flash.cpp
 *
 *  Created on: 17 Nov 2022
 *      Author: student
 */

#include "Flash.h"
#include <stdio.h>

void Flash::erase()
{
	_flashState = FLASH_STATE_ERASE;
	FLASH_EraseInitTypeDef basicFlash;

	basicFlash.TypeErase = FLASH_TYPEERASE_PAGES;
	basicFlash.Banks = FLASH_BANK_2;
	basicFlash.Page = _page;
	basicFlash.NbPages = 1;

	HAL_FLASH_Unlock();

	HAL_FLASHEx_Erase_IT(&basicFlash);
}

void Flash::writh( void* data, uint32_t dataSize)
{
	if(_flashState==FLASH_STATE_ERASE){
		return;
	}

	HAL_FLASH_Program_IT(FLASH_TYPEPROGRAM_DOUBLEWORD, _flashAdd , *(uint64_t*)(data + _dataIndex));
	_dataIndex +=8;

	///////////data over full//////////
	if((_dataIndex)>=dataSize){
		_dataIndex = 0;

		//HAL_FLASH_Lock();
	}
}






