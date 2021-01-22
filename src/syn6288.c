#include "syn6288.h"
#include "usart.h"
//RXD接端口P1^3,TXD接端口P1^2
uchar nBkm = 0x00;
//*****************************************************
#define HEADLEN       5  //数据包头的长度
#define BKM_OFFSET    4  //背景音乐命令偏移
#define LEN_OFFSET    2  //长度字节的偏移量（一般不会超过255字节，因此只使用1字节长度）
#define BKM_MAX      15	 //背景音乐数量

//*****************************************************

//数据包头（0xFD + 2字节长度 + 1字节命令字 + 1字节命令参数)
uchar head[HEADLEN] = {0xfd,0x00,0x00,0x01,0x00};

//****************************************************




	




//背景音乐(参数为0表示关闭背景音乐)
void BkMusic(uchar num)
{
	num %= BKM_MAX + 1;
	nBkm = num;
}

//发声程序
void Speech(uchar *buf)
{
	uchar i = 0;          //循环计数变量
	uchar xor = 0x00;     //校验码初始化
	uchar ch = 0x00;
    uchar len = 0x00;

    while(buf[len++]);

	//发送数据包头(0xFD + 2字节长度 + 1字节命令字 + 1字节命令参数)
	for(i = 0; i < HEADLEN; i++)
	{
		if(i == BKM_OFFSET)
			ch = nBkm << 3; //写入背景音乐
		else if(i == LEN_OFFSET)
			ch = len + 3;
		else
			ch = head[i];
		
		xor ^= ch;
		SendChar(ch);
		delay_ms(1);
   	}

	//发送文字内容
	for(i = 0; i < len; i++)
	{
		xor ^= buf[i];
		SendChar(buf[i]);
		delay_ms(1);
	}

	SendChar(xor);         //发送校验位

	delay_ms(50);
	//while(BUSY);         //等待合成结束
	delay_ms(50);

}

