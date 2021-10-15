#include <REGX52.H>
#include "UserDef.H"
#include "Uart.H"

sbit Motor = P2^2;		
INT8U State = 3;		//0�أ� 1�� , 3������

void Delay19ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 35;
	j = 13;
	do
	{
		while (--j);
	} while (--i);
}

void Delay1450us()		//@11.0592MHz
{
	unsigned char i, j;

	i = 3;
	j = 150;
	do
	{
		while (--j);
	} while (--i);
}

void Delay1800us()		//@11.0592MHz
{
	unsigned char i, j;

	i = 4;
	j = 54;
	do
	{
		while (--j);
	} while (--i);
}

void Delay18ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 33;
	j = 66;
	do
	{
		while (--j);
	} while (--i);
}


/*******************************************************************************
* �� �� ��         :  main����
* ��������		   :  ����ѭ��ִ��
* ��    ��         :  ��
* ��    ��         :  ��
*******************************************************************************/
void main(void)
{
	INT16U count = 0;
	Uart_Initialization();
	while(1)
	{
		if(State == 0)	//��
		{
			ES = 0;		//�رմ����ж�
			for(count = 0; count < 100; count++)
			{
				Motor = 1;
				Delay1800us();
				Motor = 0;
				Delay18ms();
			}
			State = 3;
			ES = 1;		//�򿪴����ж�
		}
		if(State == 1)	//��
		{
			ES = 0;		//�رմ����ж�
			for(count = 0; count < 100; count++)
			{
				Motor = 1;
				Delay1450us();
				Motor = 0;
				Delay18ms();
			}
			State = 3;
			ES = 1;		//�򿪴����ж�
		}
		if(State == 3)
			Motor = 0;
	}
}

/*******************************************************************************
* �� �� ��		: Uart_Routine �����жϺ���
* ��������		: ���������յ�����ʱִ����Ӧ����
* ��    �� 		: ��
* ��    ��		: ��
*******************************************************************************/
void Uart_Routine() interrupt 4
{
	if(TI == 1)
	{
		TI = 0;
	}
	if(RI == 1)
	{
		RI = 0;
		Uart_SendByte(SBUF);
		if(SBUF == 'A')
			State = 1;
		if(SBUF == 'B')
			State = 0;
	}
}