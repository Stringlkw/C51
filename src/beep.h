#ifndef _BEEP_H_
#define _BEEP_H_
#include "general.h"
sbit beep = P2^3;


void beepRing(uint frequency);   //按一定频率响
void beepStop();



#endif