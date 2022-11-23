

#include "CliContainer.h"

CliContainer CliContainer;

CliContainer::CliContainer()
{
	_counter = 0;
	memset(_CliCommand, 0, sizeof(CliCommand*) * MAX_CLI);
}

CliContainer::~CliContainer()
{
	for (int i = 0; i < MAX_CLI; i++) {
		if (_CliCommand[i] != NULL) {
			delete _CliCommand[i];
		}
	}
}

void CliContainer::add(CliCommand* pCliCommand)
{
	if (_counter < MAX_CLI) {
		_CliCommand[_counter] = pCliCommand;
		_counter++;
	}
}

int CliContainer::getCounter(){
	return _counter;
}

int CliContainer::Call (char* cmdname, char* param ){
	for (int i = 0; i < _counter; i++){
		if(strcmp(cmdname, _CliCommand[i]->getName())==0){
			_CliCommand[i]->doCommand(param);
			return 1;
		}
	}
	return 0;
}






