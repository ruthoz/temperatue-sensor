#include "main.h"
#include "Linkedlist.h"
#include "stdio.h"
#include "cmsis_os.h"
#include <stdlib.h>
#include <string.h>

extern LinkedList list1;

void LogOutPut(Type type, char* buffer){
	LinkedList_addBegin(&list1, type, buffer);
}

void Entry_Task1(void *argument)
{
  /* USER CODE BEGIN 5 */
	char buffer[80];
  /* Infinite loop */
  for(;;)
  {
	osDelay(500);
	sprintf(buffer, "TASK 1 - %ld" , HAL_GetTick());
	LogOutPut(LOG_DEBUG, buffer);
  }
  /* USER CODE END 5 */
}


void Entry_Task2(void *argument)
{
  /* USER CODE BEGIN Entry_Task2 */
	char buffer[80];
  /* Infinite loop */
  for(;;)
  {
	  osDelay(300);
	  sprintf(buffer, "TASK 2 - %ld" , HAL_GetTick());
	  LogOutPut(LOG_EROR, buffer);
  }
  /* USER CODE END Entry_Task2 */
}


void Entry_LOGGER(void *argument)
{
  /* USER CODE BEGIN Entry_LOGGER */
  /* Infinite loop */
  for(;;)
  {
	LinkedList_printAndDelete(&list1);
    osDelay(1);
  }
  /* USER CODE END Entry_LOGGER */
}


