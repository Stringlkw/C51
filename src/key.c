// #include "key.h"

// uchar code KeyCodeMap[4][4] = {
//     //矩阵按键编号到标准键盘键码的映射表
//     {'1', '2', '3', 0x26},  //数字键1、数字键2、数字键3、向上键
//     {'4', '5', '6', 0x25},  //数字键4、数字键5、数字键6、向左键
//     {'7', '8', '9', 0x28},  //数字键7、数字键8、数字键9、向下键
//     {'0', 0x1B, 0x0D, 0x27} //数字键0、ESC键、  回车键、 向右键
// };
// uchar pdata KeyState[4][4] = { //全部矩阵按键的当前状态
//     {1, 1, 1, 1},
//     {1, 1, 1, 1},
//     {1, 1, 1, 1},
//     {1, 1, 1, 1}};

// /* 按键驱动函数，检测按键动作，调度相应动作函数，需在主循环中调用 */
// void KeyDriver()
// {
//     uchar i, j;
//     static uchar pdata keyPre[4][4] = {//按键值备份，保存前一次的值
//                                        {1, 1, 1, 1},
//                                        {1, 1, 1, 1},
//                                        {1, 1, 1, 1},
//                                        {1, 1, 1, 1}};
//     for (i = 0; i < 4; i++)
//     {
//         for (j = 0; j < 4; j++)
//         {
//             if (keyPre[i][j] != KeyState[i][j])
//             {
//                 if (keyPre[i][j] != 0)
//                 {
//                     KeyAction(KeyCodeMap[i][j]); //调用按键动作函数
//                 }
//                 keyPre[i][j] = KeyState[i][j];
//             }
//         }
//     }
// }

// /* 按键扫描函数，需在定时中断中调用，推荐调用间隔1ms */
// void KeyScan()
// {
//     uchar i;
//     static uchar keyout = 0;     //矩阵按键扫描输出索引
//     static uchar keybuf[4][4] = {//矩阵按键扫描缓冲区
//                                  {0xFF, 0xFF, 0xFF, 0xFF},
//                                  {0xFF, 0xFF, 0xFF, 0xFF},
//                                  {0xFF, 0xFF, 0xFF, 0xFF},
//                                  {0xFF, 0xFF, 0xFF, 0xFF}};

//     //将一行的4个按键值移入缓冲区
//     keybuf[keyout][0] = (keybuf[keyout][0] << 1) | KEY_IN_1;
//     keybuf[keyout][1] = (keybuf[keyout][1] << 1) | KEY_IN_2;
//     keybuf[keyout][2] = (keybuf[keyout][2] << 1) | KEY_IN_3;
//     keybuf[keyout][3] = (keybuf[keyout][3] << 1) | KEY_IN_4;
//     //消抖后更新按键状态
//     for (i = 0; i < 4; i++) //每行4个按键，所以循环4次
//     {
//         if ((keybuf[keyout][i] & 0x0F) == 0x00)
//         { //连续4次扫描值为0，即4*4ms内都是按下状态时，可认为按键已稳定的按下
//             KeyState[keyout][i] = 0;
//         }
//         else if ((keybuf[keyout][i] & 0x0F) == 0x0F)
//         { //连续4次扫描值为1，即4*4ms内都是弹起状态时，可认为按键已稳定的弹起
//             KeyState[keyout][i] = 1;
//         }
//     }
//     //执行下一次的扫描输出
//     keyout++;               //输出索引递增
//     keyout = keyout & 0x03; //索引值加到4即归零
//     switch (keyout)         //根据索引，释放当前输出引脚，拉低下次的输出引脚
//     {
//     case 0:
//         KEY_OUT_4 = 1;
//         KEY_OUT_1 = 0;
//         break;
//     case 1:
//         KEY_OUT_1 = 1;
//         KEY_OUT_2 = 0;
//         break;
//     case 2:
//         KEY_OUT_2 = 1;
//         KEY_OUT_3 = 0;
//         break;
//     case 3:
//         KEY_OUT_3 = 1;
//         KEY_OUT_4 = 0;
//         break;
//     default:
//         break;
//     }
// }