#include "lcd1602.h"

//д�����������
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


//��ʼ��
void lcd1602Init()
{
	lcd1602Write(0x38, LCD_WRITE_COM); //lcd��ʾ����
	lcd1602Write(0x08, LCD_WRITE_COM);	//��ʾ�ر�
	lcd1602Write(0x01, LCD_WRITE_COM);	//����
	lcd1602Write(0x06, LCD_WRITE_COM);	//��ʾ����ƶ�����
	lcd1602Write(0x0f, LCD_WRITE_COM);	//�����˸
}


//��ʾһ���ַ���
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


//��ʾһ���ַ�
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


//����
void lcd1602Clear()  
{ 
	lcd1602Write(0x01, LCD_WRITE_COM);
	delay_ms(5);
 }


