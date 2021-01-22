
#include "beep.h"
void beepRing(uint frequency)
{
    beep = 1;
    delay_ms(frequency);
    beep = 0;
    delay_ms(frequency);
}

void beepStop()
{
    beep = 1;
}