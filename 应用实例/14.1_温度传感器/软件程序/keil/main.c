#include <reg52.h>
#include"userdef.h"
#include"lcd1602.h"
#include"ds18b20.h"
#include"keypad.h"
#include"alarm.h"

void main(void)
{ 
	lcd_init();//LCD初始化显示
	while(1)
	{
		keypadscan();
		if(dismod_change==1)
		{
			lcd_dis_mod(1);
			while(dismod_change)  //在此状态重复读取温度值并显示
			{
				read_temp(1);//读取温度
				buz_led_alarm();
		        lcd_disp_18b20(1);//显示
		        read_temp(2);//读取温度
				buz_led_alarm();
		        lcd_disp_18b20(2);//显示
				keypadscan();
			}
		}
		if(dismod_change==0)	  //在此状态循环检测键盘设置上下限
		{
			lcd_dis_mod(2);
			while(!dismod_change)
			{			
				keypadscan();
				if(temp_change)				//判断当前设置是上限还是下限用于提醒用户
				{
					lcd_write_com(0x81);	//让光标闪烁
				}
				else
					lcd_write_com(0xc1);
			}
		}
	}
}