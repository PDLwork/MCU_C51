#include <REGX52.H>
#include "UserDef.H"
#include "LCD1602.H"
#include "Delay.H"

/*******************************************************************************
* �� �� ��         : LCD_WriteCommand ��LCD1602д�������
* ��������		   : ΪLCDд������
* ��    ��         : LCD_Command ���������
* ��    ��         : ��
*******************************************************************************/
static void LCD_WriteCommand(INT8U LCD_Command)  
{ 
     LCD_RS = 0;
     LCD_RW = 0;
     LCD_DataPort = LCD_Command;
     LCD_E = 1;
     DelayXms(3);
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
     LCD_E = 1;
     DelayXms(3);
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
static void LCD_site(INT8U Line,INT8U Column)
{
	if(Line == 1)
	{
		LCD_WriteCommand(0x80 + (Column - 1));
	}
	if(Line == 2)
	{
		LCD_WriteCommand((0x80 + 0x40) + (Column - 1));
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
extern void LCD_ShowString(INT8U Line,INT8U Column,INT8S String[])
{
	INT8U i;
	LCD_site(Line,Column);
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
					 Length(��ʾ���ȣ���ΧΪ1~5)
* ��    ��         : ��
*******************************************************************************/
extern void LCD_ShowNumber(INT8U Line,INT8U Column,INT16U Number, INT8U Length)
{
	INT8U i, LCD_Number[4];
	LCD_site(Line,Column);
	
	LCD_Number[4] = Number / 10000;                 //���ڴ����λ
	LCD_Number[3] = (Number % 10000) / 1000;		//���ڴ��ǧλ
	LCD_Number[2] = (Number % 1000) / 100;			//���ڴ�Ű�λ
	LCD_Number[1] = (Number % 100) / 10;			//���ڴ��ʮλ
	LCD_Number[0] = Number % 10;					//���ڴ�Ÿ�λ

	for(i = Length; i > 0; i--)
	{
		LCD_WriteData('0' + LCD_Number[i - 1]);
	}
}

/*******************************************************************************
* �� �� ��         : LCD_ShowChar ��LCD��ʾ�ַ�������
* ��������		   : ��������ʾλ����ʾ�ַ�
* ��    ��         : Line����ʾ�����꣬��Χ��1��2��
					 Cloumn����ʾ�����꣬��Χ��1��16��
					 LCD_Char����ʾ�ַ���
* ��    ��         : ��
*******************************************************************************/
extern void LCD_ShowChar(INT8U Line,INT8U Column,INT8U LCD_Char)
{
	LCD_site(Line,Column);
	LCD_WriteData(LCD_Char);
}

/*******************************************************************************
* �� �� ��		: LCD_ShowSignedNumber
* ��������		: LCD��ʾ�з�������
* ��    �� 		: Line����ʾ�����꣬��Χ��1��2��
				  Cloumn����ʾ�����꣬��Χ��1��16��
				  SignedNumber����ʾ���֣���Χ��-32768~32767��
				  Length����ʾ���ȣ���Χ��-32768~32767��
* ��    ��		: ��
*******************************************************************************/
extern void LCD_ShowSignedNumber(INT8U Line, INT8U Column, INT16S SignedNumber, INT8U Length)
{
	INT8U i, LCD_ShowNumber[4];
	
	LCD_site(Line,Column);
	
	if(SignedNumber < 0)
	{
		LCD_ShowChar(2, 2, '-');
		SignedNumber = -SignedNumber;
	}
	
	LCD_ShowNumber[4] = SignedNumber / 10000;                 	//���ڴ����λ
	LCD_ShowNumber[3] = (SignedNumber % 10000) / 1000;			//���ڴ��ǧλ
	LCD_ShowNumber[2] = (SignedNumber % 1000) / 100;			//���ڴ�Ű�λ
	LCD_ShowNumber[1] = (SignedNumber % 100) / 10;				//���ڴ��ʮλ
	LCD_ShowNumber[0] = SignedNumber % 10;						//���ڴ�Ÿ�λ
	
	for(i = Length; i > 0; i--)
	{
		LCD_WriteData('0' + LCD_ShowNumber[i - 1]);
	}
}