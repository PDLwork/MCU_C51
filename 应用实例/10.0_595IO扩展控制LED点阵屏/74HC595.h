#ifndef __74HC595_H__
#define	__74HC595_H__

//引脚配置：
sbit _595_RCLK = P1^0;
sbit _595_SRCLK = P1^1;	
sbit _595_SER = P1^2;

//外部调用：
extern void _74HC595_Initialization();
extern void MatrixLED_ShowOneColumn(INT8U Show_Column, INT8U Show_Data);
extern void _74HC595_SendByte1(INT8U _595_Byte);

#endif