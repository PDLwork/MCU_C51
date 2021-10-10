/*******************************************************************************
实现功能 ：	用独立按键键盘控制舵机旋转到一定的角度
			舵机是用PWM波控制的
			PWM波是通过定时器零定时加值与比较值比较实现的
引脚定义 ：	独立按键	→	P1
			舵机信号线	→	P2^2
*******************************************************************************/

#include <REGX52.H>
#include "UserDef.H"
#include "Timer.H"
#include "ButtonScan.H"
				
sbit Motor = P2^2;		
INT8U Compare = 7;		//7-90  27 -90

/*******************************************************************************
* 函 数 名         :  main （主函数）
* 函数功能		   :  主程循环执行
* 输    入         :  无
* 输    出         :  无
*******************************************************************************/
void main(void)
{
	Timer0_Initialization();
	while(1)
	{
		ButtonScan();
		if(Button_Value != 0)
		{
			switch(Button_Value)
			{
				case 1:	Compare = 7;	break;
				case 2:	Compare = 10; 	break;
				case 3:	Compare = 13; 	break;
				case 4:	Compare = 15; 	break;
				case 5:	Compare = 18; 	break;
				case 6:	Compare = 21;	break;
				case 7:	Compare = 24; 	break;
				case 8:	Compare = 27; 	break;
			}
		}
	}
}

/*******************************************************************************
* 函 数 名         : Timer_Routine 定时器主函数
* 函数功能		   : 计时器计时一定时间执行内容
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void Timer0_Routine() interrupt 1
{
	static INT8U count;
	TL0 = 0x9C;		//重置定时初始值100微秒 
	TH0 = 0xFF;
    count++;
	count %= 200;	//实现超过100归零  可以取代if判断  一个PWM的周期为200*0.1ms即20ms
	if(count < Compare)
		Motor = 1;
	else
		Motor = 0;
}