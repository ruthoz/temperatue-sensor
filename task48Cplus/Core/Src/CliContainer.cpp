/*
 * container.cpp
 *
 *  Created on: 6 Nov 2022
 *      Author: student
 */

#include "CliContainer.h"
#include <stdio.h>
#include <cstring>
#include "Led.h"
#include "Communication.h"
#include <stdlib.h>



CliContainer::CliContainer()
{
	m_counter = 0;
	memset(m_CliCommand, NULL, sizeof(CliCommand)* MAX_CLI);
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





