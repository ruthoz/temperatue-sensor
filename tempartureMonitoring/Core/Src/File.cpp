/*
 * File.cpp
 *
 *  Created on: Nov 29, 2022
 *      Author: student
 */

#include <File.h>

extern UART_HandleTypeDef huart2;

File::File(const char* nameFile) {
	strcpy(_nameFile, nameFile);
}


void File::initSDCard(){
	HAL_Delay(1000);
	fres = f_mount(&FatFs, "", 1); //1=mount now
	if (fres != FR_OK) {
		printf("f_mount error (%i)\r\n", fres);
		return;
	}
}

void File::read(){
	fres = f_open(&fil, _nameFile, FA_READ);
	if (fres != FR_OK) {
		printf("f_open error (%i)\r\n", fres);
		return;
	}
	//Read 250 bytes from "file" on the SD card
	 BYTE readBuf[256];

	//We can either use f_read OR f_gets to get data out of files
	//f_gets is a wrapper on f_read that does some string formatting for us
	TCHAR* rres = f_gets((TCHAR*)readBuf, 256, &fil);
	if(rres == 0){
		printf("f_gets error (%i)\r\n", fres);
	}
	while(rres != 0) {
		rres = f_gets((TCHAR*)readBuf, 256, &fil);
		printf("Read string from file contents: %s\r\n", readBuf);
	}

	//Be a tidy kiwi - don't forget to close your file!
	f_close(&fil);


}

void File::write(const char* writeBuf){
	//write a file "write.txt"
	fres = f_open(&fil, _nameFile, FA_WRITE | FA_OPEN_APPEND | FA_OPEN_EXISTING);
	if(fres == FR_OK) {
    	//printf("I was able to open 'write.txt' for writing\r\n");
	} else {
		printf("f_open error (%i)\r\n", fres);
    }

	UINT bytesWrote;
	fres = f_write(&fil, writeBuf, strlen(writeBuf), &bytesWrote);
	if(fres == FR_OK) {
		//printf("Wrote %i bytes to '%s'!\r\n", bytesWrote, _nameFile);
	} else {
		printf("f_write error (%i)\r\n", fres);
	}

	 //Be a tidy kiwi - don't forget to close your file!
	f_close(&fil);
}

void File::clear(){

	//write a file "write.txt"
	fres = f_open(&fil, _nameFile, FA_CREATE_ALWAYS);
	if(fres == FR_OK) {
    	//myprintf("I was able to open 'write.txt' for writing\r\n");
	} else {
		printf("f_open error (%i)\r\n", fres);
    }
	 //Be a tidy kiwi - don't forget to close your file!
	f_close(&fil);
}

