#include "ds1302.h"

#define Delay1us() _nop_()

//---DS1302写入和读取时分秒的地址命令---//
//---秒分时日月周年 最低位读写位;-------//
uchar code READ_RTC_ADDR[7] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d};
uchar code WRITE_RTC_ADDR[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};
//---存储顺序是秒分时日月周年,存储格式是用BCD码---//
uchar TIME[7] = {0x00, 0x30, 0x12, 0x01, 0x01, 0x02, 0x13};

void Ds1302Write(uchar addr, uchar dat);
uchar Ds1302Read(uchar addr);

void ds1302Init()
{
	uchar n;
	Ds1302Write(0x8E, 0X00); //禁止写保护，就是关闭写保护功能

	for (n = 0; n < 7; n++) //写入7个字节的时钟信号：分秒时日月周年
	{
		Ds1302Write(WRITE_RTC_ADDR[n], TIME[n]);
	}

	Ds1302Write(0x8E, 0x80); //打开写保护功能
}

#define _BCD2HEX(BCD) BCD & 0xf0 * 10 + BCD & 0x0f
#define _HEX2BCD(HEX) HEX % 10 + (HEX / 10 % 10) << 4;

void readTime(Ds1302_TypeDef *time)
{
	uchar tmp;
	/*读取秒*/
	tmp = Ds1302Read(READ_RTC_ADDR[0]);
	time->sec = tmp;
	/*读取分*/
	tmp = Ds1302Read(READ_RTC_ADDR[1]);
	time->min = tmp;
	/*读取时*/
	tmp = Ds1302Read(READ_RTC_ADDR[2]);

	if (tmp & 0x80)
	{
		time->mode = (tmp & 0x20) ? PM : AM;
		time->hour = tmp & 0x10 * 10 + tmp & 0x0f;
	}
	else
	{
		time->mode = H24;
		time->hour = tmp;
	}

	time->hour = tmp;
	/*读取日*/
	tmp = Ds1302Read(READ_RTC_ADDR[3]);
	time->date = tmp;
	/*读取月*/
	tmp = Ds1302Read(READ_RTC_ADDR[4]);
	time->mon = tmp;
	/*读取周*/
	tmp = Ds1302Read(READ_RTC_ADDR[5]);
	time->day = tmp;
	/*读取年*/
	tmp = Ds1302Read(READ_RTC_ADDR[6]);
	time->year = tmp;
}
void writeTime(Ds1302_TypeDef *time)
{
	uchar tmp;
	/*写入秒*/
	tmp = time->sec;
	time->sec = tmp;
	Ds1302Write(WRITE_RTC_ADDR[0], tmp);
	/*写入分*/
	tmp = time->min;
	Ds1302Write(WRITE_RTC_ADDR[1], tmp);
	/*写入时*/
	tmp = time->hour;
	if (time->mode != H24)
		tmp |= (time->mode = AM) ? 0 : 0x20;
	Ds1302Write(WRITE_RTC_ADDR[2], tmp);
	/*写入日*/
	tmp = time->date;
	Ds1302Write(WRITE_RTC_ADDR[3], tmp);
	/*写入月*/
	tmp = time->mon;
	Ds1302Write(WRITE_RTC_ADDR[4], tmp);
	/*写入周*/
	tmp = time->day;
	Ds1302Write(WRITE_RTC_ADDR[5], tmp);
	/*写入年*/
	tmp = time->year;
	tmp = _HEX2BCD(tmp);
	Ds1302Write(WRITE_RTC_ADDR[6], tmp);
}
void Ds1302Write(uchar addr, uchar dat)
{
	uchar n;
	CE = 0;
	Delay1us();

	SCLK = 0; //先将SCLK置低电平。
	Delay1us();
	CE = 1; //然后将CE(CE)置高电平。
	Delay1us();

	for (n = 0; n < 8; n++) //开始传送八位地址命令
	{
		DSIO = addr & 0x01; //数据从低位开始传送
		addr >>= 1;
		SCLK = 1; //数据在上升沿时，DS1302读取数据
		Delay1us();
		SCLK = 0;
		Delay1us();
	}

	for (n = 0; n < 8; n++) //写入8位数据
	{
		DSIO = dat & 0x01;
		dat >>= 1;
		SCLK = 1; //数据在上升沿时，DS1302读取数据
		Delay1us();
		SCLK = 0;
		Delay1us();
	}

	CE = 0; //传送数据结束
	Delay1us();
}

uchar Ds1302Read(uchar addr)
{
	uchar n, dat = 0, dat1;
	CE = 0;
	_nop_();
	SCLK = 0;
	_nop_();
	CE = 1;
	for (n = 0; n < 8; n++)
	{
		DSIO = addr & 0x01;
		addr >>= 1;
		SCLK = 1;
		_nop_();
		SCLK = 0;
		_nop_();
	}
	for (n = 0; n < 8; n++)
	{
		dat1 = DSIO;
		dat1 <<= n;
		dat |= dat1;

		SCLK = 1;
		_nop_();
		SCLK = 0;
		_nop_();
	}
	CE = 0;
	_nop_(); //以下为DS1302复位的稳定时间,必须的。
	SCLK = 1;
	_nop_();
	DSIO = 0;
	_nop_();
	DSIO = 1;
	_nop_();
	return dat;
}
