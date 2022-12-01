/*
 * File.h
 *
 *  Created on: Nov 29, 2022
 *      Author: student
 */

#ifndef INC_FILE_H_
#define INC_FILE_H_

#include "main.h"
#include "fatfs.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h> //for va_list var arg functions


class File {
private:
	//some variables for FatFs
	FATFS FatFs; 	//Fatfs handle
	FIL fil; 		//File handle
	FRESULT fres; //Result after operations
	char _nameFile [20];
	DWORD free_clusters, free_sectors, total_sectors;

public:
	File(const char* nameFile);
	~File(){};

	void initSDCard();
	void read();
	void write(const char* writeBuf);
	void clear();
};

#endif /* INC_FILE_H_ */
