#ifndef _BEEP_H_
#define _BEEP_H_
#include "general.h"
sbit beep = P2^3;


void beepRing(uint frequency);   //��һ��Ƶ����
void beepStop();



#endif