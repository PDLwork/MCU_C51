#include <REGX52.H>
#include "UserDef.H"
#include "Delay.H"
#include "ButtonScan.H"

INT8U Button_Value;

extern INT8U ButtonScan(void)
{
	Button_Value = 0;
	P1 = 0xFF;		//将按钮引脚置1
	
	if(Button1 == 0)      	//检测按键1按下
	{
		DelayXms(10);    //延时消抖
		if(Button1 == 0)
		{
			Button_Value = 1;
		}
		while(Button1 != 1);   //松手检测
	}
	
	if(Button2 == 0)      	//检测按键1按下
	{
		DelayXms(10);    //延时消抖
		if(Button2 == 0)
		{
			Button_Value = 2;
		}
		while(Button2 != 1);   //松手检测
	}
	
	if(Button3 == 0)      	//检测按键1按下
	{
		DelayXms(10);    //延时消抖
		if(Button3 == 0)
		{
			Button_Value = 3;
		}
		while(Button3 != 1);   //松手检测
	}
	
	if(Button4 == 0)      	//检测按键1按下
	{
		DelayXms(10);    //延时消抖
		if(Button4 == 0)
		{
			Button_Value = 4;
		}
		while(Button4 != 1);   //松手检测
	}
	
	if(Button5 == 0)      	//检测按键1按下
	{
		DelayXms(10);    //延时消抖
		if(Button5 == 0)
		{
			Button_Value = 5;
		}
		while(Button5 != 1);   //松手检测
	}
	
	if(Button6 == 0)      	//检测按键1按下
	{
		DelayXms(10);    //延时消抖
		if(Button6 == 0)
		{
			Button_Value = 6;
		}
		while(Button6 != 1);   //松手检测
	}
	
	if(Button7 == 0)      	//检测按键1按下
	{
		DelayXms(10);    //延时消抖
		if(Button7 == 0)
		{
			Button_Value = 7;
		}
		while(Button7 != 1);   //松手检测
	}
	
	if(Button8 == 0)      	//检测按键1按下
	{
		DelayXms(10);    //延时消抖
		if(Button8 == 0)
		{
			Button_Value = 8;
		}
		while(Button8 != 1);   //松手检测
	}
	
	return Button_Value;
}