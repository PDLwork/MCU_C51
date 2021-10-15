#include <REGX52.H>
#include "UserDef.H"
#include "Uart.H"

sbit Motor = P2^2;		
INT8U State = 3;		//0关， 1开 , 3不控制

void Delay19ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 35;
	j = 13;
	do
	{
		while (--j);
	} while (--i);
}

void Delay1450us()		//@11.0592MHz
{
	unsigned char i, j;

	i = 3;
	j = 150;
	do
	{
		while (--j);
	} while (--i);
}

void Delay1800us()		//@11.0592MHz
{
	unsigned char i, j;

	i = 4;
	j = 54;
	do
	{
		while (--j);
	} while (--i);
}

void Delay18ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 33;
	j = 66;
	do
	{
		while (--j);
	} while (--i);
}


/*******************************************************************************
* 函 数 名         :  main函数
* 函数功能		   :  主程循环执行
* 输    入         :  无
* 输    出         :  无
*******************************************************************************/
void main(void)
{
	INT16U count = 0;
	Uart_Initialization();
	while(1)
	{
		if(State == 0)	//关
		{
			ES = 0;		//关闭串口中断
			for(count = 0; count < 100; count++)
			{
				Motor = 1;
				Delay1800us();
				Motor = 0;
				Delay18ms();
			}
			State = 3;
			ES = 1;		//打开串口中断
		}
		if(State == 1)	//开
		{
			ES = 0;		//关闭串口中断
			for(count = 0; count < 100; count++)
			{
				Motor = 1;
				Delay1450us();
				Motor = 0;
				Delay18ms();
			}
			State = 3;
			ES = 1;		//打开串口中断
		}
		if(State == 3)
			Motor = 0;
	}
}

/*******************************************************************************
* 函 数 名		: Uart_Routine 串口中断函数
* 函数功能		: 发送完或接收到数据时执行相应操作
* 输    入 		: 无
* 输    出		: 无
*******************************************************************************/
void Uart_Routine() interrupt 4
{
	if(TI == 1)
	{
		TI = 0;
	}
	if(RI == 1)
	{
		RI = 0;
		Uart_SendByte(SBUF);
		if(SBUF == 'A')
			State = 1;
		if(SBUF == 'B')
			State = 0;
	}
}