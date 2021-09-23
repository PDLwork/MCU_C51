#include <reg51.h>

#include"userdef.h"
#include"lcd1602.h"
#include"ds18b20.h"

uchar data disdata[4];	  //���ڴ����ʾ��������

static void delay1ms(uint x)  /*��ʱ1���뺯��*/
{ 
    uint i,j;
    for(i=0;i<x;i++)
    	for(j=0;j<100;j++);
}

extern void lcd_write_com(uchar com)   /*LCDд�����*/
{ 
     delay1ms(1);
     LCD_RS = 0;
     LCD_RW = 0;
     LCD_E = 0;
     P0 = com;
     delay1ms(1);
     LCD_E = 1;
     delay1ms(1);
     LCD_E = 0;
}

static void lcd_write_dat(uchar dat)   /*LCDд���ݺ���*/
{ 
     delay1ms(1);;
     LCD_RS = 1;
     LCD_RW = 0;
     LCD_E = 0;
     P0 = dat;
     delay1ms(1);
     LCD_E = 1;
     delay1ms(1);
     LCD_E = 0;
}

extern void lcd_init()         /*LCD��ʼ������*/
{
    lcd_write_com(0x01);	   //����
    delay1ms(1);
    lcd_write_com(0x38);	   //������ʾ���С�ÿ���ַ�Ϊ5*7����������Ϊ8��
	delay1ms(1);
	lcd_write_com(0x06);	   //������ַָ������
	delay1ms(1);
}

extern void lcd_dis_mod(uchar x)	   /*��ʾ��ʽ���ã�1Ϊʵʱ��ʾ��2Ϊ����ģʽ*/
{
	if(x==1)
	{
		lcd_write_com(0x0c);	   //��ʾ�򿪡����ر�
		delay1ms(1);

		lcd_write_com(0x80);
	    lcd_write_dat('A');
	    lcd_write_dat(':');
	    lcd_write_com(0x8A);
	    lcd_write_dat(0xdf);	    //��ʾ�����¶��ַ���
	    lcd_write_dat('C');
	
	    lcd_write_com(0xc0);
	    lcd_write_dat('B');
	    lcd_write_dat(':');
	    lcd_write_com(0xcA);
	    lcd_write_dat(0xdf);        //��ʾ�����¶��ַ���
	    lcd_write_dat('C');
	}
	if(x==2)
	{	
		lcd_write_com(0x0f);	   //��ʾ�򿪡����򿪲���˸
		delay1ms(1);

		lcd_write_com(0x80);
	    lcd_write_dat('H');
	    lcd_write_dat(':');
		lcd_write_com(0x86);
		lcd_write_dat(0xdf);        //��ʾ�����¶��ַ���
	    lcd_write_dat('C');
		
		lcd_write_com(0xc0);
	    lcd_write_dat('L');
	    lcd_write_dat(':');
		lcd_write_com(0xc6);
		lcd_write_dat(0xdf);        //��ʾ�����¶��ַ���
	    lcd_write_dat('C');	
	}
}

extern void lcd_disp_alarm(char xx)    /*����������ʾ����*/
{
	uchar flagdat;	
	if(xx>=0)
	{
		flagdat=0x20;//���¶Ȳ���ʾ����
	}
	else
	{
		flagdat=0x2d;//���¶���ʾ����:-
		xx = xx * -1;
	}

	disdata[0]=xx/100+0x30;//��λ��
	disdata[1]=xx/10%10+0x30;//ʮλ��
	disdata[2]=xx%10+0x30;//��λ��
			
	if(disdata[0]==0x30)
	{
		disdata[0]=0x20;//�����λΪ0������ʾ
        if(disdata[1]==0x30)
		{
			disdata[1]=0x20;//�����λΪ0��ʮλΪ0Ҳ����ʾ
		}
	}
    lcd_write_dat(flagdat);//��ʾ����λ
    lcd_write_dat(disdata[0]);//��ʾ��λ
    lcd_write_dat(disdata[1]);//��ʾʮλ 
    lcd_write_dat(disdata[2]);//��ʾ��λ
}

extern void lcd_disp_18b20(uchar x)    /*�¶�ֵ��ʾ����*/
{    
	uchar flagdat;
	disdata[0]=tvalue/10000+0x30;//��λ��
	disdata[1]=tvalue%10000/1000+0x30;//ʮλ��
	disdata[2]=tvalue%1000/100+0x30;//��λ��
	disdata[3]=tvalue%100/10+0x30;//С�����һλ
	disdata[4]=tvalue%10+0x30;//С�������λ
	
	if(tflag==0)
		flagdat=0x20;//���¶Ȳ���ʾ����
	else
		flagdat=0x2d;//���¶���ʾ����:-

	if(disdata[0]==0x30)
	{
		disdata[0]=0x20;//�����λΪ0������ʾ
        if(disdata[1]==0x30)
		{
			disdata[1]=0x20;//�����λΪ0��ʮλΪ0Ҳ����ʾ
		}
	}

    if(x==1)
    {
		lcd_write_com(0x82);	//��ʾ��ַλ��
	}
	if(x==2)
	{
		lcd_write_com(0xc2);
	}
    lcd_write_dat(flagdat);//��ʾ����λ
    lcd_write_dat(disdata[0]);//��ʾ��λ
    lcd_write_dat(disdata[1]);//��ʾʮλ 
    lcd_write_dat(disdata[2]);//��ʾ��λ 
    lcd_write_dat(0x2e);//��ʾС���� 
	lcd_write_dat(disdata[3]);//��ʾС�����һλ
	lcd_write_dat(disdata[4]);//��ʾС�������λ	
}