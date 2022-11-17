
#pragma once

#define MAX_CLI 20

#include "CliCommand.h"


class CliContainer
{
	CliCommand* m_CliCommand[MAX_CLI];
public:
	CliContainer();
	~CliContainer();
private:
	int m_counter;
public:
	void add(CliCommand * pCliCommand);
	int getCounter(){
		return m_counter;
	}
	int Call (char* cmdname);
};



