/*
 * Flash.h
 *
 *  Created on: 17 Nov 2022
 *      Author: student
 */
#include "main.h"
#include <stdio.h>

#ifndef FLASH_H_
#define FLASH_H_

class Flash {
private:
	typedef enum FlashState{
		FLASH_STATE_NONE,
		FLASH_STATE_ERASE,
		FLASH_STATE_WRITE,
	}FlashState;

	FlashState _flashState;
	uint32_t _flashAdd;
	uint32_t _page;
	uint8_t _dataIndex;

public:

	Flash(){
		_flashState=FLASH_STATE_NONE;
		_dataIndex=0;
		_page = 256;
		_flashAdd = 0x08080000;
	}
	~Flash(){};

	void erase();
	void writh( void* data, uint32_t dataSize);
};

#endif /* FLASH_H_ */





