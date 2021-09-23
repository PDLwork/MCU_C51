#ifndef __74HC595_H__
#define	__74HC595_H__

//引脚配置：
sbit _595_RCLK = P1^0;
sbit _595_SRCLK = P1^1;	
sbit _595_SER = P1^2;

//外部调用：
extern void _74HC595_Initialization();
extern void _74HC595_SendByte(INT8U amount, _595_Byte1, _595_Byte2, _595_Byte3);

#endif