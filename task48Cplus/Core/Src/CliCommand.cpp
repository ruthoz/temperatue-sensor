#include <CliCommand.h>
#include "Led.h"
#include "main.h"
#include <stdio.h>
#include "CliContainer.h"

extern Led ledR;
extern CliContainer *pCli;



class LedOnCmd : public CliCommand {
	Led *_led;

public:
	LedOnCmd (const char* name){
		_led= led;
		_comadName = {"Led"};
		_stateComand =  {"on"};
	}
	void doCommand(){
		_led->on();
	}
};

class LedOffCmd : public CliCommand {
private:
	Led *_led;
	const char* _comadName;
	const char* _stateComand;
public:
	LedOffCmd (Led *led){
		_led= led;
		_comadName = {"Led"};
		_stateComand =  {"off"};
	}
	void doCommand(){
		_led->off();
	}
};

class LedBlinkCmd : public CliCommand {
private:
	Led *_led;
	const char* _comadName;
	const char* _stateComand;
public:
	LedBlinkCmd (Led *led){
		_led= led;
		_comadName = {"Led"};
		_stateComand =  {"blink"};
	}
	void doCommand(){
		_led->blink();
	}
};


void CliCommand::CliInit()
{
	//////////////////ledR//////////////////////////////
	pCli->add (new LedOnCmd(&ledR));

}
