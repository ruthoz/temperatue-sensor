#include <stdio.h>
#include <string.h>
#include <task44.h>
#include "cmsis_os.h"
#include "main.h"

#define USE_CRIT_SEC
//#define USE_MUTEX

extern osMutexId_t myMutex01Handle;
int GlobalFlag = 0;

void printTask(char* name)
{
	printf("Hi! My name is %s!\r\n\n",name);
}



/* USER CODE END Header_entry_Task01 */
void entry_Task(void *argument) {
	/* USER CODE BEGIN entry_Task01 */

	PrintTask *task = (PrintTask*) argument;
	/* Infinite loop */
	for (;;) {
#ifdef USE_MUTEX
	  osMutexAcquire(myMutex01Handle, osWaitForever);
#endif

#ifdef USE_CRIT_SEC
	  int flag = 1;
	  while (flag == 1) {
			taskENTER_CRITICAL();
			flag = GlobalFlag;
			if (flag == 0) {
				GlobalFlag = 1;
				taskEXIT_CRITICAL();
			}
	  }
#endif
				for (int i = 0; i < 3; i++) {
					printTask(task->name);
					osDelay(task->delay);
				}

#ifdef USE_CRIT_SEC
				GlobalFlag = 0;
#endif

#ifdef USE_MUTEX
	  osMutexRelease(myMutex01Handle);
#endif

		osDelay(1);
	}
	/* USER CODE END entry_Task01 */
}


