#include <CliCommand.h>
#include "Led.h"
#include "main.h"
#include <stdio.h>
#include "CliContainer.h"
#include <cstring>

extern Led ledR;
extern Led ledB;
extern CliContainer CliContainer;

class LedOnCmd : public CliCommand {
	Led *_led;
public:
	LedOnCmd (const char * name, Led * led) : CliCommand(name), _led(led) {}
	void doCommand() override {
		_led->on();
	}
};

class LedOffCmd : public CliCommand {
	Led *_led;
public:
	LedOffCmd (const char * name, Led * led) : CliCommand(name), _led(led) {}
	void doCommand() override {
		_led->off();
	}
};


void CliInit()
{
	//////////////////ledR//////////////////////////////
	CliContainer.add (new LedOnCmd("ledRedOn", &ledR));
	CliContainer.add (new LedOffCmd("ledRedOff", &ledB));

	//////////////////ledB//////////////////////////////
	CliContainer.add (new LedOnCmd("ledBlueOn", &ledR));
	CliContainer.add (new LedOffCmd("ledBlueOff", &ledB));
}

