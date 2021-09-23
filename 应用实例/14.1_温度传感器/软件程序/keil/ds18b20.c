#include <reg51.h>

#include"userdef.h"
#include"lcd1602.h"
#include"ds18b20.h"

uchar code str1[] = {0x28,0x30,0xC5,0xB8,0x00,0x00,0x00,0x8E}; //ROM1
uchar code str2[] = {0x28,0x31,0xC5,0xB8,0x00,0x00,0x00,0xB9}; //ROM2
uint tvalue;//温度值
bit tflag;//温度正负标志

static void delay5us(uint i)  /*延时5微秒函数*/
{
     while(i--);
}

static void ds18b20reset()     /*ds1820复位函数*/
{   
    uchar x=0;
    LCE_DQ = 1;       //DQ复位
    delay5us(4); 	  //延时
    LCE_DQ = 0;       //DQ拉低
    delay5us(100); 	  //精确延时大于480us
    LCE_DQ = 1;       //DQ拉高
    delay5us(40); 
}

static uchar ds18b20_read()   /*读一个字节数据*/
{
	uchar i = 0;
    uchar dat = 0;
    for (i=0;i<8;i++)
	{  
		LCE_DQ = 0; //给脉冲信号
		dat>>=1;
		LCE_DQ = 1; //给脉冲信号
		if(LCE_DQ)
		dat|=0x80;
		delay5us(10);
	}
	return(dat);
}

static void ds18b20_write(uchar dat)  /*写一个字节数据*/
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

static void b20_Matchrom(uchar x)  /*匹配ROM函数*/
{
    char j;
    ds18b20_write(0x55);    //发送匹配ROM命令
    if (x==1)
    {
        for(j=0;j<8;j++)
        ds18b20_write(str1[j]); //发送18B20的序列号，先发送低字节 
    }
    if(x==2)
    {
		for(j=0;j<8;j++)
        ds18b20_write(str2[j]); //发送18B20的序列号，先发送低字节 
    }
}

extern uchar read_temp(uchar z)   /*读取温度值并转换函数*/
{
    uchar th,tl;
    float tt;
/**********************************************************************/
    ds18b20reset();    	  //初始化
//  ds18b20_write(0xCC);		  //发送Skip Rom命令，跳过匹配直接转换温度
	if(z==1)
    {
        b20_Matchrom(1);  //匹配ROM1
    }
    if(z==2)
	{
        b20_Matchrom(2);  //匹配ROM2
	}
	ds18b20_write(0x44);		  //发送Convert T命令，开始转换温度
/*********************************************************************/
    ds18b20reset();    	  //初始化
    if(z==1)
    {
        b20_Matchrom(1);  //匹配ROM1
    }
    if(z==2)
	{
        b20_Matchrom(2);  //匹配ROM2
	}
	ds18b20_write(0x4E);		  //发送write scratchpad命令,向18B20写三个字节，分别为报警上限、下限以及转换分辨率设置
	ds18b20_write(0xFF);		  //由于不用18B20内部的报警，所以将上下限设置为最高与最低
	ds18b20_write(0x00);
	ds18b20_write(0x7F);		  //设置转换精度——1F：9位————3F：10位————5F：11位————7F：12位——
/*************************************************************************/
    ds18b20reset();    	 //初始化
    if(z==1)
    {
        b20_Matchrom(1);  //匹配ROM1
    }
    if(z==2)
	{
        b20_Matchrom(2);  //匹配ROM2
	}
	ds18b20_write(0xbe);    //读取温度 
	tl = ds18b20_read();    //低8位
	th = ds18b20_read();    //高8位
	tvalue = th;
	tvalue<<=8;
	tvalue=tvalue|tl;
	if(tvalue<0x0fff)
    	tflag=0;
    else
    {
		tvalue=~tvalue+1;  //补码取反加一
		tflag=1;
    }
    tt=tvalue*0.0625;	   //乘最小位的权值转换为10进制数值
    tvalue=tt*100;		   //要显示两位小数，乘100用于取模提取数字
    return(tvalue);
}