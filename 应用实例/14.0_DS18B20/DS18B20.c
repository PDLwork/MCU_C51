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
	OneWire_SendByte(DS18B20_SKIP_ROM);		//跳过匹配ROM
	OneWire_SendByte(DS18B20_CONVERT);		//转换温度
}

extern float DS18B20_ReadTemperature(void)
{
	INT8U TLSB, TMSB;
	INT16S TemporaryTemperature;
	float DS18B20_Temperature;
	OneWire_Initialization();
	OneWire_SendByte(DS18B20_SKIP_ROM);		//跳过匹配ROM
	OneWire_SendByte(DS18B20_READ_SCRATHPAD);	//读取温度命令
	TLSB = OneWire_ReceiveByte();  //先读取低8位
	TMSB = OneWire_ReceiveByte();  //再读取低8位
	TemporaryTemperature = (TMSB << 8) | TLSB;
	DS18B20_Temperature = TemporaryTemperature / 16.0;  //除16会丢失精度
	return DS18B20_Temperature;
}