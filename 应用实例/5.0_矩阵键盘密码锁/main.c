#include <REG52.H>
#include "UserDef.H"
#include "LCD1602.H"
#include "keyboard.h"

INT8U Actualkeyboard, site;
INT8S Input[6];

void Initialization()
{
	site = 0;
    LCD_Initialization();
	LCD_ShowString(1, 1, "PassWord:");
	LCD_site(1, 11);
	LCD_WriteCommand(0X0D);      //设置光标闪烁	
}

/*******************************************************************************
* 函 数 名         :  main （主函数）
* 函数功能		   :  主程循环执行
* 输    入         :  无
* 输    出         :  无
*******************************************************************************/
void main(void)
{
	Initialization();
	while(1)
	{
		KeyboardScan();
		if(KeyboardValue != 0)
		{
			switch(KeyboardValue)
			{
				case(1) : 
					Actualkeyboard = 1; 
					break;
				case(2) : 
					Actualkeyboard = 2; 
					break;
				case(3) : 
					Actualkeyboard = 3; 
					break;
				case(5) : 
					Actualkeyboard = 4; 
					break;
				case(6) : 
					Actualkeyboard = 5; 
					break;
				case(7) : 
					Actualkeyboard = 6; 
					break;
				case(9) : 
					Actualkeyboard = 7; 
					break;
				case(10): 
					Actualkeyboard = 8; 
				break;
				case(11): 
					Actualkeyboard = 9; 
					break;
				case(14): 
					Actualkeyboard = 0; 
					break;
				case(13):
					site--;
					Actualkeyboard = 10;
					break;
				case(15):
					site++;
					Actualkeyboard = 11;
					break;
				case(16): 
					Actualkeyboard = 12; 
					break;
				case(12):
					Initialization();
					break;
			}
			if(Actualkeyboard <= 9)
			{
				Input[site] = Actualkeyboard;
				LCD_ShowChar(1, site + 11, ('0' + Input[site]));
				if(site < 5)
					site++;
			}
			LCD_site(1, site + 11);
			if(Actualkeyboard == 12)
			{
				INT8U x, flag = 0;
				INT8S PassWord[6] = {6, 7, 8, 0, 1, 2};
				for(x = 0; x <= 5; x++)
				{
					if(Input[x] != PassWord[x])
						flag = 1;
				}
				if(flag == 0)
					LCD_ShowString(2, 1, "Welcome!");
				if(flag == 1)
					LCD_ShowString(2, 1, "Error!  ");	
			}
		}
	}
}