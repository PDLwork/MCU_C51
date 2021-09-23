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
int temperature_1,temperature_2,temperature;         //����¶�ֵ
code uchar shuma[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90}; //��ʾ���� ���������
//��ʱ����
void delay(uint num)
{
	while( --num );
}
void disp()	//�������ʾ���� 
{
	if(flag_disp==0)                          //��ʾ��һ·
	{
		if(flag_fu1==1)	 
		{all_off;P0=0xBF;w1=0;delay(150);}	  //����¶�Ϊ�����ڵ�һλ��ʾ��-��
		else
		{all_off;P0=0xFF;w1=0;delay(150);}
	}
	else //��ʾ�ڶ�·
	{
		if(flag_fu2==1)	 //���¶�
		{all_off;P0=0xBF;w1=0;delay(150);}
		else
		{all_off;P0=0xFF;w1=0;delay(150);}
	}
	all_off;P0=shuma[temperature/1000];w2=0;delay(150); //��С����λ
	all_off;P0=shuma[temperature/100%10]&0x7F;w3=0;delay(150);//��ʾ�¶�
	all_off;P0=shuma[temperature/10%10];w4=0;delay(150);

	all_off;P0=shuma[yuzhi1/10];w5=0;delay(150);//��ʾ����
	all_off;P0=shuma[yuzhi1%10];w6=0;delay(150);

	all_off;P0=shuma[yuzhi2/10];w7=0;delay(150);//��ʾ����
	all_off;P0=shuma[yuzhi2%10];w8=0;delay(150);

}
void BUTONscan()	   //����ɨ�躯��
{
	if(!BUTON1)	   //��ⰴ��
	{
		delay(10); //��ʱ������			    
		if(!BUTON1)  //
		{
			if(yuzhi1<99)yuzhi1++;
			while(!BUTON1){;}//�������
		}
	}
	if(!BUTON2)	   //��ⰴ��
	{
		delay(10); //��ʱ������
		if(!BUTON2)  //
		{
			if(yuzhi1>1)yuzhi1--;
			while(!BUTON2){;}//�������
		}
	}
	if(!BUTON3)	   //��ⰴ��
	{
		delay(10); //��ʱ������
		if(!BUTON3)  //
		{
			flag_disp=0;
			while(!BUTON3){;}//�������
		}
	}
	if(!BUTON4)	   //��ⰴ��
	{
		delay(10); //��ʱ������
		if(!BUTON4)  //
		{
			flag_disp=1;
			while(!BUTON4){;}//�������
		}
	}
	if(!BUTON5)	   //��ⰴ��
	{
		delay(10); //��ʱ������
		if(!BUTON5)  //
		{
			if(yuzhi2<99)yuzhi2++;
			while(!BUTON5){;}//�������
		}
	}
	if(!BUTON6)	   //��ⰴ��
	{
		delay(10); //��ʱ������
		if(!BUTON6)  //
		{
			if(yuzhi2>1)yuzhi2--;
			while(!BUTON6){;}//�������
		}
	}
}
void main()
{
	TMOD |= 0x01;	//��ʼ����ʱ��0		     
	TL0 = 0x00;		//���ö�ʱ��ֵ
	TH0 = 0xee;		//���ö�ʱ��ֵ5MS
	EA=1;                      
	ET0=1;                 
	TR0=0;  

	while(1)		
	{
		BUTONscan();	//����ɨ�躯��
		temperature_1=ReadTemperature_1();	 //���¶�1
		temperature_2=ReadTemperature_2();	 //���¶�2
			
		temperature_1 = abs(temperature_1);//ȡ����ֵ
		temperature_1=temperature_1%10000;//�¶�������2λС��(������ʮ������)
		temperature_2 = abs(temperature_2);//ȡ����ֵ
		temperature_2=temperature_2%10000;//�¶�������2λС��(������ʮ������)
		if(flag_disp==0)
		{temperature=temperature_1;}
		else
		{temperature=temperature_2;}
		if(flag_fu1==1 || flag_fu2==1 || temperature_1<yuzhi1*100 || temperature_1>yuzhi2*100 || temperature_2<yuzhi1*100 || temperature_2>yuzhi2*100)	
			bz=0;
		else
			bz=1;
		disp();			//�������ʾ
	}
}
void Tim() interrupt 1 
{
	TL0 = 0x00;		//���ö�ʱ��ֵ
	TH0 = 0xee;		//���ö�ʱ��ֵ

	count++;
	switch(count)  //����ܶ�̬��ʾ
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