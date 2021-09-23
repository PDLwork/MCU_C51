#include <REGX52.H>
#include "UserDef.H"
#include "AT24C02.H"
#include "I2C.H"

/*******************************************************************************
* �� �� ��		: AT24C02_WriteByte ��EEPROMд�뺯����
* ��������		: �������ַ��д��һ���ֽ�����
* ��    �� 		: WordAddress��д���ֽڵ�ַ ���뷶Χ0~255��
				  Data��д�����ݣ�
* ��    ��		: ��
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
* �� �� ��		: AT24C02_ReadByte��EEPROM��ȡ������
* ��������		: ��ȡ�����ַ�ڵ�һ���ֽ�����
* ��    �� 		: WordAddress����ȡ��ַ ���뷶Χ0~255��
* ��    ��		: Data����ȡ���ݣ�
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