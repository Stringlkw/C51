#ifndef _I2C_H_
#define _I2C_H_

#include "general.h"

sbit SDA = P1 ^ 0;
sbit SCL = P1 ^ 1;

#define ADDWR 0x90 //写数据地址
#define ADDRD 0x91 //读数据地址


void i2cStart();
void i2cStop();
void i2cAck();
void noI2cAck();
void i2cWriteByte(uchar dat);
uchar i2cReadByte();
uchar readADC(uchar channel);
void writeAt24c02(uchar address, uchar dat);
uchar readAt24c02(uchar address);

#endif