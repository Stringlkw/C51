#include "lcd12864.h"
uchar code NUM[] = {"0123456789 :.-"};

bit lcdBusy()
{

    bit result;
    P0 = 0X00;
    RS = 0;
    RW = 1;
    LCDEN = 1;
    delay_ms(1);
    result = (bit)(P0 & 0x80);
    LCDEN = 0;
    return (result);
}

void lcd12864Write(uchar byte, uchar sign)
{
    while (lcdBusy())
        ;

    RS = sign;
    RW = 0;
    LCDEN = 0;
    _nop_();
    _nop_();
    GPIO_LCD12864 = byte;
    delay_ms(1);
    LCDEN = 1;
    delay_ms(1);
    LCDEN = 0;
    delay_ms(1);
}

void lcd12864Init()
{
    lcd12864Write(0x30, LCD_WRITE_COM);
    lcd12864Write(0x02, LCD_WRITE_COM);

    lcd12864Write(0x06, LCD_WRITE_COM);

    lcd12864Write(0x0c, LCD_WRITE_COM);

    lcd12864Write(0x01, LCD_WRITE_COM);

    lcd12864Write(0x80, LCD_WRITE_COM);
}

void lcd12864DisplayString(uchar row, uchar column, uchar *str)
{
    uchar point;
    if (row == 0)
    {
        point = 0x80 + column;
    }
    else if (row == 1)
    {
        point = 0x90 + column;
    }
    else if (row == 2)
    {
        point = 0x88 + column;
    }
    else if (row == 3)
    {
        point = 0x98 + column;
    }
    else
    {
        return;
    }
    lcd12864Write(point, LCD_WRITE_COM);
    delay_ms(1);
    while (*str != '\0')
    {
        lcd12864Write(*str, LCD_WRITE_DATA);
        delay_ms(2);
        str++;
    }
}

void lcd12864DisplayChar(uchar row, uchar column, uchar ch)
{
    uchar point;
    if (row == 0)
    {
        point = 0x80 + column;
    }
    else if (row == 1)
    {
        point = 0x90 + column;
    }
    else if (row == 2)
    {
        point = 0x88 + column;
    }
    else if (row == 3)
    {
        point = 0x98 + column;
    }
    lcd12864Write(point, LCD_WRITE_COM);
    delay_ms(1);
    lcd12864Write(ch, LCD_WRITE_DATA);
}

void lcd12864WriteChar(uchar ch)
{
    lcd12864Write(ch, LCD_WRITE_DATA);
}
void lcd12864Clear()
{
    lcd12864Write(0x01, LCD_WRITE_COM);
    delay_ms(5);
}

void lcd12864ShowStr(uchar row, uchar column, uchar *str, uchar len)
{
    uchar point;
    if (row == 0)
    {
        point = 0x80 + column;
    }
    else if (row == 1)
    {
        point = 0x90 + column;
    }
    else if (row == 2)
    {
        point = 0x88 + column;
    }
    else if (row == 3)
    {
        point = 0x98 + column;
    }
    else
    {
        return;
    }
    lcd12864Write(point, LCD_WRITE_COM);
    delay_ms(1);
    while (len--)
    {
        lcd12864Write(*str++, LCD_WRITE_DATA);
        delay_ms(1);
    }
}

void lcd12864DisplayNum(uchar row, uchar column, uchar num)
{
    lcd12864DisplayChar(row, column, NUM[num]);
}

void lcd12864WriteNum(uchar num)
{
    lcd12864Write(NUM[num], LCD_WRITE_DATA);
}

void lcd12864SetPos(uchar row, uchar column)
{
    uchar point;
    if (row == 0)
    {
        point = 0x80 + column;
    }
    else if (row == 1)
    {
        point = 0x90 + column;
    }
    else if (row == 2)
    {
        point = 0x88 + column;
    }
    else if (row == 3)
    {
        point = 0x98 + column;
    }
    lcd12864Write(point, LCD_WRITE_COM);
}

//****************************************
//整数转字符串
//****************************************
void intToString(uchar *str, int temp_data)
{
    if (temp_data < 0)
    {
        temp_data = -temp_data;
        *str = '-';
    }
    else
        *str = ' ';
    *++str = temp_data / 100 + 0x30;
    temp_data = temp_data % 100; //取余运算
    *++str = temp_data / 10 + 0x30;
    temp_data = temp_data % 10; //取余运算
    *++str = temp_data + 0x30;
}
