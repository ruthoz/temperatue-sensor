

#ifndef SRC_CLI_H_
#define SRC_CLI_H_

#include "main.h"
#include "led.h"
#include "commTask.h"

typedef void(*HandlerFunc)(void*);


void cliInit();

#endif /* SRC_CLI_H_ */
