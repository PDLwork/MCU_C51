#include <REGX52.H>
#include "UserDef.H"
#include "OneWire.H"

extern bit OneWire_Initialization(void)
{
	bit AckBit;
	INT8U i;
	OneWire_DQ = 1;			//��DQ����������  ��ʼ��
	OneWire_DQ = 0;
    i = 248; while (--i);	//��ʱ500us������480us��
	OneWire_DQ = 1;			//�ͷ�DQ
	i = 33; while (--i);    //��ʱ70us ������60 С��300��
	AckBit = OneWire_DQ;	//���ӻ��Ƿ�Ӧ��
	i = 123; while (--i);	//��ʱ250us ������300 - 70���ȴ��ӻ��ͷ�����
	return AckBit;
}

static void OneWire_SendBit(bit SendBit)
{
	INT8U i;
	OneWire_DQ = 0;
	i = 3; while (--i);		//��ʱ10us  ��1~15us��
	OneWire_DQ = SendBit;	//Ϊ0��һֱ���ͣ�Ϊ1���ͷ����ߣ����ɷ���
	i = 25; while (--i);	//��ʱ55us  ������������60����120us��
	OneWire_DQ = 1;			//�ͷ����� ��ֹ0ʱһֱ����
}

static bit OneWire_ReceiveBit(void)
{
	bit ReceiveBit;
	INT8U i;
	OneWire_DQ = 0;			//����������
	i = 2; while (--i);		//��ʱ5us
	OneWire_DQ = 1;			//�������ͷ�
	i = 2; while (--i);		//��ʱ5us
	ReceiveBit = OneWire_DQ;	//��ȡDQֵ
	i = 25; while (--i);	//��ʱ55us  ������������60����120us��
	return ReceiveBit;      //���ﲻ��Ҫ�ͷ����ߣ���Ϊ����18B20���ͷ�����
}

extern void OneWire_SendByte(INT8U SendByte)
{
	INT8U i;
	for(i = 0; i < 8; i++)
	{
		OneWire_SendBit(SendByte & (0x01 << i));	//�ӵ�λ��ʼд
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