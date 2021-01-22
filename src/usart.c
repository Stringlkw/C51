#include "usart.h"

void usartInit()
{
    SCON = 0x50;
    TMOD = 0x20; //设置定时器 1 为模式 2
    PCON = 0x00;
    TH1 = 0xfd; //装初值设定波特率
    TL1 = 0xfd;
    TR1 = 1; //启动定时器
    EA = 1;  //开总中断
    ES = 1;  //开串中断
}

void uart2Init() //COM2初始化///
{
    S2CON = 0x50;
    BRT = 0XFD;
    AUXR = 0x11;
    IE2 = 0x01;
    EA = 1;
}

void usartWriteByte(uchar dat)
{
    ES = 0;
    SBUF = dat;
    while (TI == 0)
        ;
    TI = 0;
    ES = 1;
}

void usartWriteString(uchar *str)
{
    while (*str != '\0')
    {
        usartWriteByte(*str++);
    }
}

void UART_Init(void)
{
	AUXR &= 0xF7;		//波特率不倍速
	S2CON = 0x50;		//8位数据,可变波特率
	AUXR &= 0xFB;		//独立波特率发生器时钟为Fosc/12,即12T
	BRT = 0xFD;			//设定独立波特率发生器重装值
	AUXR |= 0x10;		//启动独立波特率发生器
	ES = 1;				//也可以用IE2 |= 0X01，不过下面读取也需要全部用IE2
	EA = 1;
}

void SendChar(uchar DAT)
{
	ES = 0;			//IE2 &= 0Xfe;
	S2BUF = DAT;
	while((S2CON & 0X02) == 0);
	S2CON &= ~0X02;
	ES = 1;			//IE2 |= 0X01;
}
