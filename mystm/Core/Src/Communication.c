#include <Communication.h>
#include <stdio.h>
#include <string.h>


extern UART_HandleTypeDef huart2;
extern TIM_HandleTypeDef htim6;
extern I2C_HandleTypeDef hi2c1;


#define MAX_BUFFER_LENGTH 100
static uint8_t cmdbuffer[MAX_BUFFER_LENGTH];
static Comand comands[20];
static int counterComand = 0;
static int cmdcount = 0;
static int cmdprint = 0;

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
	char state[20];
	char param [20];

   int params = sscanf((const char*)cmdbuffer, "%s %s %s", cmd, state, param );
   if (params == 0){
	   return;
  }

   for(int i=0; i<counterComand ; i++){
	   if(strcmp(cmd, comands[i].comandName) == 0){
		   if(strcmp(state, comands[i].stateComand) == 0){
			   comands[i].comandPointer(comands[i].object, param);
			   return;
		   }
	   }
   }
   printf("Invalid command\r\n");

}


void Communication_registerCommand(char* comandName, char* stateComand, HandlerFunc comandPointer, void* object){
	comands[counterComand].comandName = comandName;
	comands[counterComand].stateComand = stateComand;
	comands[counterComand].comandPointer = comandPointer;
	comands[counterComand].object = object;
	counterComand++;

}
