#ifndef __DS12B20_H
#define __DS12B20_H

#include "general.h"
#include "lcd12864.h"

/*U2_DS18B20*/
sbit DS_data = P2^2;

/*DS18B20*/
uchar DS_Init(void);
void DS_Write(unsigned char cmd);
unsigned char DS_Read();
/*U2获取温度*/
unsigned int get_temp();
void Display(unsigned int Tem);
void write_storage(uchar MAX,uchar MIN);

#endif /*__DS12B20_H*/
