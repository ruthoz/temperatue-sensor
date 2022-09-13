#include "Flash.h"
#include <stdio.h>
//static char data[256]= "hello world";
FLASH_EraseInitTypeDef basicFlash;
uint32_t page256Add = 0x08080000;
uint32_t page257Add = 0x08080800;
#define PAGE_SIZE 2048

void Flash_init(Flash* flash)
{
	flash->flashState=FLASH_STATE_NONE;
	flash->dataIndex=0;
	flash->flashAdd = page256Add;
	Flash_freeWrith(flash);
}

void Flash_erase(Flash* flash)
{
	flash->flashState = FLASH_STATE_ERASE;

	basicFlash.TypeErase = FLASH_TYPEERASE_PAGES;
	basicFlash.Banks = FLASH_BANK_2;
	basicFlash.Page = flash->page;
	basicFlash.NbPages = 1;

	HAL_FLASH_Unlock();

	HAL_FLASHEx_Erase_IT(&basicFlash);
}

void Flash_writh(Flash* flash, uint32_t flashAdd, void* data, uint32_t dataSize)
{
	if(flash->flashState==FLASH_STATE_ERASE){
		return;
	}

	///////////if page 257 full//////////
	if(flash->pageOfSet >= 4096){
		flash->page = 256;
		//flash->flashAdd = page256Add;
		flash->pageOfSet = 0;
		Flash_erase(flash);

	}
	/////////// if page 256 full//////////
	if(flash->pageOfSet >=2048){
		flash->page = 257;
		//flash->flashAdd = page256Add;
		Flash_erase(flash);
	}

	HAL_FLASH_Program_IT(FLASH_TYPEPROGRAM_DOUBLEWORD, flashAdd + flash->pageOfSet , *(uint64_t*)(data + flash->dataIndex));
	flash->pageOfSet +=8;
	flash->dataIndex +=8;


	///////////data over full//////////
	if((flash->dataIndex)>=dataSize){
		//flash->flashState = FLASH_STATE_NONE;
		flash->dataIndex = 0;

		//HAL_FLASH_Lock();

		//printf("%s\n\r", (char*)(flashAdd));
		if(flash->pageOfSet <=2048){
			printf("page 256\n\r");
		}
		else{
			printf("page 257\n\r");
		}

	}
}

void Flash_freeWrith(Flash* flash)
{
	for(int j=0; j<PAGE_SIZE*2 ; j+=8){
		uint32_t * readData = (uint32_t *)(page256Add+j);
		uint32_t value = *readData;
		if(value == 0xFFFFFFFFULL){
			if((j / PAGE_SIZE) == 0){
				flash->page = 256;
			}
			else{
				flash->page = 257;
			}
			//flash->flashAdd = (page256Add+j);
			flash->pageOfSet = j;
			return;
		}

    }
	flash->page = 256;
	//flash->flashAdd = page256Add;
	flash->pageOfSet = 0;
}

static char data[256]= "hello world";
void flash_onTimerInterrupt(Flash* flash){
	Flash_writh(flash, flash->flashAdd, data ,sizeof(data) );
}

