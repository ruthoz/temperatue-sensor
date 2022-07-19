#include "CLI.h"
#include "led.h"
#include "commTask.h"

extern LED ledR;


void cliInit(){
	RegisterCommand("led", "on", ledOn, &ledR);
	RegisterCommand("led", "off", ledOff, &ledR);
}

void cmdLed(void* obj){

}

