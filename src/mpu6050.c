#include "mpu6050.h"
#include "i2c.h"
#include "lcd12864.h"

uchar dis_buf[4];  //显示数字(-511至512)的字符数组
uint dis_data; //变量

//**************************************
//向I2C设备写入一个字节数据
//**************************************
void writeMpu6050(uchar REG_Address, uchar REG_data)
{
	i2cStart();					//起始信号
	i2cWriteByte(SlaveAddress); //发送设备地址+写信号
	i2cWriteByte(REG_Address);	//内部寄存器地址，
	i2cWriteByte(REG_data);		//内部寄存器数据，
	i2cStop();					//发送停止信号
}
//**************************************
//从I2C设备读取一个字节数据
//**************************************
uchar readMpu6020(uchar REG_Address)
{
	uchar REG_data;
	i2cStart();						//起始信号
	i2cWriteByte(SlaveAddress);		//发送设备地址+写信号
	i2cWriteByte(REG_Address);		//发送存储单元地址，从0开始
	i2cStart();						//起始信号
	i2cWriteByte(SlaveAddress + 1); //发送设备地址+读信号
	REG_data = i2cReadByte();		//读出寄存器数据
	noI2cAck();					//接收应答信号
	i2cStop();						//停止信号
	return REG_data;
}
//**************************************
//初始化MPU6050
//**************************************
void mpu6050Init()
{
	writeMpu6050(PWR_MGMT_1, 0x00); //解除休眠状态
	writeMpu6050(SMPLRT_DIV, 0x07);
	writeMpu6050(CONFIG, 0x06);
	writeMpu6050(GYRO_CONFIG, 0x18);
	writeMpu6050(ACCEL_CONFIG, 0x01);
}
//**************************************
//合成数据
//**************************************
int getData(uchar REG_Address)
{
	char H, L;
	H = readMpu6020(REG_Address);
	L = readMpu6020(REG_Address + 1);
	return (H << 8) + L; //合成数据
}

//**************************************
//在12864上显示10位数据
//**************************************
void Display10BitData(uchar row, uchar column,int value)
{
	
	value /= 64; //转换为10位数据
	intToString(dis_buf, value);
	lcd12864SetPos(row, column);
	lcd12864WriteChar(dis_buf[0]);
	lcd12864WriteChar(dis_buf[1]);
	lcd12864WriteChar(dis_buf[2]);
	lcd12864WriteChar(dis_buf[3]);
	lcd12864WriteChar(' ');
}
