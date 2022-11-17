/*
 * TimerTask.h
 *
 *  Created on: 17 Nov 2022
 *      Author: student
 */

#ifndef INC_TIMERTASK_H_
#define INC_TIMERTASK_H_

class TimerTask {

public:
	TimerTask(){}

	virtual void timerFunc() = 0;
	virtual ~TimerTask(){}
};



#endif /* INC_TIMERTASK_H_ */
