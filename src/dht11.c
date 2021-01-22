// #include "dht11.h"
// #include "lcd12864.h"

// sbit DHT11_DQ = P1 ^ 0; //dht11data�˽ӵ�Ƭ����P1^0��//
// unsigned char mun_char_table[]={"0123456789"};
// uchar hum_float, hum_int, tmp_float, tmp_int;
// uint m, n;
// //����Ҫ����ʱ
// void delayus(uchar n)
// {
//     while (n--)
//         ;
// }
// //����Ҫ����ʱ
// void Delay10ms(void) //12M��������ʱ
// {
//     uchar a, b;
//     for (b = 249; b > 0; b--)
//         for (a = 17; a > 0; a--)
//             ;
// }

// //��ʼ
// void dhtReset(void)
// {
//     DHT11_DQ = 1;
//     delay_ms(10);
//     DHT11_DQ = 0;
//     Delay10ms(); //�������������ͱ������
//     //18msDHT11�ܼ�⵽��ʼ�ź�
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
//             ;        //�ȴ�50ms
//         delayus(30); //��ʱ29us
//         if (DHT11_DQ == 1)
//         {
//             dht = dht | 0x01;
//             delayus(60);
//         }
//         else
//             delayus(30); //��ʱ29us
//     }
//     return dht;
// }
// void dhtReadHumTmp()
// {
//     dhtReset();
//     DHT11_DQ = 0; //����������>18ms
//     delay_ms(20); //��ʱ>18ms
//     DHT11_DQ = 1; //���ߵȴ�
//     delayus(30);  //��ʱ29us
//     DHT11_DQ = 1;
//     if (!DHT11_DQ)
//     {
//         while (!DHT11_DQ)
//             ;
//         while (DHT11_DQ)
//             ;
//         hum_int = dhtReadByte(); //ʪ����������
//         hum_float = dhtReadByte(); //ʪ��С������
//         tmp_int = dhtReadByte();   //�¶���������
//         tmp_float = dhtReadByte(); //�¶�С������
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
