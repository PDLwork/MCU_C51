#include <REGX52.H>
#include "UserDef.H"
#include "AT24C02.H"
#include "I2C.H"

/*******************************************************************************
* 函 数 名		: AT24C02_WriteByte （EEPROM写入函数）
* 函数功能		: 在输入地址上写入一个字节内容
* 输    入 		: WordAddress（写入字节地址 输入范围0~255）
				  Data（写入内容）
* 输    出		: 无
*******************************************************************************/
extern void AT24C02_WriteByte(INT8U WordAddress, Data)
{
	I2C_Start();
	I2C_SendByte(0xA0);
	I2C_ReceiveAck();
	I2C_SendByte(WordAddress);
	I2C_ReceiveAck();
	I2C_SendByte(Data);
	I2C_ReceiveAck();
	I2C_Stop();
}

/*******************************************************************************
* 函 数 名		: AT24C02_ReadByte（EEPROM读取函数）
* 函数功能		: 读取输入地址内的一个字节内容
* 输    入 		: WordAddress（读取地址 输入范围0~255）
* 输    出		: Data（读取内容）
*******************************************************************************/
extern INT8U AT24C02_ReadByte(INT8U WordAddress)
{
	INT8U Data;
	I2C_Start();
	I2C_SendByte(0xA0);
	I2C_ReceiveAck();
	I2C_SendByte(WordAddress);
	I2C_ReceiveAck();
	I2C_Start();
	I2C_SendByte(0xA1);
	I2C_ReceiveAck();
	Data = I2C_ReceiveByte();
	I2C_SendAck(1);
	I2C_Stop();
	return Data;
}	