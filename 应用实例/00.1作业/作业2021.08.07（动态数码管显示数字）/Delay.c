#include <REGX52.H>
#include <INTRINS.H>
#include "UserDef.H"
#include "Delay.H"

/*******************************************************************************
* 函 数 名         :  DelayXms 
* 函数功能		 :  延时Xms 	   晶振为12MHz 
* 输    入         :  xms（延时毫秒数）
* 输    出         :  无
*******************************************************************************/
extern void DelayXms(INT16U xms)	
{
	INT8U  i, j; 
	while(xms--)
	{
	i = 2;
	j = 236;
		do
		{
			while (--j);
		} 
		while (--i);
	}
}