#include <REGX52.H>
#include "UserDef.H"
#include "Timer.H"

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