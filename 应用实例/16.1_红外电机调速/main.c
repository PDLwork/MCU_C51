#include <REGX52.H>
#include "UserDef.H"
#include "Infrared.H"
#include "Timer.H"

#define smg P1

INT8U NixieTable[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};//共阳数码管代码表"0-F"(a为最低位)

/*******************************************************************************
* 函 数 名         :  main （主函数）
* 函数功能		   :  主程循环执行
* 输    入         :  无
* 输    出         :  无
*******************************************************************************/
void main(void)
{
	static INT8U Number = 0;
	Infrared_Initialization();
	Timer1_Initialization();
	while(1)
	{
		if(Infrared_DataFlag)
		{
			if(Infrared_Command == Infrared_0)
				Number = 0;
			if(Infrared_Command == Infrared_1)
				Number = 1;
			if(Infrared_Command == Infrared_2)
				Number = 2;
			if(Infrared_Command == Infrared_3)
				Number = 3;
			Infrared_DataFlag = 0;
		}
		smg = NixieTable[Number];
		
		switch(Number)		//根据速度值选择比较值输出对应的PWM波形
		{
			case 0 : Compare = 0; 	break;
			case 1 : Compare = 50; 	break;
			case 2 : Compare = 75; 	break;
			case 3 : Compare = 100; break;
		}
	}
}