#include <reg51.h>

#include"userdef.h"
#include"lcd1602.h"
#include"ds18b20.h"

uchar data disdata[4];	  //用于存放显示数字数组

static void delay1ms(uint x)  /*延时1毫秒函数*/
{ 
    uint i,j;
    for(i=0;i<x;i++)
    	for(j=0;j<100;j++);
}

extern void lcd_write_com(uchar com)   /*LCD写命令函数*/
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

static void lcd_write_dat(uchar dat)   /*LCD写数据函数*/
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

extern void lcd_init()         /*LCD初始化设置*/
{
    lcd_write_com(0x01);	   //清屏
    delay1ms(1);
    lcd_write_com(0x38);	   //设置显示两行、每个字符为5*7点阵、数据线为8根
	delay1ms(1);
	lcd_write_com(0x06);	   //输入后地址指针右移
	delay1ms(1);
}

extern void lcd_dis_mod(uchar x)	   /*显示方式设置，1为实时显示，2为设置模式*/
{
	if(x==1)
	{
		lcd_write_com(0x0c);	   //显示打开、光标关闭
		delay1ms(1);

		lcd_write_com(0x80);
	    lcd_write_dat('A');
	    lcd_write_dat(':');
	    lcd_write_com(0x8A);
	    lcd_write_dat(0xdf);	    //显示摄氏温度字符°
	    lcd_write_dat('C');
	
	    lcd_write_com(0xc0);
	    lcd_write_dat('B');
	    lcd_write_dat(':');
	    lcd_write_com(0xcA);
	    lcd_write_dat(0xdf);        //显示摄氏温度字符°
	    lcd_write_dat('C');
	}
	if(x==2)
	{	
		lcd_write_com(0x0f);	   //显示打开、光标打开并闪烁
		delay1ms(1);

		lcd_write_com(0x80);
	    lcd_write_dat('H');
	    lcd_write_dat(':');
		lcd_write_com(0x86);
		lcd_write_dat(0xdf);        //显示摄氏温度字符°
	    lcd_write_dat('C');
		
		lcd_write_com(0xc0);
	    lcd_write_dat('L');
	    lcd_write_dat(':');
		lcd_write_com(0xc6);
		lcd_write_dat(0xdf);        //显示摄氏温度字符°
	    lcd_write_dat('C');	
	}
}

extern void lcd_disp_alarm(char xx)    /*报警设置显示函数*/
{
	uchar flagdat;	
	if(xx>=0)
	{
		flagdat=0x20;//正温度不显示符号
	}
	else
	{
		flagdat=0x2d;//负温度显示负号:-
		xx = xx * -1;
	}

	disdata[0]=xx/100+0x30;//百位数
	disdata[1]=xx/10%10+0x30;//十位数
	disdata[2]=xx%10+0x30;//个位数
			
	if(disdata[0]==0x30)
	{
		disdata[0]=0x20;//如果百位为0，不显示
        if(disdata[1]==0x30)
		{
			disdata[1]=0x20;//如果百位为0，十位为0也不显示
		}
	}
    lcd_write_dat(flagdat);//显示符号位
    lcd_write_dat(disdata[0]);//显示百位
    lcd_write_dat(disdata[1]);//显示十位 
    lcd_write_dat(disdata[2]);//显示个位
}

extern void lcd_disp_18b20(uchar x)    /*温度值显示函数*/
{    
	uchar flagdat;
	disdata[0]=tvalue/10000+0x30;//百位数
	disdata[1]=tvalue%10000/1000+0x30;//十位数
	disdata[2]=tvalue%1000/100+0x30;//个位数
	disdata[3]=tvalue%100/10+0x30;//小数点后一位
	disdata[4]=tvalue%10+0x30;//小数点后两位
	
	if(tflag==0)
		flagdat=0x20;//正温度不显示符号
	else
		flagdat=0x2d;//负温度显示负号:-

	if(disdata[0]==0x30)
	{
		disdata[0]=0x20;//如果百位为0，不显示
        if(disdata[1]==0x30)
		{
			disdata[1]=0x20;//如果百位为0，十位为0也不显示
		}
	}

    if(x==1)
    {
		lcd_write_com(0x82);	//显示地址位置
	}
	if(x==2)
	{
		lcd_write_com(0xc2);
	}
    lcd_write_dat(flagdat);//显示符号位
    lcd_write_dat(disdata[0]);//显示百位
    lcd_write_dat(disdata[1]);//显示十位 
    lcd_write_dat(disdata[2]);//显示个位 
    lcd_write_dat(0x2e);//显示小数点 
	lcd_write_dat(disdata[3]);//显示小数点后一位
	lcd_write_dat(disdata[4]);//显示小数点后两位	
}