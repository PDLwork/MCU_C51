#include <REGX52.H>
#include "UserDef.H"
#include "OneWire.H"

extern bit OneWire_Initialization(void)
{
	bit AckBit;
	INT8U i;
	OneWire_DQ = 1;			//将DQ拉高在拉低  初始化
	OneWire_DQ = 0;
    i = 248; while (--i);	//延时500us（大于480us）
	OneWire_DQ = 1;			//释放DQ
	i = 33; while (--i);    //延时70us （大于60 小于300）
	AckBit = OneWire_DQ;	//检测从机是否应答
	i = 123; while (--i);	//延时250us （大于300 - 70）等待从机释放总线
	return AckBit;
}

static void OneWire_SendBit(bit SendBit)
{
	INT8U i;
	OneWire_DQ = 0;
	i = 3; while (--i);		//延时10us  （1~15us）
	OneWire_DQ = SendBit;	//为0则一直拉低，为1则释放总线，即可发送
	i = 25; while (--i);	//延时55us  （加起来超过60少于120us）
	OneWire_DQ = 1;			//释放总线 防止0时一直拉低
}

static bit OneWire_ReceiveBit(void)
{
	bit ReceiveBit;
	INT8U i;
	OneWire_DQ = 0;			//将总线拉低
	i = 2; while (--i);		//延时5us
	OneWire_DQ = 1;			//将总线释放
	i = 2; while (--i);		//延时5us
	ReceiveBit = OneWire_DQ;	//读取DQ值
	i = 25; while (--i);	//延时55us  （加起来超过60少于120us）
	return ReceiveBit;      //这里不需要释放总线，因为最终18B20会释放总线
}

extern void OneWire_SendByte(INT8U SendByte)
{
	INT8U i;
	for(i = 0; i < 8; i++)
	{
		OneWire_SendBit(SendByte & (0x01 << i));	//从低位开始写
	}
}

extern INT8U OneWire_ReceiveByte(void)
{
	INT8U i, ReceiveByte = 0x00;
	for(i = 0; i < 8; i++)
	{
		if(OneWire_ReceiveBit())
			ReceiveByte |= (0x01 << i);
	}
	return ReceiveByte;
}