#include <reg52.h>
#include"userdef.h"
#include"lcd1602.h"
#include"ds18b20.h"
#include"keypad.h"
#include"alarm.h"

void main(void)
{ 
	lcd_init();//LCD��ʼ����ʾ
	while(1)
	{
		keypadscan();
		if(dismod_change==1)
		{
			lcd_dis_mod(1);
			while(dismod_change)  //�ڴ�״̬�ظ���ȡ�¶�ֵ����ʾ
			{
				read_temp(1);//��ȡ�¶�
				buz_led_alarm();
		        lcd_disp_18b20(1);//��ʾ
		        read_temp(2);//��ȡ�¶�
				buz_led_alarm();
		        lcd_disp_18b20(2);//��ʾ
				keypadscan();
			}
		}
		if(dismod_change==0)	  //�ڴ�״̬ѭ������������������
		{
			lcd_dis_mod(2);
			while(!dismod_change)
			{			
				keypadscan();
				if(temp_change)				//�жϵ�ǰ���������޻����������������û�
				{
					lcd_write_com(0x81);	//�ù����˸
				}
				else
					lcd_write_com(0xc1);
			}
		}
	}
}