/*
 * HandleCommand.c
 *
 *  Created on: Sep 13, 2022
 *      Author: student
 */

#include <HandleCommand.h>
#include "Led.h"
#include <stdio.h>
#include <string.h>

extern Led ledR;
extern Led ledB;
extern UART_HandleTypeDef huart2;
#define MAX_BUFFER_LENGTH 100
static uint8_t cmdbuffer[MAX_BUFFER_LENGTH];
static int cmdcount = 0;
static int cmdprint = 0;


////////////////////////////////////////////////////////////////////////
int _write(int fd, char* ptr, int len)
{
	HAL_UART_Transmit(&huart2, (uint8_t*)ptr, len, HAL_MAX_DELAY);
	return len;
}
//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
int Communication_commTask()
{
	uint8_t ch;

	HAL_StatusTypeDef Status = HAL_UART_Receive(&huart2, &ch, 1, 10);
	if (Status != HAL_OK)
	{
		if ((huart2.Instance->ISR & USART_ISR_ORE) != 0)
		{
			__HAL_UART_CLEAR_OREFLAG(&huart2);
		}

		// here we have a time to print the command
		while (cmdprint < cmdcount)
		{
			HAL_UART_Transmit(&huart2, &cmdbuffer[cmdprint++], 1, 0xFFFF);
		}

		return 0;
	}

	if (ch != '\r' && ch != '\n')
	{
		//HAL_UART_Transmit(&huart2, &ch, 1, 0xFFFF);

		if (cmdcount >= MAX_BUFFER_LENGTH)
		{
			cmdcount = 0;
			cmdprint = 0;
		}

		cmdbuffer[cmdcount++] = ch;
		return 0;
	}

	// here we have a time to print the command
	while (cmdprint < cmdcount)
	{
		HAL_UART_Transmit(&huart2, &cmdbuffer[cmdprint++], 1, 0xFFFF);
	}

	HAL_UART_Transmit(&huart2, (uint8_t*)"\r\n", 2, 0xFFFF);

	cmdbuffer[cmdcount] = 0;
	cmdcount = 0;
	cmdprint = 0;
	return 1;
}


void Communication_handleCommand()
{
	char cmd[20];
	char param [20];

   int params = sscanf((const char*)cmdbuffer, "%s %s", cmd, param );
   if (params == 0){
	   return;
   }

   if (strcmp(cmd, "redBlink") == 0){
	   setBlinkLed(&ledR,param);
   }
   if (strcmp(cmd, "blueBlink") == 0){
	   setBlinkLed(&ledB , param);
   }
   else{
   	  printf("Invalid command\r\n");
   }
}

void Entry_uartTask(void *argument)
{
  /* USER CODE BEGIN Entry_uartTask */
  /* Infinite loop */
  for(;;)
  {
	  if (Communication_commTask()){
		  Communication_handleCommand();
	  }

  }
  /* USER CODE END Entry_uartTask */
}

