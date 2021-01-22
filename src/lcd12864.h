#ifndef _LCD12864_H_
#define _LCD12864_H_

#include "general.h"

sbit RS = P3 ^ 5;
sbit RW = P3 ^ 6;
sbit LCDEN = P3 ^ 4;
#define GPIO_LCD12864 P0

void lcd12864Init();
void lcd12864Clear();
void lcd12864Write(uchar byte, uchar sign);
void lcd12864DisplayString(uchar row, uchar column, uchar *str);
void lcd12864DisplayChar(uchar row, uchar column, uchar ch);
void lcd12864WriteChar(uchar ch);
void lcd12864ShowStr(uchar row, uchar column, uchar *str, uchar len);
void lcd12864SetPos(uchar row, uchar column);
void lcd12864DisplayNum(uchar row, uchar column, uchar num);
void lcd12864WriteNum(uchar num);
void intToString(uchar *str, int temp_data);
#endif