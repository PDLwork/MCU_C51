#include <REGX52.H>
#include "UserDef.H"
#include "OneWire.H"
#include "DS18B20.H"

#define DS18B20_SKIP_ROM		0xCC
#define DS18B20_CONVERT			0x44
#define DS18B20_READ_SCRATHPAD	0xBE

extern void DS18B20_ConverTemperature(void)
{
	OneWire_Initialization();
	OneWire_SendByte(DS18B20_SKIP_ROM);		//����ƥ��ROM
	OneWire_SendByte(DS18B20_CONVERT);		//ת���¶�
}

extern float DS18B20_ReadTemperature(void)
{
	INT8U TLSB, TMSB;
	INT16S TemporaryTemperature;
	float DS18B20_Temperature;
	OneWire_Initialization();
	OneWire_SendByte(DS18B20_SKIP_ROM);		//����ƥ��ROM
	OneWire_SendByte(DS18B20_READ_SCRATHPAD);	//��ȡ�¶�����
	TLSB = OneWire_ReceiveByte();  //�ȶ�ȡ��8λ
	TMSB = OneWire_ReceiveByte();  //�ٶ�ȡ��8λ
	TemporaryTemperature = (TMSB << 8) | TLSB;
	DS18B20_Temperature = TemporaryTemperature / 16.0;  //��16�ᶪʧ����
	return DS18B20_Temperature;
}