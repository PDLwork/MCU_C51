#include <REGX52.H>
#include "userdef.h"
#include "LCD1602.h"

/*******************************************************************************
* 函 数 名         :  DelayXms 
* 函数功能		   :  延时Xms 	   晶振为12MHz 
* 输    入         :  X:延时毫秒数
* 输    出         :  无
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
* 函 数 名         :LCD_writecommand 
* 函数功能		   :1602写命令操作
* 输    入         :LCD_command(命令代码)
* 输    出         :无
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
* 函 数 名         :LCD_writeData 
* 函数功能		   :1602写数据操作
* 输    入         :LCD_data(传输数据)
* 输    出         :无
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
* 函 数 名         :LCD_Initialization 
* 函数功能		   :1602显示初始化 
* 输    入         :无
* 输    出         :无
*******************************************************************************/

extern void LCD_Initialization()
{
	LCD_writeCommand(0X01);//显示清屏
	LCD_writeCommand(0X38);//16*2显示，5*7点阵，八位数据接口
  	LCD_writeCommand(0X0C);//显示打开，光标关闭
	LCD_writeCommand(0X06);//写完后地址加一，显示屏不移动
}

/*******************************************************************************
* 函 数 名         :LCD_site
* 函数功能		   :确定显示位置 
* 输    入         :Line(行，范围：1~2)
				    Column(列，范围：1~16) 
* 输    出         :无 
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
* 函 数 名         :LCD_ShowString
* 函数功能		   :显示字符串
* 输    入         :Line(行，范围：1~2)
				    Column(列，范围：1~16)
				    String[](存放字符串) 
* 输    出         :无 
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
* 函 数 名         :LCD_ShowChar
* 函数功能		   :显示字符
* 输    入         :Line(行，范围：1~2)
				    Column(列，范围：1~16)
				    LCD_char(存放字符) 
* 输    出         :无 
*******************************************************************************/

extern void LCD_ShowChar(INT8U Line, INT8U Column, INT8U LCD_char)
{

	LCD_site(Line, Column);
	
	LCD_writeData(LCD_char);	

}

/*******************************************************************************
* 函 数 名         :LCD_ShowNumber 
* 函数功能		   :显示数字 
* 输    入         :Line(行，范围：1~2)
				    Column(列，范围：1~16)
				    LCD_number(存放数字, 范围：0~65535)
* 输    出         :无 
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