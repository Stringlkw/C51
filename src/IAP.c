#include "IAP.h"
/*使用示例
    当需要把数据写进E2PROM时，需要先擦除，使用程序IAP_erase(IAP_ADDRESS);进行擦除
然后写进去用程序IAP_write(IAP_ADDRESS, lc);。
    当重启后需要读E2PROM数据时，使用程序lc = IAP_read(IAP_ADDRESS);
*/
/*----------------------------
Disable ISP/IAP/EEPROM function
Make MCU in a safe state
----------------------------*/
void iapIdle()
{
	IAP_CONTR = 0;
	IAP_CMD = 0;
	IAP_TRIG = 0;
	IAP_ADDRH = 0x80;       //高位数据地址
	IAP_ADDRL = 0;
}

/*----------------------------
Read one uchar from ISP/IAP/EEPROM area 
Input: addr (ISP/IAP/EEPROM address) 
Output:Flash data
----------------------------*/
uchar iapRead(uint addr)
{
	uchar dat;
	
	IAP_CONTR = ENABLE_IAP;
	IAP_CMD = CMD_READ;
	IAP_ADDRL = addr;
	IAP_ADDRH = addr >> 8;
	IAP_TRIG = 0x5a;
	IAP_TRIG = 0xa5;
	_nop_();
	
	dat = IAP_DATA;
	iapIdle();
	
	return dat;
}

/*----------------------------
Program one uchar to ISP/IAP/EEPROM area 
Input: addr (ISP/IAP/EEPROM address)
		dat (ISP/IAP/EEPROM data) 
Output:-
----------------------------*/
void iapWrite(uint addr, uchar dat)
{
	IAP_CONTR = ENABLE_IAP;
	IAP_CMD = CMD_PROGRAM;
	IAP_ADDRL = addr;
	IAP_ADDRH = addr >> 8;
	IAP_DATA = dat;
	IAP_TRIG = 0x5a;
	IAP_TRIG = 0xa5;
	_nop_();

	iapIdle();
}

/*----------------------------
Erase one sector area
Input: addr (ISP/IAP/EEPROM address) 
Output:-
----------------------------*/
void iapErase(uint addr)
{
	IAP_CONTR = ENABLE_IAP;
	IAP_CMD = CMD_ERASE;
	IAP_ADDRL = addr;
	IAP_ADDRH = addr >> 8;
	IAP_TRIG = 0x5a;
	IAP_TRIG = 0xa5;
	_nop_();
	
	iapIdle();
}