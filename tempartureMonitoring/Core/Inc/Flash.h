/*
 * Flash.h
 *
 *  Created on: 17 Nov 2022
 *      Author: student
 */
#include "main.h"
#include "MyMain.h"

#ifndef FLASH_H_
#define FLASH_H_


class Flash
{
private:
	uint32_t _flashAdd;
	uint32_t _page;

public:

	Flash(){
		_page = 256;
		_flashAdd = 0x08080000;
	}
	~Flash(){};

	void erase();
	void writh( void* data, size_t size);
	void read(thresholdTemp* buffer);
};

#endif /* FLASH_H_ */





