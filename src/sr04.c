#include "SR04.h"
#include "lcd12864.h"


//声明全局变量
bit FLAG_SR04 = 0;
//引脚定义
sbit Echo = P2 ^ 6;
sbit Trig = P2 ^ 7;

uint measuretime = 0;
unsigned long S = 0;

//启动SR04模块
void sr04Start()
{
	Trig = 1; //20us的高电平
	delay_us(20);
	Trig = 0;
	while (!Echo)
		;	 //当Echo为零时等待
	TR1 = 1; //开启计时
	while (Echo && (!FLAG_SR04))
		; //当Echo为1计数并等待
	TR1 = 0;
}

//计算距离
unsigned long sr04Conut()
{
	measuretime = TH1 * 256 + TL1;
	TH1 = 0;
	TL1 = 0;
	return S = (measuretime * 1.7) / 100; //算出来是CM	  11。0592M晶振
}

void sr04Display(uchar row, uchar column, unsigned long s)
{
	if ((s >= 700) || (FLAG_SR04 == 1)) //超出测量
	{
		FLAG_SR04 = 0;
		lcd12864SetPos(row, column);
		lcd12864WriteNum(13);
		lcd12864WriteNum(12);
		lcd12864WriteNum(13);
		lcd12864WriteNum(13);
	}
	else
	{
		lcd12864SetPos(row, column);
		lcd12864WriteChar(s % 1000 / 100 + '0');
		lcd12864WriteNum(12);
		lcd12864WriteChar(s % 1000 % 100 / 10 + '0');
		lcd12864WriteChar(s % 1000 % 10 % 10 + '0');
	}
}