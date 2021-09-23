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
			if( (Time_Length > (13500 - 500))  &&  (Time_Length < (13500 + 500)) )		//满足开始条件
			{
				Infrared_State = 2;		//设置为开始接收模式 下个下降沿即开始接收数据
				Timer0_Run();
			}
			else if( (Time_Length > (11250 - 500))  &&  (Time_Length < (11250 + 500)) )	//满足重复发送条件
			{
				Infrared_RepeatFlag = 1;
				Infrared_State = 0;
			}
			else
				Infrared_State = 0;		//不满足开始和重复条件，将模式重新设置为0
			break;
			
		case 2:
			Time_Length = Timer0_GetCounter();
			Timer0_Run();

			if( (Time_Length > (1120 - 500))  &&  (Time_Length < (1120 + 500)) )		//红外发送0
			{
				Infrared_Data[DataBit_Site / 8] &= ~(0x01 << (DataBit_Site % 8));
				DataBit_Site++;
			}
			else if( (Time_Length > (2250 - 500))  &&  (Time_Length < (2250 + 500)) )		//红外发送1
			{
				Infrared_Data[DataBit_Site / 8] |= (0x01 << (DataBit_Site % 8));
				DataBit_Site++;
			}
			else
			{
				DataBit_Site = 0; 
				Infrared_State = 0;		//不满足发0和发1的条件，将模式重新设置为0
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
				Infrared_State = 0;		//传输完32为数据，将模式重新设置为0
			}
			
			break;
	}
}

void Timer0_Routine() interrupt 1
{
	TR0 = 0;	//计数满之后关闭计数器，防止干扰导致程序进入中断
}