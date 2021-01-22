#ifndef _LCD1602_H_
#define  _LCD1602_H_

#include "general.h"


sbit RS = P3^5;//RSΪ�Ĵ���ѡ�񣬸ߵ�ƽʱѡ�����ݼĴ������͵�ƽʱѡ��ָ��Ĵ���
sbit RW = P3^6;//RWΪ��д�ź���,�ߵ�ƽʱ���ж��������͵�ƽʱ����д����
sbit LCDEN = P3^4;//E��Ϊʹ�ܶˣ���E���ɸߵ�ƽ����ɵ͵�ƽʱ��Һ��ģ��ִ�����
#define GPIO_LCD1602 P2

void lcd1602Write(uchar byte, uchar sign);//д��һ���ֽڣ�signΪ LCD_WRITE_DATA	ʱд�����ݣ� Ϊ	LCD_WRITE_COM д������
void lcd1602Init();//1602��ʼ��
void lcd1602DisplayString(uchar row, uchar column, uchar *str);//�ڿ���ʾ��λ����ʾ�ַ���  0 <= column <= 15�� 0 <= row <= 1
void lcd1602DisplayChar(uchar row, uchar column, uchar ch);//�ڿ���ʾ��λ����ʾ�ַ�  0 <= column <= 15�� 0 <= row <= 1
void lcd1602Clear();//����



#endif