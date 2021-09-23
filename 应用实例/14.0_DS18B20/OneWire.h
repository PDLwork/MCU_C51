#ifndef __OneWire_H__
#define	__OneWire_H__

//���Ŷ���
sbit OneWire_DQ = P2^2;

//�ⲿ����
extern bit OneWire_Initialization();
extern void OneWire_SendByte(INT8U SendByte);
extern INT8U OneWire_ReceiveByte();
	
#endif