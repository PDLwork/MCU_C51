/*******************************************************************************
实现功能 ：	通过按键控制马达转速，并在数码管显示挡位
			按键1按下，速度增加
			按键2按下，速度减少
			按键3按下，速度归零
			
引脚定义 ：	Motor	→	P2^2
			smg		→	P0
			Button	→	P1
*******************************************************************************/
	
#include <REGX52.H>
#include "UserDef.H"
#include "Timer.H"
#include "ButtonScan.H"

sbit Motor = P2^2;
#define smg P0

INT8U Compare;		//用于比较输出PWM波形 (范围为0—100)
INT8S Speed;		//速度挡位 (范围为0—3 0：不动 1—3：速度逐渐增加)
INT8U NixieTable[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};//共阳数码管代码表"0-F"(a为最低位)


/*******************************************************************************
* 函 数 名         :  main （主函数）
* 函数功能		   :  主程循环执行
* 输    入         :  无
* 输    出         :  无
*******************************************************************************/
void main(void)
{
	Timer0_Initialization();
	Compare = 0;
	smg = NixieTable[Speed];
	while(1)
	{
		ButtonScan();		//键盘扫描
		
		if(Button_Value)	//通过按键改变速度值
		{
			if(Button_Value == 1)
			{
				Speed++;
				if(Speed > 3)
					Speed = 3;
			}
			if(Button_Value == 2)
			{
				Speed--;
				if(Speed < 0)
					Speed = 0;
			}	
			if(Button_Value == 3)
				Speed = 0;
		}
		
		smg = NixieTable[Speed];		//显示速度值
		
		switch(Speed)		//根据速度值选择比较值输出对应的PWM波形
		{
			case(0): Compare = 0; 	break;
			case(1): Compare = 50; 	break;
			case(2): Compare = 75; 	break;
			case(3): Compare = 100; break;
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
	count %= 100;	//实现超过100归零  可以取代if判断  一个PWM的周期为100*100us即10ms
	if(count < Compare)
		Motor = 1;
	else
		Motor = 0;
}