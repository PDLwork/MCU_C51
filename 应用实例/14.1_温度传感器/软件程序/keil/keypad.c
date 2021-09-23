#include <reg52.h>
#include"userdef.h"
#include"lcd1602.h"
#include"keypad.h"

bit dismod_change = 1;		//显示模式设置，1为实时显示模式，0为设置报警模式
bit temp_change = 1;	   //温度设置标志位，1为设置上限，0为设置下限
char higtemp = 110;		//分别存放报警上下限
char lowtemp = -5;

static void delay1ms(uint x)  /*延时1毫秒函数*/
{ 
    uint i,j;
    for(i=0;i<x;i++)
    	for(j=0;j<100;j++);
}

extern void keypadscan(void)		 /*键盘读取函数*/
{
	if(SW_1==0)			   //显示模式转化开关
	{
		delay1ms(10);	   //延时10毫秒后再次扫描消抖
		if(SW_1==0)
		{
			lcd_init();    //LCD初始化显示
			dismod_change = !dismod_change;
			lcd_write_com(0x82);
			lcd_disp_alarm(higtemp);
			lcd_write_com(0xC2);
			lcd_disp_alarm(lowtemp);
			while(!SW_1);	   //直到松开按钮，防止误触
		}	
	}

	if(SW_2==0)			   //上下限转换开关
	{
		delay1ms(10);	   
		if(SW_2==0)
		{
			temp_change = !temp_change;
			while(!SW_2);	   
		}	
	}

	if(SW_3==0)			 //＋1开关
	{
		delay1ms(10);	   
		if(SW_3==0)
		{
			if(!dismod_change)
			{
				if(temp_change)
					higtemp = higtemp + 1;
				if(!temp_change)
				{
					lowtemp = lowtemp + 1;
				}
				lcd_write_com(0x82);
				lcd_disp_alarm(higtemp);
				lcd_write_com(0xC2);
				lcd_disp_alarm(lowtemp);
				lcd_dis_mod(2);	
			}
			while(!SW_3);	   
		}	
	}

	if(SW_4==0)			//-1开关
	{
		delay1ms(10);	  
		if(SW_4==0)
		{
			if(!dismod_change)
			{
				if(temp_change)
					higtemp = higtemp - 1;
				if(!temp_change)
				{
					lowtemp = lowtemp - 1;
				}
				lcd_write_com(0x82);
				lcd_disp_alarm(higtemp);
				lcd_write_com(0xC2);
				lcd_disp_alarm(lowtemp);
				lcd_dis_mod(2);	
			}
			while(!SW_4);	   
		}	
	}

	if(SW_5==0)			 //＋10开关
	{
		delay1ms(10);	   
		if(SW_5==0)
		{
			if(!dismod_change)
			{
				if(temp_change)
					higtemp = higtemp + 10;
				if(!temp_change)
				{
					lowtemp = lowtemp + 10;
				}
				lcd_write_com(0x82);
				lcd_disp_alarm(higtemp);
				lcd_write_com(0xC2);
				lcd_disp_alarm(lowtemp);
				lcd_dis_mod(2);	
			}
			while(!SW_5);	  
		}	
	}

	if(SW_6==0)			 //-10开关
	{
		delay1ms(10);	   
		if(SW_6==0)
		{
			if(!dismod_change)
			{
				if(temp_change)
					higtemp = higtemp - 10;
				if(!temp_change)
				{
					lowtemp = lowtemp - 10;
				}
				lcd_write_com(0x82);
				lcd_disp_alarm(higtemp);
				lcd_write_com(0xC2);
				lcd_disp_alarm(lowtemp);
				lcd_dis_mod(2);	
			}
			while(!SW_6);	   
		}	
	}
}