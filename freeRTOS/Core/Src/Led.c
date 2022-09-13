/*
 * Led.c
 *
 *  Created on: Sep 13, 2022
 *      Author: student
 */

#include "Led.h"
#include "cmsis_os.h"
static int delay = 500;

void Entry_blinkTask(void *argument)
{
  /* USER CODE BEGIN Entry_blinkTask */
  /* Infinite loop */
  for(;;)
  {
	  HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	  osDelay(delay);

  }
  /* USER CODE END Entry_blinkTask */
}

