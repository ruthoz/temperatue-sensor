/*
 * SDCard.h
 *
 *  Created on: Nov 27, 2022
 *      Author: student
 */

#ifndef INC_SDCARD_H_
#define INC_SDCARD_H_
#include "main.h"
#include "fatfs.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h> //for va_list var arg functions



class SDCard {
private:
	//some variables for FatFs
	FATFS FatFs; 	//Fatfs handle
	FIL fil; 		//File handle
	FRESULT fres; //Result after operations
	char _nameFile [20];
	DWORD free_clusters, free_sectors, total_sectors;

public:
	SDCard(const char* nameFile);
	~SDCard();
	void myprintf(const char *fmt, ...);
	void readFile();
	void writeToFile(const char* writeBuf);

};

#endif /* INC_SDCARD_H_ */
