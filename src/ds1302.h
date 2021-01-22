#ifndef __DS1302_H__
#define __DS1302_H__

#include "general.h"
//---定义ds1302使用的IO口---//
sbit DSIO = P2 ^ 2;
sbit CE = P2 ^ 1;
sbit SCLK = P2 ^ 0;

enum Ds1302_MODE
{
    H24,
    AM,
    PM
};
typedef struct
{
    uchar sec;
    uchar min;
    uchar hour;
    uchar date;
    uchar mon;
    uchar day;
    uchar year;
    uchar mode;
} Ds1302_TypeDef;

void ds1302Init(); //DS1302初始化
void readTime(Ds1302_TypeDef *time);
void writeTime(Ds1302_TypeDef *time);

#endif