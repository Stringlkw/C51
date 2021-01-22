#include "ds18b20.h"
#include "lcd12864.h"


void main()
{
    uint temperature = 0;
    lcd12864Init();

    while (1)
    {
        while(1)
	{
			temperature = get_temp();
			Display(temperature);		
	}
    }
}
