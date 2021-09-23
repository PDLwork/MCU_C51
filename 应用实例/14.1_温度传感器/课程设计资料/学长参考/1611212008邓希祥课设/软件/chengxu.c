#include <reg52.h> 
#include <DS18B20_1.h>
#include <DS18B20_2.h> 
#include <math.h>         

#define uchar unsigned char	  
#define uint  unsigned  int	 
sbit BUTON1=P1^0;
sbit BUTON2=P1^1;
sbit BUTON3=P1^2;
sbit BUTON4=P1^3;
sbit BUTON5=P1^4;
sbit BUTON6=P1^5;
sbit w1=P2^0;
sbit w2=P2^1;
sbit w3=P2^2;
sbit w4=P2^3;
sbit w5=P2^4;
sbit w6=P2^5;
sbit w7=P2^6;
sbit w8=P2^7;
sbit bz=P1^6;
#define all_off {P2=0XFF;}

bit flag_disp;
uchar count,yuzhi1=15,yuzhi2=30;				
int temperature_1,temperature_2,temperature;         //存放温度值
code uchar shuma[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90}; //显示段码 共阳数码管
//延时函数
void delay(uint num)
{
	while( --num );
}
void disp()	//数码管显示函数 
{
	if(flag_disp==0)                          //显示第一路
	{
		if(flag_fu1==1)	 
		{all_off;P0=0xBF;w1=0;delay(150);}	  //如果温度为负，在第一位显示“-”
		else
		{all_off;P0=0xFF;w1=0;delay(150);}
	}
	else //显示第二路
	{
		if(flag_fu2==1)	 //负温度
		{all_off;P0=0xBF;w1=0;delay(150);}
		else
		{all_off;P0=0xFF;w1=0;delay(150);}
	}
	all_off;P0=shuma[temperature/1000];w2=0;delay(150); //带小数点位
	all_off;P0=shuma[temperature/100%10]&0x7F;w3=0;delay(150);//显示温度
	all_off;P0=shuma[temperature/10%10];w4=0;delay(150);

	all_off;P0=shuma[yuzhi1/10];w5=0;delay(150);//显示上限
	all_off;P0=shuma[yuzhi1%10];w6=0;delay(150);

	all_off;P0=shuma[yuzhi2/10];w7=0;delay(150);//显示下限
	all_off;P0=shuma[yuzhi2%10];w8=0;delay(150);

}
void BUTONscan()	   //按键扫描函数
{
	if(!BUTON1)	   //检测按下
	{
		delay(10); //延时消抖动			    
		if(!BUTON1)  //
		{
			if(yuzhi1<99)yuzhi1++;
			while(!BUTON1){;}//检测松手
		}
	}
	if(!BUTON2)	   //检测按下
	{
		delay(10); //延时消抖动
		if(!BUTON2)  //
		{
			if(yuzhi1>1)yuzhi1--;
			while(!BUTON2){;}//检测松手
		}
	}
	if(!BUTON3)	   //检测按下
	{
		delay(10); //延时消抖动
		if(!BUTON3)  //
		{
			flag_disp=0;
			while(!BUTON3){;}//检测松手
		}
	}
	if(!BUTON4)	   //检测按下
	{
		delay(10); //延时消抖动
		if(!BUTON4)  //
		{
			flag_disp=1;
			while(!BUTON4){;}//检测松手
		}
	}
	if(!BUTON5)	   //检测按下
	{
		delay(10); //延时消抖动
		if(!BUTON5)  //
		{
			if(yuzhi2<99)yuzhi2++;
			while(!BUTON5){;}//检测松手
		}
	}
	if(!BUTON6)	   //检测按下
	{
		delay(10); //延时消抖动
		if(!BUTON6)  //
		{
			if(yuzhi2>1)yuzhi2--;
			while(!BUTON6){;}//检测松手
		}
	}
}
void main()
{
	TMOD |= 0x01;	//初始化定时器0		     
	TL0 = 0x00;		//设置定时初值
	TH0 = 0xee;		//设置定时初值5MS
	EA=1;                      
	ET0=1;                 
	TR0=0;  

	while(1)		
	{
		BUTONscan();	//按键扫描函数
		temperature_1=ReadTemperature_1();	 //读温度1
		temperature_2=ReadTemperature_2();	 //读温度2
			
		temperature_1 = abs(temperature_1);//取绝对值
		temperature_1=temperature_1%10000;//温度整数和2位小数(现在是十进制数)
		temperature_2 = abs(temperature_2);//取绝对值
		temperature_2=temperature_2%10000;//温度整数和2位小数(现在是十进制数)
		if(flag_disp==0)
		{temperature=temperature_1;}
		else
		{temperature=temperature_2;}
		if(flag_fu1==1 || flag_fu2==1 || temperature_1<yuzhi1*100 || temperature_1>yuzhi2*100 || temperature_2<yuzhi1*100 || temperature_2>yuzhi2*100)	
			bz=0;
		else
			bz=1;
		disp();			//数码管显示
	}
}
void Tim() interrupt 1 
{
	TL0 = 0x00;		//设置定时初值
	TH0 = 0xee;		//设置定时初值

	count++;
	switch(count)  //数码管动态显示
	{
		case 1:all_off;P0=shuma[temperature/1000];w1=0;
		break;
		case 2:all_off;P0=shuma[temperature/100%10]&0x7F;w2=0;
		break;
		case 3:all_off;P0=shuma[temperature/10%10];w3=0;
		break;
		case 4:all_off;P0=shuma[temperature%10];w4=0;
		break;
		case 5:all_off;P0=shuma[56/10];w5=0;
		break;
		case 6:all_off;P0=shuma[56%10];w6=0;
		break;
		case 7:all_off;P0=shuma[15/10];w7=0;
		break;
		case 8:all_off;P0=shuma[15%10];w8=0;count=0;
		break;
		default:break;
	}
}	