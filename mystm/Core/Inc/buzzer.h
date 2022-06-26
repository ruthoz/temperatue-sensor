

#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_

#include "main.h"

typedef enum StateBuzzer_
{
	MUSIC_ON,
	MUSIC_OFF,

}StateBuzzer;

typedef struct _buzzer
{
	StateBuzzer state;
	size_t sizeOfMusic;
	int currentNote;
	int counter;
	int Maxcount;

}BUZZER;

void buzzerInit(BUZZER* buzzer);
void playNote(BUZZER* buzzer);
void playNextNote();
void buzzerOnTimerInterrupt(BUZZER* buzzer);


#endif /* INC_BUZZER_H_ */
