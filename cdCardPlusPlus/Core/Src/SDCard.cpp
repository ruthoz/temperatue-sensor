/*
 * SDCard.cpp
 *
 *  Created on: Nov 27, 2022
 *      Author: student
 */

#include <SDCard.h>
extern UART_HandleTypeDef huart2;

SDCard::SDCard(const char* nameFile) {

	strcpy(_nameFile, nameFile);
	fres = f_mount(&FatFs, "", 1); //1=mount now
	if (fres != FR_OK) {
		myprintf("f_mount error (%i)\r\n", fres);
		while(1);
	}

	 //Let's get some statistics from the SD card

	FATFS* getFreeFs;

	fres = f_getfree("", &free_clusters, &getFreeFs);
	if (fres != FR_OK) {
	    myprintf("f_getfree error (%i)\r\n", fres);
	    while(1);
	}

	//Formula comes from ChaN's documentation
	total_sectors = (getFreeFs->n_fatent - 2) * getFreeFs->csize;
	free_sectors = free_clusters * getFreeFs->csize;

}

SDCard::~SDCard() {
	//We're done, so de-mount the drive
	f_mount(NULL, "", 0);
}
void SDCard::openFile(){
	fres = f_open(&fil, "_nameFile", FA_READ);
	if (fres != FR_OK) {
		myprintf("f_open error (%i)\r\n");
	    while(1);
	}
}

void SDCard::myprintf(const char *fmt, ...) {
  static char buffer[256];
  va_list args;
  va_start(args, fmt);
  vsnprintf(buffer, sizeof(buffer), fmt, args);
  va_end(args);

  int len = strlen(buffer);
  HAL_UART_Transmit(&huart2, (uint8_t*)buffer, len, -1);

}

void SDCard::printFile(){
	//Read 30 bytes from "test.txt" on the SD card
	 BYTE readBuf[30];

	//We can either use f_read OR f_gets to get data out of files
	//f_gets is a wrapper on f_read that does some string formatting for us
	TCHAR* rres = f_gets((TCHAR*)readBuf, 30, &fil);
	if(rres != 0) {
		myprintf("Read string from '%s' contents: %s\r\n", _nameFile, readBuf);
	} else {
		myprintf("f_gets error (%i)\r\n", fres);
	}

	//Be a tidy kiwi - don't forget to close your file!
	f_close(&fil);
}

void SDCard::writeToFile(char* readBuf){
	//Now let's try and write a file "write.txt"
	fres = f_open(&fil, "_nameFile", FA_WRITE | FA_OPEN_ALWAYS | FA_CREATE_ALWAYS);
	if(fres == FR_OK) {
    	myprintf("I was able to open 'write.txt' for writing\r\n");
	} else {
		myprintf("f_open error (%i)\r\n", fres);
    }

	UINT bytesWrote;
	fres = f_write(&fil, readBuf, sizeof(readBuf), &bytesWrote);
	if(fres == FR_OK) {
		myprintf("Wrote %i bytes to '%s'!\r\n", bytesWrote, _nameFile);
	} else {
		myprintf("f_write error (%i)\r\n");
	}

	 //Be a tidy kiwi - don't forget to close your file!
	f_close(&fil);
}




