#include <REGX52.H>
#include "userdef.h"
#include "LCD1602.h"

/*******************************************************************************
* �� �� ��         :  DelayXms 
* ��������		   :  ��ʱXms 	   ����Ϊ12MHz 
* ��    ��         :  X:��ʱ������
* ��    ��         :  ��
*******************************************************************************/
static void DelayXms(INT16U xms)	
{
	INT8U i, j; 
	while(--xms)
	{
	i = 2;
	j = 238;
		do
		{
			while (--j);
		} 
		while (--i);
	}
}

/*******************************************************************************
* �� �� ��         :LCD_writecommand 
* ��������		   :1602д�������
* ��    ��         :LCD_command(�������)
* ��    ��         :��
*******************************************************************************/

static void LCD_writeCommand(INT8U LCD_command)
{

	LCD_RS = 0;
	LCD_RW = 0;

	DelayXms(1);

	LCD_DataPort = LCD_command;
	LCD_E = 1;

	DelayXms(5);

	LCD_E = 0;

	DelayXms(5);

}

/*******************************************************************************
* �� �� ��         :LCD_writeData 
* ��������		   :1602д���ݲ���
* ��    ��         :LCD_data(��������)
* ��    ��         :��
*******************************************************************************/

static void LCD_writeData(INT8U LCD_data)
{

	LCD_RS = 1;
	LCD_RW = 0;
	
	DelayXms(1);
	
	LCD_DataPort = LCD_data;
	LCD_E = 1;

	DelayXms(5);

	LCD_E = 0;

	DelayXms(5);

}

/*******************************************************************************
* �� �� ��         :LCD_Initialization 
* ��������		   :1602��ʾ��ʼ�� 
* ��    ��         :��
* ��    ��         :��
*******************************************************************************/

extern void LCD_Initialization()
{
	LCD_writeCommand(0X01);//��ʾ����
	LCD_writeCommand(0X38);//16*2��ʾ��5*7���󣬰�λ���ݽӿ�
  	LCD_writeCommand(0X0C);//��ʾ�򿪣����ر�
	LCD_writeCommand(0X06);//д����ַ��һ����ʾ�����ƶ�
}

/*******************************************************************************
* �� �� ��         :LCD_site
* ��������		   :ȷ����ʾλ�� 
* ��    ��         :Line(�У���Χ��1~2)
				    Column(�У���Χ��1~16) 
* ��    ��         :�� 
*******************************************************************************/

static void LCD_site(INT8U Line, INT8U Column)
{

	if(Line == 1)
	{

		LCD_writeCommand(0X80 + (Column - 1));	
	
	}

	if(Line == 2)
	{
	
		LCD_writeCommand((0X80 + 0X40) + (Column - 1));
	
	}	

}

/*******************************************************************************
* �� �� ��         :LCD_ShowString
* ��������		   :��ʾ�ַ���
* ��    ��         :Line(�У���Χ��1~2)
				    Column(�У���Χ��1~16)
				    String[](����ַ���) 
* ��    ��         :�� 
*******************************************************************************/

extern void LCD_ShowString(INT8U Line, INT8U Column, INT8U String[])
{

	unsigned char i;	

	LCD_site(Line, Column);

	for(i = 0; String[i] != '\0'; i++)
	{
	
		LCD_writeData(String[i]);
	
	}

}

/*******************************************************************************
* �� �� ��         :LCD_ShowChar
* ��������		   :��ʾ�ַ�
* ��    ��         :Line(�У���Χ��1~2)
				    Column(�У���Χ��1~16)
				    LCD_char(����ַ�) 
* ��    ��         :�� 
*******************************************************************************/

extern void LCD_ShowChar(INT8U Line, INT8U Column, INT8U LCD_char)
{

	LCD_site(Line, Column);
	
	LCD_writeData(LCD_char);	

}

/*******************************************************************************
* �� �� ��         :LCD_ShowNumber 
* ��������		   :��ʾ���� 
* ��    ��         :Line(�У���Χ��1~2)
				    Column(�У���Χ��1~16)
				    LCD_number(�������, ��Χ��0~65535)
* ��    ��         :�� 
*******************************************************************************/

extern void LCD_ShowNumber(INT8U Line, INT8U Column, unsigned int LCD_number)
{

	char number[4];

	LCD_site(Line, Column);
	
	number[4] = LCD_number / 10000;
	
	number[3] = (LCD_number % 10000) / 1000;
	
	number[2] = (LCD_number % 1000) / 100;

	number[1] = (LCD_number % 100) / 10;

	number[0] = LCD_number % 10;
	

	LCD_writeData(number[4] + '0');
	LCD_writeData(number[3] + '0');
	LCD_writeData(number[2] + '0');
	LCD_writeData(number[1] + '0');
	LCD_writeData(number[0] + '0');

}