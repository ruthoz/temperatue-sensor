#ifndef INC_MAINTIMER_H_
#define INC_MAINTIMER_H_


#include "TimerTask.h"

#define MAX_TIMER_TASKS 10

class MainTimer {
private:
	TimerTask* _timerTasks[MAX_TIMER_TASKS];
	int _timerCount;

	int getTimerTaskIndex(TimerTask *pTimerTask) {
		for (int i = 0; i < _timerCount; i++) {
			if (_timerTasks[i] == pTimerTask) {
				return i;
			}

		}
		return -1;
	}
public:
	MainTimer() {
		_timerCount = 0;
	}
	~MainTimer() {}
	void addTimerTask(TimerTask *pTimerTask) {
		if (getTimerTaskIndex(pTimerTask) == -1) {
			_timerTasks[_timerCount] = pTimerTask;
			_timerCount++;
		}
	}

	void deleteTimerTask(TimerTask *pTimerTask) {
		int i = getTimerTaskIndex(pTimerTask);
		if (i != -1) {
			_timerCount--;
			if (i == _timerCount) {
				_timerTasks[i] = { 0 };
			} else {
				_timerTasks[i] = _timerTasks[_timerCount];
				_timerTasks[_timerCount] = { 0 };
			}
		}

	}
	void callTimerFunc() {
		for (int i = 0; i < _timerCount; i++) {
			_timerTasks[i]->timerFunc();
		}
	}

};

#endif /* INC_MAINTIMER_H_ */
