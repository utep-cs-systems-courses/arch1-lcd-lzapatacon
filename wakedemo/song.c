#include <msp430.h>
#include "buzzer.h"
#include "song.h"
void song()
{
  
  buzzer_init();
  switch(s_state)
    {
    case 0: period = 3000; s_state = 1; break;
    case 1: period = 1400; s_state = 2; break;
    case 2: period = 1000; s_state = 3; break;
    case 3: period = 6000; s_state = 0; break;
    }
  buzzer_set_period(period);
}
