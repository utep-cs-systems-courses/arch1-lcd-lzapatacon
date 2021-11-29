#include <msp430.h>
#include "buzzer.h"
#include "song.h"

void song()
{
  switch(s_state)
    {
    case 0: period = 1000; s_state = 1; break;
    }
}
