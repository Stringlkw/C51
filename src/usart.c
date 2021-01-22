#include "usart.h"

void usartInit()
{
    SCON = 0x50;
    TMOD = 0x20; //���ö�ʱ�� 1 Ϊģʽ 2
    PCON = 0x00;
    TH1 = 0xfd; //װ��ֵ�趨������
    TL1 = 0xfd;
    TR1 = 1; //������ʱ��
    EA = 1;  //�����ж�
    ES = 1;  //�����ж�
}

void uart2Init() //COM2��ʼ��///
{
    S2CON = 0x50;
    BRT = 0XFD;
    AUXR = 0x11;
    IE2 = 0x01;
    EA = 1;
}

void usartWriteByte(uchar dat)
{
    ES = 0;
    SBUF = dat;
    while (TI == 0)
        ;
    TI = 0;
    ES = 1;
}

void usartWriteString(uchar *str)
{
    while (*str != '\0')
    {
        usartWriteByte(*str++);
    }
}

void UART_Init(void)
{
	AUXR &= 0xF7;		//�����ʲ�����
	S2CON = 0x50;		//8λ����,�ɱ䲨����
	AUXR &= 0xFB;		//���������ʷ�����ʱ��ΪFosc/12,��12T
	BRT = 0xFD;			//�趨���������ʷ�������װֵ
	AUXR |= 0x10;		//�������������ʷ�����
	ES = 1;				//Ҳ������IE2 |= 0X01�����������ȡҲ��Ҫȫ����IE2
	EA = 1;
}

void SendChar(uchar DAT)
{
	ES = 0;			//IE2 &= 0Xfe;
	S2BUF = DAT;
	while((S2CON & 0X02) == 0);
	S2CON &= ~0X02;
	ES = 1;			//IE2 |= 0X01;
}
