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
	Oled_ShowChar(5, 1, 'A');
	Oled_Test();
	Oled_ShowString(0, 7, "Hello World !!! ");
	while(1)
	{
		
	}
}