#include <DS18B20_2.h>

bit flag_fu2=0;
/***************以下是测温程序*****************/
void delay_18B20_2(unsigned int i)//延时函数
{
 while(i--);
}
//18b20初始化函数
static void Init_DS18B20(void)
{
 unsigned char x=0;
 DQ_2 = 1;    //DQ_2复位
 delay_18B20_2(8);  //稍做延时
 DQ_2 = 0;    //单片机将DQ_2拉低
 delay_18B20_2(80); //精确延时 大于 480us
 DQ_2 = 1;    //拉高总线
 delay_18B20_2(10);
 x=DQ_2;      //稍做延时后 如果x=0则初始化成功 x=1则初始化失败
 delay_18B20_2(5);
}

//读一个字节
static unsigned char ReadOneChar(void)
{
unsigned char i=0;
unsigned char dat = 0;
for (i=8;i>0;i--)
 {
  DQ_2 = 0; // 给脉冲信号
  dat>>=1;
  DQ_2 = 1; // 给脉冲信号
  if(DQ_2)
   dat|=0x80;
  delay_18B20_2(5);
 }
 return(dat);
}
//写一个字节
static void WriteOneChar(unsigned char dat)
{
 unsigned char i=0;
 for (i=8; i>0; i--)
 {
  DQ_2 = 0;
  DQ_2 = dat&0x01;
  delay_18B20_2(5);
  DQ_2 = 1;
  dat>>=1;
 }
delay_18B20_2(5);
}
//读取温度
int ReadTemperature_2(void)
{
	int value; //存放温度数值
	unsigned int tmpvalue;

	unsigned char a=0;
	unsigned char b=0;
	float t;

	Init_DS18B20();
	WriteOneChar(0xCC); // 跳过读序号列号的操作
	WriteOneChar(0x44); // 启动温度转换
	delay_18B20_2(100);
	Init_DS18B20();
	WriteOneChar(0xCC); //跳过读序号列号的操作 
	WriteOneChar(0xBE); //读取温度寄存器等（共可读9个寄存器） 前两个就是温度
	a=ReadOneChar();
	b=ReadOneChar();	
	if((b&0xf8)==0xf8) //高字节的高5位为1时，温度为负
		{flag_fu2=1;}
	else
		{flag_fu2=0;}

    //将高低两个字节合成一个整形变量
    //计算机中对于负数是利用补码来表示的
    //若是负值, 读取出来的数值是用补码表示的, 可直接赋值给int型的value
    tmpvalue = b;
    tmpvalue <<= 8;
    tmpvalue |= a;
    value = tmpvalue;
	if(flag_fu2==1)  //温度为负值
	{
		value=(~value)+1; //取反再加1
	}
 
    //使用DS18B20的默认分辨率12位, 精确度为0.0625度, 即读回数据的最低位代表0.0625度
    t = value * 0.0625;
 
    value = t * 100 + (value > 0 ? 0.5 : -0.5); //大于0加0.5, 小于0减0.5
	
    return value;
}