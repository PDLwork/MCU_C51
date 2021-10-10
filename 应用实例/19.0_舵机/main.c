/*******************************************************************************
ʵ�ֹ��� ��	�ö����������̿��ƶ����ת��һ���ĽǶ�
			�������PWM�����Ƶ�
			PWM����ͨ����ʱ���㶨ʱ��ֵ��Ƚ�ֵ�Ƚ�ʵ�ֵ�
���Ŷ��� ��	��������	��	P1
			����ź���	��	P2^2
*******************************************************************************/

#include <REGX52.H>
#include "UserDef.H"
#include "Timer.H"
#include "ButtonScan.H"
				
sbit Motor = P2^2;		
INT8U Compare = 7;		//7-90  27 -90

/*******************************************************************************
* �� �� ��         :  main ����������
* ��������		   :  ����ѭ��ִ��
* ��    ��         :  ��
* ��    ��         :  ��
*******************************************************************************/
void main(void)
{
	Timer0_Initialization();
	while(1)
	{
		ButtonScan();
		if(Button_Value != 0)
		{
			switch(Button_Value)
			{
				case 1:	Compare = 7;	break;
				case 2:	Compare = 10; 	break;
				case 3:	Compare = 13; 	break;
				case 4:	Compare = 15; 	break;
				case 5:	Compare = 18; 	break;
				case 6:	Compare = 21;	break;
				case 7:	Compare = 24; 	break;
				case 8:	Compare = 27; 	break;
			}
		}
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