#include <DS18B20_1.h>

bit flag_fu1=0;
/***************以下是测温程序*****************/
void delay_18B20_1(unsigned int i)//延时函数
{
 while(i--);
}
//18b20初始化函数
static void Init_DS18B20(void)
{
 unsigned char x=0;
 DQ_1 = 1;    //DQ_1复位
 delay_18B20_1(8);  //稍做延时
 DQ_1 = 0;    //单片机将DQ_1拉低
 delay_18B20_1(80); //精确延时 大于 480us
 DQ_1 = 1;    //拉高总线
 delay_18B20_1(10);
 x=DQ_1;      //稍做延时后 如果x=0则初始化成功 x=1则初始化失败
 delay_18B20_1(5);
}

//读一个字节
static unsigned char ReadOneChar(void)
{
unsigned char i=0;
unsigned char dat = 0;
for (i=8;i>0;i--)
 {
  DQ_1 = 0; // 给脉冲信号
  dat>>=1;
  DQ_1 = 1; // 给脉冲信号
  if(DQ_1)
  dat|=0x80;
  delay_18B20_1(5);
 }
 return(dat);
}
//写一个字节
static void WriteOneChar(unsigned char dat)
{
 unsigned char i=0;
 for (i=8; i>0; i--)
 {
  DQ_1 = 0;
  DQ_1 = dat&0x01;
  delay_18B20_1(5);
  DQ_1 = 1;
  dat>>=1;
 }
delay_18B20_1(5);
}
//读取温度
int ReadTemperature_1(void)
{
	int value;                  //存放温度数值
	unsigned int tmpvalue;		 //温度整合的中间辅助变量

	unsigned char a=0;			//存放温度低位
	unsigned char b=0;			//存放温度高位
	float t;

	Init_DS18B20();
	WriteOneChar(0xCC);       // 跳过读序号列号的操作
	WriteOneChar(0x44);       // 启动温度转换
	delay_18B20_1(100);
	Init_DS18B20();
	WriteOneChar(0xCC); //跳过读序号列号的操作 
	WriteOneChar(0xBE); //读取温度寄存器等（共可读9个寄存器） 前两个就是温度

	a=ReadOneChar();
	b=ReadOneChar();

	if((b&0xf8)==0xf8) //高字节的高5位为1时，温度为负
		{flag_fu1=1;}
	else
		{flag_fu1=0;}

    //将高低两个字节合成一个整形变量
    //计算机中对于负数是利用补码来表示的
    //若是负值, 读取出来的数值是用补码表示的, 可直接赋值给int型的value
    tmpvalue = b;
    tmpvalue <<= 8;
    tmpvalue |= a;
    value = tmpvalue;
	if(flag_fu1==1)  //温度为负值
	{
		value=(~value)+1; //取反再加1
	}
 

    t = value * 0.0625;
    value = t * 100 + (value > 0 ? 0.5 : -0.5); //大于0加0.5, 小于0减0.5
	
    return value;
}