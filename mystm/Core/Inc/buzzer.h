

#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_

#include "main.h"

typedef enum StateBuzzer_
{
	MUSIC_ON,
	MUSIC_OFF,

}StateBuzzer;

typedef struct buzzer_
{
	StateBuzzer state;
	size_t sizeOfMusic;
	int currentNote;
	int counter;
	int maxCount;

}Buzzer;

void Buzzer_init(Buzzer* buzzer);
void Buzzer_playNote(Buzzer* buzzer);
void Buzzer_playNextNote();
void Buzzer_onTimerInterrupt(void* obj);
void Buzzer_on(Buzzer* buzzer);
void Buzzer_off(Buzzer* buzzer);
#endif /* INC_BUZZER_H_ */
