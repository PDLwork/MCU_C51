#include <REGX52.H>
#include "UserDef.H"
#include "Timer.H"

INT8U Compare;

/*******************************************************************************
* �� �� ��         : Timer0_Initialization ��ʱ����ʼ������
* ��������		   : ��ʱ����ʼ�����ã�1����@12.000MHz��
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
extern void Timer0_Initialization(void)
{
	EA = 1;  		//���жϴ�
	ET0 = 1; 		//��ʱ��0��
	TMOD &= 0xF0;	//���ֵ
	TMOD |= 0x01;	//���ö�ʱ��ģʽ1
	TF0 = 0;		//���TF0��־
//	TR0 = 1;		//��ʱ��0��ʼ��ʱ
}

extern void Timer0_Run(void)
{
	TL0 = 0;		
	TH0 = 0;
	TR0 = 1;		//������ֵ�����ʼ��ʱ
}

extern INT16U Timer0_GetCounter(void)
{
	INT16U GetCounter;
	TR0 = 0;		//����ʱ��ֹͣ���ȡ����ֵ
	GetCounter = (TH0 << 8) | TL0;
	return GetCounter;
}

extern void Timer1_Initialization(void)
{
	EA = 1;  		//���жϴ�
	ET1 = 1; 		//��ʱ��0��
	TMOD &= 0x0F;	//���ֵ
	TMOD |= 0x10;	//���ö�ʱ��ģʽ1
	TL1 = 0x9C;		//���ö�ʱ��ʼֵ100΢�� 
	TH1 = 0xFF;
	TF1 = 0;		//���TF0��־
	TR1 = 1;		//��ʱ��0��ʼ��ʱ
}

void Timer1_Routine() interrupt 3
{
	static INT8U count;
	TL1 = 0x9C;		//���ö�ʱ��ʼֵ100΢�� 
	TH1 = 0xFF;
    count++;
	count %= 100;	//ʵ�ֳ���100����  ����ȡ��if�ж�  һ��PWM������Ϊ100*100us��10ms
	if(count < Compare)
		Motor = 1;
	else
		Motor = 0;
}