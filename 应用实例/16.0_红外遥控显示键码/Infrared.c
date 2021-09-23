#include <REGX52.H>
#include "UserDef.H"
#include "Timer.H"
#include "Int.H"
#include "Infrared.H"

bit Infrared_RepeatFlag, Infrared_DataFlag;
INT8U Infrared_Command, Infrared_Address;

extern void Infrared_Initialization(void)
{
	Int0_Initialization();
	Timer0_Initialization();
}

void Int0_Routine(void) interrupt 0
{
	INT16U Time_Length;
	static INT8U DataBit_Site = 0, Infrared_Data[] = {0, 0, 0, 0};
	static INT8U Infrared_State = 0;
	
	switch(Infrared_State)
	{
		case 0:
			Timer0_Run();
			Infrared_State = 1;
			break;
		
		case 1:
			Time_Length = Timer0_GetCounter();
			if( (Time_Length > (13500 - 500))  &&  (Time_Length < (13500 + 500)) )		//���㿪ʼ����
			{
				Infrared_State = 2;		//����Ϊ��ʼ����ģʽ �¸��½��ؼ���ʼ��������
				Timer0_Run();
			}
			else if( (Time_Length > (11250 - 500))  &&  (Time_Length < (11250 + 500)) )	//�����ظ���������
			{
				Infrared_RepeatFlag = 1;
				Infrared_State = 0;
			}
			else
				Infrared_State = 0;		//�����㿪ʼ���ظ���������ģʽ��������Ϊ0
			break;
			
		case 2:
			Time_Length = Timer0_GetCounter();
			Timer0_Run();

			if( (Time_Length > (1120 - 500))  &&  (Time_Length < (1120 + 500)) )		//���ⷢ��0
			{
				Infrared_Data[DataBit_Site / 8] &= ~(0x01 << (DataBit_Site % 8));
				DataBit_Site++;
			}
			else if( (Time_Length > (2250 - 500))  &&  (Time_Length < (2250 + 500)) )		//���ⷢ��1
			{
				Infrared_Data[DataBit_Site / 8] |= (0x01 << (DataBit_Site % 8));
				DataBit_Site++;
			}
			else
			{
				DataBit_Site = 0; 
				Infrared_State = 0;		//�����㷢0�ͷ�1����������ģʽ��������Ϊ0
			}
			
			if(DataBit_Site >= 32)
			{
				if((Infrared_Data[0] == ~Infrared_Data[1])  &&  (Infrared_Data[2] == ~Infrared_Data[3])) 
				{
					Infrared_RepeatFlag = 1;
					Infrared_Address = Infrared_Data[0];
					Infrared_Command = Infrared_Data[2];
				}
				DataBit_Site = 0;
				Infrared_State = 0;		//������32Ϊ���ݣ���ģʽ��������Ϊ0
			}
			
			break;
	}
}

void Timer0_Routine() interrupt 1
{
	TR0 = 0;	//������֮��رռ���������ֹ���ŵ��³�������ж�
}