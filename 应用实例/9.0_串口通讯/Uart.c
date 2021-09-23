#include <REGX52.H>
#include "UserDef.H"
#include "Uart.h"
#include "Delay.h"
#include "LCD1602.H"

/*******************************************************************************
* 函 数 名		: Uart_Initialization 串口通讯函数初始化
* 函数功能		: 配置串口通讯寄存器
* 输    入 		: 无
* 输    出		: 无
*******************************************************************************/
extern void Uart_Initialization(void)
{
	
	PCON &= 0x7F;		//波特率不倍速				/*9600bps@11.0592MHz*/
	SCON = 0x50;		//8位数据,可变波特率
	TMOD &= 0x0F;		//与或赋值法配置模式
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xFD;		//设定定时初值
	TH1 = 0xFD;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
	EA = 1;			//打开总中断
	ES = 1;		//打开串口中断
	
//	PCON |= 0x80;		//使能波特率倍速位SMOD		/*4800bps@12.000MHz*/
//	SCON = 0x50;		//8位数据,可变波特率
//	TMOD &= 0x0F;		//清除定时器1模式位
//	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
//	TL1 = 0xF3;		//设定定时初值
//	TH1 = 0xF3;		//设定定时器重装值
//	ET1 = 0;		//禁止定时器1中断
//	TR1 = 1;		//启动定时器1
//	EA = 1;			//打开总中断
//	ES = 1;		//打开串口中断
	
}

/*******************************************************************************
* 函 数 名		: Uart_SendByte  串口发送字节函数
* 函数功能		: 单片机向外发送一个字节
* 输    入 		: Byte（输出字节内容）
* 输    出		: 无
*******************************************************************************/
extern void Uart_SendByte(INT8U Byte)
{
	SBUF = Byte;
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
		LCD_ShowChar(2, 1, SBUF);
		RI = 0;
	}
}

extern void Uart_SendString(INT8U Uart_String[])
{
	INT8U i;
	for(i=0; Uart_String[i] != '\0'; i++)
	{
		SBUF = Uart_String[i];
		DelayXms(2);
	}
}