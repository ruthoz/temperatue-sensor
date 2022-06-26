
#include "stateflashligth.h"


FlashLightState currentState = STATE_OFF;
FlashLightState changhState()
{
  switch (currentState)
  {
    case STATE_OFF :
         currentState = STATE_ON_FULL;
         break;

    case STATE_ON_FULL :
          currentState = STATE_ON_HALF;
          break;

    case STATE_ON_HALF :
          currentState = STATE_ON_BLINKING;
          break;

    case STATE_ON_BLINKING :
          currentState = STATE_OFF;
          break;
  }
  ledcontrol();
  return 1;
}


