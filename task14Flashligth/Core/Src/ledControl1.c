#include <ledControl1.h>

extern TIM_HandleTypeDef htim6;
void LedOff()
{
	HAL_TIM_Base_Stop_IT(&htim6);
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 0);

}

void LedOnFull()
{
	HAL_TIM_Base_Stop_IT(&htim6);
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 1);
}

void LedOnHalf()
{
	__HAL_TIM_SET_COUNTER(&htim6, 0);
    __HAL_TIM_SET_AUTORELOAD(&htim6, 100);
	HAL_TIM_Base_Start_IT(&htim6);
}

void LedOnBlinking()
{
	__HAL_TIM_SET_COUNTER(&htim6, 0);
    __HAL_TIM_SET_AUTORELOAD(&htim6, 1000);
    HAL_TIM_Base_Start_IT(&htim6);
}
