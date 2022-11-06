#include "mymain.h"

#ifndef SRC_ICOMMAND_H_
#define SRC_ICOMMAND_H_

#define MAX_NAME_LEN 20

class CliCommand {
private:
	const char* _name(MAX_NAME_LEN);
public:
	CliCommand(char * name){
		strcpy(_name,name)
	}
	void CliInit();
	virtual void doCommand() = 0;
	virtual ~CliCommand(){}
	const char* getName()const{
		return _name
	}
};

#endif /* SRC_ICOMMAND_H_ */
