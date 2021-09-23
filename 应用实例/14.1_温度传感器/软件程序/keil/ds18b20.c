#include <reg51.h>

#include"userdef.h"
#include"lcd1602.h"
#include"ds18b20.h"

uchar code str1[] = {0x28,0x30,0xC5,0xB8,0x00,0x00,0x00,0x8E}; //ROM1
uchar code str2[] = {0x28,0x31,0xC5,0xB8,0x00,0x00,0x00,0xB9}; //ROM2
uint tvalue;//�¶�ֵ
bit tflag;//�¶�������־

static void delay5us(uint i)  /*��ʱ5΢�뺯��*/
{
     while(i--);
}

static void ds18b20reset()     /*ds1820��λ����*/
{   
    uchar x=0;
    LCE_DQ = 1;       //DQ��λ
    delay5us(4); 	  //��ʱ
    LCE_DQ = 0;       //DQ����
    delay5us(100); 	  //��ȷ��ʱ����480us
    LCE_DQ = 1;       //DQ����
    delay5us(40); 
}

static uchar ds18b20_read()   /*��һ���ֽ�����*/
{
	uchar i = 0;
    uchar dat = 0;
    for (i=0;i<8;i++)
	{  
		LCE_DQ = 0; //�������ź�
		dat>>=1;
		LCE_DQ = 1; //�������ź�
		if(LCE_DQ)
		dat|=0x80;
		delay5us(10);
	}
	return(dat);
}

static void ds18b20_write(uchar dat)  /*дһ���ֽ�����*/
{ 
	uchar i=0;
    for (i=0; i<8; i++)
	{
		LCE_DQ = 0;
        LCE_DQ = dat&0x01;
        delay5us(10);
        LCE_DQ = 1;
        dat>>=1;
    }
}

static void b20_Matchrom(uchar x)  /*ƥ��ROM����*/
{
    char j;
    ds18b20_write(0x55);    //����ƥ��ROM����
    if (x==1)
    {
        for(j=0;j<8;j++)
        ds18b20_write(str1[j]); //����18B20�����кţ��ȷ��͵��ֽ� 
    }
    if(x==2)
    {
		for(j=0;j<8;j++)
        ds18b20_write(str2[j]); //����18B20�����кţ��ȷ��͵��ֽ� 
    }
}

extern uchar read_temp(uchar z)   /*��ȡ�¶�ֵ��ת������*/
{
    uchar th,tl;
    float tt;
/**********************************************************************/
    ds18b20reset();    	  //��ʼ��
//  ds18b20_write(0xCC);		  //����Skip Rom�������ƥ��ֱ��ת���¶�
	if(z==1)
    {
        b20_Matchrom(1);  //ƥ��ROM1
    }
    if(z==2)
	{
        b20_Matchrom(2);  //ƥ��ROM2
	}
	ds18b20_write(0x44);		  //����Convert T�����ʼת���¶�
/*********************************************************************/
    ds18b20reset();    	  //��ʼ��
    if(z==1)
    {
        b20_Matchrom(1);  //ƥ��ROM1
    }
    if(z==2)
	{
        b20_Matchrom(2);  //ƥ��ROM2
	}
	ds18b20_write(0x4E);		  //����write scratchpad����,��18B20д�����ֽڣ��ֱ�Ϊ�������ޡ������Լ�ת���ֱ�������
	ds18b20_write(0xFF);		  //���ڲ���18B20�ڲ��ı��������Խ�����������Ϊ��������
	ds18b20_write(0x00);
	ds18b20_write(0x7F);		  //����ת�����ȡ���1F��9λ��������3F��10λ��������5F��11λ��������7F��12λ����
/*************************************************************************/
    ds18b20reset();    	 //��ʼ��
    if(z==1)
    {
        b20_Matchrom(1);  //ƥ��ROM1
    }
    if(z==2)
	{
        b20_Matchrom(2);  //ƥ��ROM2
	}
	ds18b20_write(0xbe);    //��ȡ�¶� 
	tl = ds18b20_read();    //��8λ
	th = ds18b20_read();    //��8λ
	tvalue = th;
	tvalue<<=8;
	tvalue=tvalue|tl;
	if(tvalue<0x0fff)
    	tflag=0;
    else
    {
		tvalue=~tvalue+1;  //����ȡ����һ
		tflag=1;
    }
    tt=tvalue*0.0625;	   //����Сλ��Ȩֵת��Ϊ10������ֵ
    tvalue=tt*100;		   //Ҫ��ʾ��λС������100����ȡģ��ȡ����
    return(tvalue);
}