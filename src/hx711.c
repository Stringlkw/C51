// #include "hx711.h"
// #include "lcd12864.h"
// long Weight_Shiwu = 0;
// bit Flag_ERROR = 0;
// ulong Weight_Maopi = 0;
// uint qupi = 0;

// //校准参数
// //因为不同的传感器特性曲线不是很一致，因此，每一个传感器需要矫正这里这个参数才能使测量值很准确。
// //当发现测试出来的重量偏大时，增加该数值。
// //如果测试出来的重量偏小时，减小改数值。
// //该值可以为小数
// #define GapValue 400
// //****************************************************
// //延时函数
// //****************************************************
// void Delay_hx711_us(void)
// {
//     _nop_();
//     _nop_();
// }

// //****************************************************
// //读取HX711
// //****************************************************
// ulong hx711Read(void) //增益128
// {
//     ulong count;
//     uchar i;
//     HX711_DOUT = 1;
//     Delay_hx711_us();
//     HX711_SCK = 0;
//     count = 0;
//     EA = 1;
//     while (HX711_DOUT)
//         ;
//     EA = 0;
//     for (i = 0; i < 24; i++)
//     {
//         HX711_SCK = 1;
//         count = count << 1;
//         HX711_SCK = 0;
//         if (HX711_DOUT)
//             count++;
//     }
//     HX711_SCK = 1;
//     count = count ^ 0x800000; //第25个脉冲下降沿来时，转换数据
//     Delay_hx711_us();
//     HX711_SCK = 0;
//     return (count);
// }

// //****************************************************
// //称重
// //****************************************************
// void getWeight()
// {
//     Weight_Shiwu = hx711Read();
//     Weight_Shiwu = Weight_Shiwu - Weight_Maopi; //获取净重
//     if (Weight_Shiwu > 0)
//     {
//         Weight_Shiwu = (unsigned int)((float)Weight_Shiwu / GapValue) - qupi; //计算实物的实际重量
//         if (Weight_Shiwu > 5000)                                              //超重报警
//         {
//             Flag_ERROR = 1;
//         }
//         else
//         {
//             Flag_ERROR = 0;
//         }
//     }
//     else
//     {
//         Weight_Shiwu = 0;
//     }
// }

// void getMaopi()
// {
//     Weight_Maopi = hx711Read();
// }

// void hx711Display()
// {
//     if (Flag_ERROR == 1)
//     {
//         lcd12864DisplayString(1, 0, "ERROR");
//     }
//     else
//     {
//         lcd12864SetPos(1, 4);
//         lcd12864WriteNum(Weight_Shiwu / 1000);
//         lcd12864WriteNum(Weight_Shiwu % 1000 / 100);
//         lcd12864WriteNum(Weight_Shiwu % 100 / 10);
//         lcd12864WriteNum(Weight_Shiwu % 10);
//         lcd12864WriteChar('g');
//     }
// }

// void key1Scan()
// {
//     if (k1 == 0)
//     {
//         delay_ms(10);
//         if (qupi == 0)
//         {
//             qupi = Weight_Shiwu;
//         }
//         else
//         {
//             qupi = 0;
//         }
//         while (!k1)
//             ;
//     }
// }