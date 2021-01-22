#include "time.h"
/*计时时间*/
//计时50ms：设置为3cB0;
//计时10ms：设置为D8F0;
//计时2ms：设置为F830;
//计时1ms：设置为FC18;
//计时500us：设置为FE0C；
//计时50us：设置为FFCE；
//计时10us：设置为FFF6；

/*------------------------------------------------
                    定时器初始化子程序
------------------------------------------------*/
void timer0Init()
{
    TMOD |= 0x02;
    TH0 = 156; //计时50ms
    TL0 = 156;

    EA = 1;
    ET0 = 1;
    TR0 = 1;
}

void timer1Init()
{
    TMOD |= 0x10;
    TH1 = 0x3C;
    TL1 = 0xB0;

    EA = 1;
    ET1 = 1;
    TR1 = 1;
}

void timerInit()
{
    TMOD = 0X11;
    TH0 = 0x3C; //计时50ms
    TL0 = 0xB0;
    TH1 = 0x3C;
    TL1 = 0xB0;
    TR0 = 1;
    TR1 = 0;
    ET0 = ET1 = 1;
    EA = 1;
}

void externalInit()
{
    EA = 1;
    EX0 = 1;
    IT0 = 1;
}

/*------------------------------------------------
                 定时器中断子程序
------------------------------------------------*/
/*定时器0*/
//void Timer0Interrupt() interrupt 1
//{
//    TH0 = 0x3C;
//    TL0 = 0xB0;
//    //TODO
//}

/*定时器1*/
//void Timer1Interrupt(void) interrupt 3
//{
//    TH1 = 0x3C;
//    TL1 = 0xB0;
//    //TODO
//}