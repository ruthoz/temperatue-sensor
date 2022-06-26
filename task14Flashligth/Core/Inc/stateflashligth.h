/*
 * stateflashligth.h
 *
 *  Created on: Jun 9, 2022
 *      Author: student
 */

#ifndef INC_STATEFLASHLIGTH_H_
#define INC_STATEFLASHLIGTH_H_


typedef enum FlashLightState_
{
	STATE_OFF,
	STATE_ON_FULL,
	STATE_ON_HALF,
	STATE_ON_BLINKING,
}FlashLightState;

extern FlashLightState currentState;
FlashLightState changhState();
void ledcontrol();

#endif /* INC_STATEFLASHLIGTH_H_ */
