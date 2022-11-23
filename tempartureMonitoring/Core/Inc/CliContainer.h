
#pragma once

#define MAX_CLI 20

#include "main.h"
#include "CliCommand.h"
#include <stdio.h>
#include <cstring>
#include <stdlib.h>

class CliContainer
{
	CliCommand* _CliCommand[MAX_CLI];
public:
	CliContainer();
	~CliContainer();
private:
	int _counter;
public:
	void add(CliCommand * pCliCommand);
	int getCounter();
	int Call (char* cmdname, char* param);
};



