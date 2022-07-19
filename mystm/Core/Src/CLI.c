#include <Buzzer.h>
#include <Communication.h>
#include <Led.h>
#include "CLI.h"
#include <stdlib.h>

extern Led ledR;
extern Led ledB;
extern Buzzer buzzer;

void Cli_cmdLedOn(void* obj, char* param){
	Led *led = (Led*)obj;
	Led_on(led);
}

void Cli_cmdLedOff(void* obj, char* param){
	Led *led = (Led*)obj;
	Led_off(led);
}

void Cli_cmdLedBlink(void* obj, char* param){
	Led *led = (Led*)obj;
	int period = atoi (param);
	Led_blink(led, period);
}

void Cli_cmdLedBrightness(void* obj, char* param){
	int period = atoi (param);
	Led_setBrightness(period);
}


void Cli_cmdBuzzerOn(void* obj, char* param){
	Buzzer *buzzer = (Buzzer*)obj;
	Buzzer_on(buzzer);
}

void Cli_cmdBuzzerOff(void* obj, char* param){
	Buzzer *buzzer = (Buzzer*)obj;
	Buzzer_off(buzzer);
}


void Cli_init(){
	//////////////////ledR//////////////////////////////
	Communication_registerCommand("ledR", "on", Cli_cmdLedOn, &ledR);
	Communication_registerCommand("ledR", "off", Cli_cmdLedOff, &ledR);
	Communication_registerCommand("ledR", "blink", Cli_cmdLedBlink, &ledR);

	//////////////////ledB//////////////////////////////
	Communication_registerCommand("ledB", "on", Cli_cmdLedOn, &ledB);
    Communication_registerCommand("ledB", "off", Cli_cmdLedOff, &ledB);
    Communication_registerCommand("ledB", "blink", Cli_cmdLedBlink, &ledB);

    //////////////////ledbright////////////////////////
    Communication_registerCommand("led", "bright", Cli_cmdLedOn, &ledB);

    /////////////////buzzer//////////////////////////////
    Communication_registerCommand("buzzer", "on", Cli_cmdBuzzerOn, &buzzer);
    Communication_registerCommand("buzzer", "off", Cli_cmdBuzzerOff, &buzzer);
}



