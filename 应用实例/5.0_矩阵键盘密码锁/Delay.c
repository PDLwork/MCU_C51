#include <REG52.H>
#include "UserDef.H"
#include "Delay.h"

///*******************************************************************************
//* 函 数 名         :  DelayXms 
//* 函数功能		 :  延时Xms 	   晶振为12MHz 
//* 输    入         :  xms（延时毫秒数）
//* 输    出         :  无
//*******************************************************************************/
//void DelayXms(INT16U xms)	
//{
//	INT8U  i, j; 
//	while(--xms)
//	{
//	i = 2;
//	j = 238;
//		do
//		{
//			while (--j);
//		} 
//		while (--i);
//	}
//}

/*******************************************************************************
* 函 数 名         :  DelayXms 
* 函数功能		   :  延时xms 	   晶振为11.0592MHz
* 输    入         :  xms（延时毫秒数）
* 输    出         :  无
*******************************************************************************/
extern void DelayXms(INT16U xms)	
{
	INT8U i, j; 
	while(--xms)
	{
		i = 2;
		j = 198;
		do
		{
			while (--j);
		} 
		while (--i);
	}
}