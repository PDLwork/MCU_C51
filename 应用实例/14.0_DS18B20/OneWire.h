#ifndef __OneWire_H__
#define	__OneWire_H__

//引脚定义
sbit OneWire_DQ = P2^2;

//外部调用
extern bit OneWire_Initialization();
extern void OneWire_SendByte(INT8U SendByte);
extern INT8U OneWire_ReceiveByte();
	
#endif