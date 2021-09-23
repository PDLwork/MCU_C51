/*******************************************************************************
ʵ�ֹ��� ��	ͨ�������������ת�٣������������ʾ��λ
			����1���£��ٶ�����
			����2���£��ٶȼ���
			����3���£��ٶȹ���
			
���Ŷ��� ��	Motor	��	P2^2
			smg		��	P0
			Button	��	P1
*******************************************************************************/
	
#include <REGX52.H>
#include "UserDef.H"
#include "Timer.H"
#include "ButtonScan.H"

sbit Motor = P2^2;
#define smg P0

INT8U Compare;		//���ڱȽ����PWM���� (��ΧΪ0��100)
INT8S Speed;		//�ٶȵ�λ (��ΧΪ0��3 0������ 1��3���ٶ�������)
INT8U NixieTable[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};//��������ܴ����"0-F"(aΪ���λ)


/*******************************************************************************
* �� �� ��         :  main ����������
* ��������		   :  ����ѭ��ִ��
* ��    ��         :  ��
* ��    ��         :  ��
*******************************************************************************/
void main(void)
{
	Timer0_Initialization();
	Compare = 0;
	smg = NixieTable[Speed];
	while(1)
	{
		ButtonScan();		//����ɨ��
		
		if(Button_Value)	//ͨ�������ı��ٶ�ֵ
		{
			if(Button_Value == 1)
			{
				Speed++;
				if(Speed > 3)
					Speed = 3;
			}
			if(Button_Value == 2)
			{
				Speed--;
				if(Speed < 0)
					Speed = 0;
			}	
			if(Button_Value == 3)
				Speed = 0;
		}
		
		smg = NixieTable[Speed];		//��ʾ�ٶ�ֵ
		
		switch(Speed)		//�����ٶ�ֵѡ��Ƚ�ֵ�����Ӧ��PWM����
		{
			case(0): Compare = 0; 	break;
			case(1): Compare = 50; 	break;
			case(2): Compare = 75; 	break;
			case(3): Compare = 100; break;
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
	count %= 100;	//ʵ�ֳ���100����  ����ȡ��if�ж�  һ��PWM������Ϊ100*100us��10ms
	if(count < Compare)
		Motor = 1;
	else
		Motor = 0;
}