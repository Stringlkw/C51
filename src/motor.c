// #include "motor.h"

// uchar idata dis_BJ[] = {0x01, 0x02, 0x04, 0x08, 0x08, 0x04, 0x02, 0x01};

// //顺时针转动
// void MotorCW(void)
// {
// 	uchar i;
// 	for(i = 0; i < 4; i++)
// 	{
// 		GPIO_MOTOR = (GPIO_MOTOR & 0xf0) | dis_BJ[i];
// 		delay_ms(3);//转速调节
// 	}
// }

// //逆时针转动
// void MotorCCW(void)
// {
// 	uchar i;
// 	for(i = 4; i < 8; i++)
// 	{
// 		GPIO_MOTOR = (GPIO_MOTOR & 0xf0) | dis_BJ[i];
// 		delay_ms(3);//转速调节
// 	}
// }

// //停止转动
// void MotorStop(void)
// {
// 	GPIO_MOTOR &= 0xf0;
// }



