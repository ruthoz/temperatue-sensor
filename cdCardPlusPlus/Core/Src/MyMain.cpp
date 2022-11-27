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
	SDCard file("test.txt");
	file.openFile();
	file.printFile();
	SDCard file2("write.txt");
	BYTE readBuf[30];
	strncpy((char*)readBuf, "a new file is made!", 20);

	file2.writeToFile(readBuf);

}
