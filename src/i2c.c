#include "i2c.h"
bit ack; //应答标志位
//开始
void i2cStart()
{
	SDA = 1;
	delay_us(1);
	SCL = 1;
	delay_us(5);
	SDA = 0;
	delay_us(5);
	SCL = 0;
	delay_us(2);
}

//停止
void i2cStop()
{
	SDA = 0;
	delay_us(1);
	SCL = 1;
	delay_us(5);
	SDA = 1;
	delay_us(5);
}

bit Check_Ack()
{
	uchar errtime = 250;
	delay_us(1);
	SCL = 1;
	delay_us(1);
	CY = SDA;
	while (CY)
	{
		errtime--;
		CY = SDA;
		if (!errtime)
		{
			i2cStop();
			return 1;
		}
	}
	delay_us(1);
	SCL = 0;
	return 0;
}
//应答
void i2cAck()
{
	SDA = 0;
	delay_us(3);
	SCL = 1;
	delay_us(5);
	SCL = 0;
	delay_us(2);
}

//非应答
void noI2cAck()
{
	SDA = 1;
	delay_us(3);
	SCL = 1;
	delay_us(5);
	SCL = 0;
	delay_us(2);
}

//写入一个字节到i2c
void i2cWriteByte(uchar dat)
{
	uchar i;
	for (i = 0; i < 8; i++)
	{
		if ((dat << i) & 0x80)
		{
			SDA = 1;
		}
		else
		{
			SDA = 0;
		}
		delay_us(1);
		SCL = 1;
		delay_us(5);
		SCL = 0;
	}
	delay_us(2);
	SDA = 1;
	delay_us(2);
	SCL = 1;
	delay_us(3);
	if (SDA == 1)
	{
		ack = 0;
	}
	else
	{
		ack = 1;
	}
	SCL = 0;
	delay_us(2);
}

//接收一个字节的数据
uchar i2cReadByte()
{
	uchar retc;
	uchar i;
	retc = 0;
	SDA = 1;
	for (i = 0; i < 8; i++)
	{
		delay_us(1);
		SCL = 0;
		delay_us(5);
		SCL = 1;
		delay_us(2);
		retc = retc << 1;
		if (SDA == 1)
		{
			retc = retc + 1;
		}
		delay_us(2);
	}
	SCL = 0;
	delay_us(2);
	return retc;
}

uchar readADC(uchar channel)
{
	uchar val;
	i2cStart();
	i2cWriteByte(ADDWR);
	if (ack == 0)
	{
		return 0;
	}
	i2cWriteByte(0x40 | channel);
	if (ack == 0)
	{
		return 0;
	}
	i2cStart();
	i2cWriteByte(ADDWR + 1);
	if (ack == 0)
	{
		return 0;
	}
	val = i2cReadByte();
	noI2cAck();
	i2cStop();
	return val;
}

void writeAt24c02(uchar address, uchar dat)
{
	i2cStart();
	i2cWriteByte(0xa0);

	i2cWriteByte(address);

	i2cWriteByte(dat);

	i2cStop();
}

uchar readAt24c02(uchar address)
{
	uchar dat;
	i2cStart();
	i2cWriteByte(0xa0);
	i2cWriteByte(address);
	i2cStart();
	i2cWriteByte(0xa1);
	dat = i2cReadByte();
	noI2cAck();
	i2cStop();
	return dat;
}
