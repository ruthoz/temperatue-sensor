

#include "CliContainer.h"
#include <stdio.h>
#include <cstring>
#include "Led.h"
#include "Communication.h"
#include <stdlib.h>



CliContainer::CliContainer()
{
	m_counter = 0;
	memset(m_CliCommand, 0, sizeof(CliCommand*) * MAX_CLI);
}

CliContainer::~CliContainer()
{
	for (int i = 0; i < MAX_CLI; i++) {
		if (m_CliCommand[i] != NULL) {
			delete m_CliCommand[i];
		}
	}
}

void CliContainer::add(CliCommand* pCliCommand)
{
	if (m_counter < MAX_CLI) {
		m_CliCommand[m_counter] = pCliCommand;
		m_counter++;
	}
}

int CliContainer::Call (char* cmdname){
	for (int i = 0; i < m_counter; i++){
		if(strcmp(cmdname, m_CliCommand[i]->getName())==0){
			m_CliCommand[i]->doCommand();
			return 1;
		}
	}
	return 0;
}






