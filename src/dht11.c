// #include "dht11.h"
// #include "lcd12864.h"

// sbit DHT11_DQ = P1 ^ 0; //dht11data端接单片机的P1^0口//
// unsigned char mun_char_table[]={"0123456789"};
// uchar hum_float, hum_int, tmp_float, tmp_int;
// uint m, n;
// //很重要的延时
// void delayus(uchar n)
// {
//     while (n--)
//         ;
// }
// //很正要的延时
// void Delay10ms(void) //12M晶振下延时
// {
//     uchar a, b;
//     for (b = 249; b > 0; b--)
//         for (a = 17; a > 0; a--)
//             ;
// }

// //起始
// void dhtReset(void)
// {
//     DHT11_DQ = 1;
//     delay_ms(10);
//     DHT11_DQ = 0;
//     Delay10ms(); //主机把总线拉低必须大于
//     //18msDHT11能检测到起始信号
//     Delay10ms();
//     Delay10ms();
//     DHT11_DQ = 1;
//     delay_ms(1);
// }
// uint integer(uchar x)
// {
//     uchar h, l;
//     uint n;
//     l = x & 0x0f;
//     h = (x & 0xf0) >> 4;
//     n = h * 16 + l;
//     return n;
// }

// uchar dhtReadByte()
// {
//     uchar i, dht;
//     for (i = 8; i > 0; i--)
//     {
//         dht = dht << 1;
//         while (!DHT11_DQ)
//             ;        //等待50ms
//         delayus(30); //延时29us
//         if (DHT11_DQ == 1)
//         {
//             dht = dht | 0x01;
//             delayus(60);
//         }
//         else
//             delayus(30); //延时29us
//     }
//     return dht;
// }
// void dhtReadHumTmp()
// {
//     dhtReset();
//     DHT11_DQ = 0; //数据线拉低>18ms
//     delay_ms(20); //延时>18ms
//     DHT11_DQ = 1; //拉高等待
//     delayus(30);  //延时29us
//     DHT11_DQ = 1;
//     if (!DHT11_DQ)
//     {
//         while (!DHT11_DQ)
//             ;
//         while (DHT11_DQ)
//             ;
//         hum_int = dhtReadByte(); //湿度整数数据
//         hum_float = dhtReadByte(); //湿度小数数据
//         tmp_int = dhtReadByte();   //温度整数数据
//         tmp_float = dhtReadByte(); //温度小数数据
//     }
// }

// void displayTempAndRH()
// {
//     dhtReadHumTmp();
//     m = integer(hum_int);
//     delay_ms(1);
//     n = integer(tmp_int);
//     lcd12864SetPos(3, 0);
//     lcd12864WriteChar(mun_char_table[n / 10]);
//     lcd12864WriteChar(mun_char_table[n % 10]);


//     lcd12864SetPos(3, 3);
//     lcd12864WriteChar(mun_char_table[m / 10]);
//     lcd12864WriteChar(mun_char_table[m % 10]);
// }
