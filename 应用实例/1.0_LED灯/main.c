#include <REGX52.H>
#include "UserDef.H"
#include "Delay.H"
#include "Intrins.H"

#define LED P2

/*******************************************************************************
* �� �� ��         :  main������
* ��������		   :  ִ�г�ʼ��������ѭ������ 
* ��    ��         :  ��
* ��    ��         :  ��
*******************************************************************************/
//void main(void)   //IO��ֱ�ӿ��Ƶ�
//{
//	while(1)
//	{
//		LED = 0XA3;
//	}
//}

//void main(void)   //��ʱ��˸LED
//{
//	while(1)
//	{
//		LED = 0XAA;
//		DelayXms(300);
//		LED = 0X55;
//		DelayXms(300);
//	}
//}

void main(void)   //ѭ����λ��ˮ��
{
	LED = 0X8F;
	while(1)
	{
		DelayXms(100);
//		LED = _crol_(LED,1);
		LED = _cror_(LED,1);
	}
}