#include <REGX52.H>
#include "UserDef.H"
#include "ButtonScan.H"

#define smg P0

INT8U NixieTable[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};//共阳数码管代码表"0-F"(a为最低位)

/*******************************************************************************
* 函 数 名         :  main主函数
* 函数功能		   :  按键控制数码管数字加减，带重置功能 
* 输    入         :  无
* 输    出         :  无
*******************************************************************************/
void main(void)
{
	INT8S Number = 0;
	while(1)
	{
		ButtonScan();
		
		if(Button_Value != 0)
		{
			if(Button_Value == 1)
			{
				Number++;
				if(Number > 9)
				{
					Number = 0;
				}
			}
			
			if(Button_Value == 2)
			{
				Number--;
				if(Number < 0)
				{
					Number = 9;
				}
			}
		}
		
		smg = NixieTable[Number];
	}
}