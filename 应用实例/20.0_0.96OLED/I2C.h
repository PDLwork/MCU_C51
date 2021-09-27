#ifndef __I2C_H__
#define	__I2C_H__

//引脚定义
sbit I2C_SCL = P2^1;
sbit I2C_SDA = P2^0;

//外部调用函数
extern void I2C_Start();
extern void I2C_Stop();
extern void I2C_SendByte(INT8U Byte);
extern INT8U I2C_ReceiveByte();
extern void I2C_SendAck(bit AckBit);
extern bit I2C_ReceiveAck();

#endif