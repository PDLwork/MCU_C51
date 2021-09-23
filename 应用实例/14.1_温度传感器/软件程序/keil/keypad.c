#include <reg52.h>
#include"userdef.h"
#include"lcd1602.h"
#include"keypad.h"

bit dismod_change = 1;		//��ʾģʽ���ã�1Ϊʵʱ��ʾģʽ��0Ϊ���ñ���ģʽ
bit temp_change = 1;	   //�¶����ñ�־λ��1Ϊ�������ޣ�0Ϊ��������
char higtemp = 110;		//�ֱ��ű���������
char lowtemp = -5;

static void delay1ms(uint x)  /*��ʱ1���뺯��*/
{ 
    uint i,j;
    for(i=0;i<x;i++)
    	for(j=0;j<100;j++);
}

extern void keypadscan(void)		 /*���̶�ȡ����*/
{
	if(SW_1==0)			   //��ʾģʽת������
	{
		delay1ms(10);	   //��ʱ10������ٴ�ɨ������
		if(SW_1==0)
		{
			lcd_init();    //LCD��ʼ����ʾ
			dismod_change = !dismod_change;
			lcd_write_com(0x82);
			lcd_disp_alarm(higtemp);
			lcd_write_com(0xC2);
			lcd_disp_alarm(lowtemp);
			while(!SW_1);	   //ֱ���ɿ���ť����ֹ��
		}	
	}

	if(SW_2==0)			   //������ת������
	{
		delay1ms(10);	   
		if(SW_2==0)
		{
			temp_change = !temp_change;
			while(!SW_2);	   
		}	
	}

	if(SW_3==0)			 //��1����
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

	if(SW_4==0)			//-1����
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

	if(SW_5==0)			 //��10����
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

	if(SW_6==0)			 //-10����
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