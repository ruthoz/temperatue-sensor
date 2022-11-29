/*
 * MyMain.cpp
 *
 *  Created on: Nov 27, 2022
 *      Author: student
 */

#include <MyMain.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h> //for va_list var arg functions
#include "SDCard.h"
#include "fatfs.h"


extern "C" void mainloop(){
	HAL_Delay(1000); //a short delay is important to let the SD card settle
	SDCard file("test.txt");
	file.readFile();

	SDCard file2("write.txt");
	char writeBuf[30];
	strncpy(writeBuf, "a new file is made!\r\n", 22);
	file2.writeToFile(writeBuf);
	file2.readFile();





}
