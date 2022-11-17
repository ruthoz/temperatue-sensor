
#include "mymain.h"
#include <cstring>

#ifndef SRC_ICOMMAND_H_
#define SRC_ICOMMAND_H_

#define MAX_NAME_LEN 20



class CliCommand {
private:
	char _name[MAX_NAME_LEN];
public:
	CliCommand(){}
	CliCommand(const char* name){
		strcpy(_name, name);
	}
	virtual void doCommand() = 0;
	virtual ~CliCommand(){}
	const char* getName ()const {
		return _name;
	}
};

void CliInit();

#endif /* SRC_ICOMMAND_H_ */
