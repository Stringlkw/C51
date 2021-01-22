#ifndef _GENERAL_H_
#define _GENERAL_H_

//头文件

#include <reg52.h>
#include <intrins.h>
#include <stdio.h>

//宏定义
#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long

//数据 命令选择定义
#define LCD_WRITE_DATA 1
#define LCD_WRITE_COM 0


//延时函数
void delay_us(uchar t); //大约延时 t us	，不超过 256 us
void delay_ms(uint t); //大约延时 t ms
void delay_100us(uint n);
void delay1s(void);
void delay1ms(void);
#endif
