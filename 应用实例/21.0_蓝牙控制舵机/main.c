#include <REGX52.H>
#include "UserDef.H"
#include "Uart.H"
#include "Oled.H"
#include "Timer.H"

sbit Motor = P2^2;		
INT8U Compare = 7;		//7-90  27 -90

/*******************************************************************************
* �� �� ��         :  main����
* ��������		   :  ����ѭ��ִ��
* ��    ��         :  ��
* ��    ��         :  ��
*******************************************************************************/
void main(void)
{
	Oled_Initialization();
	Oled_Clear();
	Uart_Initialization();
	Timer0_Initialization();
	Oled_ShowString(0, 2, "Hello World !!! ", MediumSize);
	while(1)
	{
		
	}
}

/*******************************************************************************
* �� �� ��         : Timer_Routine ��ʱ��������
* ��������		   : ��ʱ����ʱһ��ʱ��ִ������
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void Timer0_Routine() interrupt 1
{
	static INT8U count;
	TL0 = 0x9C;		//���ö�ʱ��ʼֵ100΢�� 
	TH0 = 0xFF;
    count++;
	count %= 200;	//ʵ�ֳ���100����  ����ȡ��if�ж�  һ��PWM������Ϊ200*0.1ms��20ms
	if(count < Compare)
		Motor = 1;
	else
		Motor = 0;
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
			Compare = 15;
		if(SBUF == 'B')
			Compare = 11;
	}
}