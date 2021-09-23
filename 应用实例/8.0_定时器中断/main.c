#include <REGX52.H>
#include "UserDef.H"
#include "Timer.H"

#define smg P0

INT8S Number = 9;
INT8U code NixieTable[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};//共阳数码管代码表"0-F"(a为最低位)

/*******************************************************************************
* 函 数 名         :  main主函数
* 函数功能		   :  采用定时器计数，制作倒计时
* 输    入         :  无
* 输    出         :  无
*******************************************************************************/
void main(void)
{
	Timer0_Initialization();
	while(1)
	{
		smg = NixieTable[Number];
	}
}

/*******************************************************************************
* 函 数 名         : Timer0_Routine 定时器0主函数
* 函数功能		   : 计时器计时一定时间执行内容
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void Timer0_Routine() interrupt 1
{
	static INT16U count;
	TL0 = 0x18;		//重置定时初值
	TH0 = 0xFC;		//重置定时初值
	count++;
	if(count >= 1000)
	{
		count = 0;
		Number--;
		if(Number < 0)
			Number = 9;
	}
}