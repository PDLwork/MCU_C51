#include <REG52.H>
#include "UserDef.H"
#include "LCD1602.H"
#include "Delay.h"
#include "keyboard.h"									

/*******************************************************************************
* �� �� ��         : LCD_WriteCommand ��LCD1602д�������
* ��������		   : ΪLCDд������
* ��    ��         : LCD_Command ���������
* ��    ��         : ��
*******************************************************************************/
extern void LCD_WriteCommand(INT8U LCD_Command)  
{ 
     LCD_RS = 0;
     LCD_RW = 0;
     LCD_DataPort = LCD_Command;
     DelayXms(5);
     LCD_E = 1;
     DelayXms(5);
     LCD_E = 0;
}

/*******************************************************************************
* �� �� ��         : LCD_WriteData ��LCD1602д���ݺ�����
* ��������		   : ΪLCDд������
* ��    ��         : LCD_Data ���������ݣ�
* ��    ��         : ��
*******************************************************************************/
static void LCD_WriteData(INT8U LCD_Data)  
{ 
     LCD_RS = 1;
     LCD_RW = 0;
     LCD_DataPort = LCD_Data;
     DelayXms(5);
     LCD_E = 1;
     DelayXms(5);
     LCD_E = 0;
}

/*******************************************************************************
* �� �� ��         : LCD_Initialization ��LCD1602��ʼ��������
* ��������		   : Һ����ʾ���ǳ�ʼ������
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
extern void LCD_Initialization()   
{
    LCD_WriteCommand(0x01);	   //����
    LCD_WriteCommand(0x38);	   //������ʾ���С�ÿ���ַ�Ϊ5*7����������Ϊ8��
	LCD_WriteCommand(0x06);	   //������ַָ������
	LCD_WriteCommand(0x0c);	   //��ʾ�򿪡����ر�
}

/*******************************************************************************
* �� �� ��         : LCD_site ��LCDȷ����ʾλ�ú�����
* ��������		   : ��������ȷ����ʾλ��
* ��    ��         : Line����ʾ�����꣬��Χ��1��2��
					 Cloumn����ʾ�����꣬��Χ��1��16��
* ��    ��         : ��
*******************************************************************************/
extern void LCD_site(INT8U Line,INT8U Cloumn)
{
	if(Line == 1)
	{
		LCD_WriteCommand(0x80 + (Cloumn - 1));
	}
	if(Line == 2)
	{
		LCD_WriteCommand((0x80 + 0x40) + (Cloumn - 1));
	}

}

/*******************************************************************************
* �� �� ��         : LCD_ShowString ��LCD��ʾ�ַ���������
* ��������		   : ��������ʾλ�ÿ�ʼ��ʾ�ַ���
* ��    ��         : Line����ʾ�����꣬��Χ��1��2��
					 Cloumn����ʾ�����꣬��Χ��1��16��
					 String����ʾ�ַ�����
* ��    ��         : ��
*******************************************************************************/
extern void LCD_ShowString(INT8U Line,INT8U Cloumn,INT8S String[])
{
	INT8U i;
	LCD_site(Line,Cloumn);
	for(i=0; String[i] != '\0'; i++)
	{
		LCD_WriteData(String[i]);
	}
}

/*******************************************************************************
* �� �� ��         : LCD_ShowNumber ��LCD��ʾ���ֺ�����
* ��������		   : ��������ʾλ����ʾ����
* ��    ��         : Line����ʾ�����꣬��Χ��1��2��
					 Cloumn����ʾ�����꣬��Χ��1��16��
					 Number����ʾ���֣���Χ��1~65535��
* ��    ��         : ��
*******************************************************************************/
extern void LCD_ShowNumber(INT8U Line,INT8U Cloumn,INT16U Number)
{
	INT8U x, LCD_Number[4];
	LCD_site(Line,Cloumn);
	
	LCD_Number[0] = Number / 10000;                 //���ڴ����λ
	LCD_Number[1] = (Number % 10000) / 1000;		//���ڴ��ǧλ
	LCD_Number[2] = (Number % 1000) / 100;			//���ڴ�Ű�λ
	LCD_Number[3] = (Number % 100) / 10;			//���ڴ��ʮλ
	LCD_Number[4] = Number % 10;					//���ڴ�Ÿ�λ

	for(x = 0; x <= 4; x++)
	{
		if(LCD_Number[x] != 0)
			break;
	}
	for( ; x <= 4; x++)
	{
		LCD_WriteData('0' + LCD_Number[x]);
	}

}

/*******************************************************************************
* �� �� ��         : LCD_ShowNumber ��LCD��ʾ���ֺ�����
* ��������		   : ��������ʾλ����ʾ����
* ��    ��         : Line����ʾ�����꣬��Χ��1��2��
					 Cloumn����ʾ�����꣬��Χ��1��16��
					 Number����ʾ���֣���Χ��1~65535��
* ��    ��         : ��
*******************************************************************************/
extern void LCD_ShowChar(INT8U Line,INT8U Cloumn,INT8U LCD_Char)
{
	LCD_site(Line,Cloumn);
	LCD_WriteData(LCD_Char);
}