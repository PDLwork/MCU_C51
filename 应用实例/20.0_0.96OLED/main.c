#include <REGX52.H>
#include "UserDef.H"
#include "Oled.H"

/*******************************************************************************
* �� �� ��         :  main ����������
* ��������		   :  ����ѭ��ִ��
* ��    ��         :  ��
* ��    ��         :  ��
*******************************************************************************/
void main(void)
{
	Oled_Initialization();
	Oled_Clear();
	Oled_ShowChar(50, 0, 'A', MediumSize);
	Oled_ShowString(0, 2, "Hello World !!! Hello World !!! Hello World !!! ", MediumSize);
	Oled_Test();while(1)
	{
		
	}
}