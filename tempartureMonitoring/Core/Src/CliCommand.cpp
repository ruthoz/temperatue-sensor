#include <CliCommand.h>
#include "Led.h"
#include "main.h"
#include <stdio.h>
#include "CliContainer.h"
#include <cstring>


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

class LedBlinkCmd : public CliCommand {
	Led *_led;
public:
	LedBlinkCmd (const char * name, Led * led) : CliCommand(name), _led(led) {}
	void doCommand() override {
		_led->blink();
	}
};


void CliInit()
{
	//////////////////ledB//////////////////////////////
	CliContainer.add (new LedOnCmd("ledBlueOn", &ledB));
	CliContainer.add (new LedOffCmd("ledBlueOff", &ledB));
	CliContainer.add (new LedOffCmd("ledBlueBlink", &ledB));
}

