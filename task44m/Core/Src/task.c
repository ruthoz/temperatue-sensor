#include "task.h"
#include <stdio.h>
#include <string.h>
#include "cmsis_os.h"
#include "main.h"

#define USE_MUTEX

extern osMutexId_t myMutex01Handle;

void printTask(char* name)
{
	printf("Hi! My name is %s!\r\n\n",name);
}



/* USER CODE END Header_entry_Task01 */
void entry_Task(void *argument)
{
  /* USER CODE BEGIN entry_Task01 */

	PrintTask * task = (PrintTask*)argument;

  /* Infinite loop */
  for(;;)
  {
	  osMutexAcquire(myMutex01Handle, osWaitForever);
	  for(int i = 0; i < 3; i++){
		  printTask(task->name);
		  osDelay(task->delay);
	  }
	  osMutexRelease(myMutex01Handle);
	  osDelay(1);
  }
  /* USER CODE END entry_Task01 */
}



