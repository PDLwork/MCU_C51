#include <REGX52.H>
#include "userdef.h"
#include "LCD1602.h"

/*******************************************************************************
* �� �� ��         :  main������
* ��������		   :   
* ��    ��         :  ��
* ��    ��         :  ��
*******************************************************************************/
void main(void)
{

	LCD_Initialization();

	while(1)
	{
		_LCD1602_ShowSignedNumber(1,1)
	}

}

extern void _LCD1602_ShowSignedNumber(unsigned char showSite, char showNumber)
{
	unsigned char Ten;
	unsigned char One;
	  
	if(showNumber < 0)
	{
		showNumber = -showNumber;
		Ten = showNumber / 10;
		One = showNumber % 10;
		LCD_ShowChar(showSite, '-');
		LCD_ShowChar(showSite + 1, Ten);
		LCD_ShowChar(showSite + 2, One);
	}
	else
	{
		Ten = showNumber / 10;
		One = showNumber % 10;
		LCD_ShowChar(showSite, Ten);
		LCD_ShowChar(showSite + 1, One);
	}

}
