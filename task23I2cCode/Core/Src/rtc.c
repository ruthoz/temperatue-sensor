#include "rtc.h"

extern I2C_HandleTypeDef hi2c1;
extern int flagSystemLoock;

void setCode(uint32_t MainCode){
	HAL_I2C_Mem_Write(&hi2c1, 208, 8, 1, (uint8_t *)&MainCode, sizeof(MainCode), 0xff);
}

uint32_t code;
int getCode(uint32_t pass){
	HAL_I2C_Mem_Read(&hi2c1, 208, 8, 1, (uint8_t *)&code, sizeof(code), 0xff);
	if (pass == code){
		return 1;
	}
	return 0;
}

int counterTimeEror = 0;
void rtcOnTimerInterrupt(){
	if (flagSystemLoock == 1){
		if (counterTimeEror > 10){
			counterTimeEror = 0;
			flagSystemLoock = 0;
			HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, 0);
		}
		else{
			counterTimeEror++;
		}
	}
}


void setClock()
{
	uint8_t setDateBuff[]={0,0,0,1,1,1,0};
	HAL_I2C_Mem_Write(&hi2c1, 208, 0, 1, setDateBuff, 7, 0xff);
}


uint8_t timeInSec(){
 uint8_t readBuff[7];
 uint8_t timeOfSec= 0;
  HAL_I2C_Mem_Read(&hi2c1, 208, 0, 1, readBuff, 7, 0xff);

  timeOfSec = ((readBuff[0] & 15) + (readBuff[0] >> 4)*10 )
            + ((readBuff[1] & 15) + (readBuff[1] >>4)*10 ) * 60
            + ((readBuff[2] & 15) + (readBuff[2] >>4)*10 ) * 60 * 60 ;


  return timeOfSec;
}

void lockSystem5min(){
	uint8_t currentime;
	currentime = timeInSec() + 300;
	HAL_I2C_Mem_Write(&hi2c1, 208, 20, 1, (uint8_t *)&currentime, sizeof(currentime), 0xff);
}

void lockOrOpen(){
	uint8_t currentime;
	HAL_I2C_Mem_Read(&hi2c1, 208, 20, 1, (uint8_t *)&currentime, sizeof(currentime), 0xff);
	if(timeInSec() <= currentime){
		flagSystemLoock = 1;
	}
	else{
	   flagSystemLoock = 0;
	   HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, 0);
	}

}


