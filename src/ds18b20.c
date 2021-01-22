#include "ds18B20.h"


uchar a,b;
/*******************************************DS18B20*************************************************/
/**
  *输入：无
  *输出：0/1
  */
void Display(uint Tem)
{
	uchar count;
	lcd12864SetPos(2,3);
	if((Tem >> 12) & 0x0001)
	{
		lcd12864WriteChar('-');
		Tem = ~Tem + 1;
	}
	else
	{
		lcd12864WriteChar('+');
	}
	Tem = Tem * 0.625;
	
	count = Tem /1000;
	if(count != 0)
	{
		lcd12864WriteChar(count+48);
	}
	count = Tem /100 %10;
	lcd12864WriteChar(count+48);
	count = Tem / 10 % 10;
	lcd12864WriteChar(count+48);
	lcd12864WriteChar('.');
	count = Tem % 10;
	lcd12864WriteChar(count+48);
	lcd12864WriteChar(' ');
}
uchar DS_Init()
{
	uchar flag = 0;
	DS_data = 0;
    /*500us*/
	for(b=251;b>0;b--)
        for(a=4;a>0;a--);
    _nop_();
	DS_data = 1; 		//释放总线
    /*15us*/
	for(b=1;b>0;b--)
        for(a=38;a>0;a--);
    _nop_();

	while(DS_data == 1);
	while(DS_data == 0)
	{
		flag = 1;	
	}
	DS_data = 1;
	return flag;			
}

void DS_Write(uchar cmd)
{
	uchar i;
	for(i = 0; i < 8; i++)
	{
		DS_data = 0;
	   	/*2us*/
		for(a=4;a>0;a--);
		DS_data = ((cmd >> i) & 0x01);
	    /*60us*/
		for(a=164;a>0;a--);
    	_nop_();
		DS_data = 1; 
	}
}

uchar DS_Read()
{
	uchar dat = 0x00;
	uchar i,num;
	for(i = 0; i < 8;i++)
	{
		DS_data = 0;
	   	/*2us*/
		for(a=4;a>0;a--);
		DS_data = 1;
		/*6us*/
		for(a=15;a>0;a--);
		num = DS_data;
		dat	= (dat | (num << i));
	    /*60us*/
		for(a=164;a>0;a--);
    	_nop_();
//		DS_data = 1;
	}
	return dat;
}

uint get_temp()
{
	uchar flag;
	uint temperature = 0x0000;
	uchar LSB,MSB;
	flag = DS_Init();
	delay1ms();
	if(flag)
	{
		DS_Write(0xcc);
		DS_Write(0x44);
		delay1s();
		flag = DS_Init();
		delay1ms();
		if(flag)
		{
			DS_Write(0xcc);
			DS_Write(0xBE);
			LSB = DS_Read();
			MSB = DS_Read();
			temperature = MSB;
			temperature <<= 8;
			temperature |= LSB;
			return temperature;
		}
		else
		{
			return 00;
		}
	}
	else
	{
	 	return 00;
	}		
}

void write_storage(uchar MAX,uchar MIN)
{
	uchar flag;
	flag = DS_Init();
	delay1ms();
	if(flag)
	{
		DS_Write(0xcc);
		DS_Write(0x4E);
		DS_Write(MAX);
		DS_Write(MIN);
	}
	flag = DS_Init();
	delay1ms();
	if(flag)
	{
		DS_Write(0xcc);
		DS_Write(0x48);
	}	
}
/***************************************************************************************************/