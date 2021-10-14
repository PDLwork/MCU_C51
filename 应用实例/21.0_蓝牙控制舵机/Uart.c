#include <REGX52.H>
#include "UserDef.H"
#include "Uart.H"
#include "Oled.H"

/*******************************************************************************
* 函 数 名		: Uart_Initialization 串口通讯函数初始化
* 函数功能		: 配置串口通讯寄存器
* 输    入 		: 无
* 输    出		: 无
*******************************************************************************/
extern void Uart_Initialization(void)		//9600bps@11.0592MHz
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

