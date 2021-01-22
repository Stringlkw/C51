#include "lcd1602.h"

//写入命令或数据
void lcd1602Write(uchar byte, uchar sign)
{
	RS = sign;
	RW = 0; 
	LCDEN = 0; 
	GPIO_LCD1602 = byte;
	LCDEN = 1;
	delay_ms(5);
	LCDEN = 0; 
}


//初始化
void lcd1602Init()
{
	lcd1602Write(0x38, LCD_WRITE_COM); //lcd显示设置
	lcd1602Write(0x08, LCD_WRITE_COM);	//显示关闭
	lcd1602Write(0x01, LCD_WRITE_COM);	//清屏
	lcd1602Write(0x06, LCD_WRITE_COM);	//显示光标移动设置
	lcd1602Write(0x0f, LCD_WRITE_COM);	//光标闪烁
}


//显示一个字符串
void lcd1602DisplayString(uchar row, uchar column, uchar *str)
{
	if((column > 15) || (row > 1))
	{
		return ;
	}
	if(0 == row)
	{
		lcd1602Write(0x80 + column, LCD_WRITE_COM);
	}
	else
	{
		lcd1602Write(0x80 + 0x40 + column, LCD_WRITE_COM);
	}
	while(*str != '\0')
	{
		lcd1602Write(*str, LCD_WRITE_DATA);
		str++;
	} 
}


//显示一个字符
void lcd1602DisplayChar(uchar row, uchar column, uchar ch)
{
	if((column > 15) || (row > 1))
	{
		  return ;
	}
	if(0 == row)
	{
		lcd1602Write(0x80 + column, LCD_WRITE_COM);
	}
	else
	{
		lcd1602Write(0x80 + 0x40 + column, LCD_WRITE_COM);
	}
	 lcd1602Write(ch, LCD_WRITE_DATA);
}


//清屏
void lcd1602Clear()  
{ 
	lcd1602Write(0x01, LCD_WRITE_COM);
	delay_ms(5);
 }


