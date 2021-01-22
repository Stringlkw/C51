#include "general.h"

void delay_us(uchar us)
{
	uchar i;
	for (i = 1; i > 0; i--)
		for (us; us > 0; us--)
			;
}

void delay_ms(uint ms)
{
	uint i, j;
	for (j = 0; j < ms; j++)
		for (i = 0; i < 920; i++)
			;
}


void delay_100us(uint n)
{
    uchar i=112;

	while(n--)
	{
		while(i--);
	}
}

void delay1s(void)   //误差 -0.000000000099us
{
    unsigned char a,b,c;
    for(c=217;c>0;c--)
        for(b=171;b>0;b--)
            for(a=73;a>0;a--);
}

void delay1ms(void)   //误差 -0.018084490741us
{
    unsigned char a,b;
    for(b=21;b>0;b--)
        for(a=130;a>0;a--);
    _nop_();  //if Keil,require use intrins.h
}