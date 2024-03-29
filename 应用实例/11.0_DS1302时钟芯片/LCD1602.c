#include <REGX52.H>
#include "UserDef.H"
#include "LCD1602.H"
#include "Delay.H"

/*******************************************************************************
* 函 数 名         : LCD_WriteCommand （LCD1602写命令函数）
* 函数功能		   : 为LCD写入命令
* 输    入         : LCD_Command （输入命令）
* 输    出         : 无
*******************************************************************************/
static void LCD_WriteCommand(INT8U LCD_Command)  
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
* 函 数 名         : LCD_WriteData （LCD1602写数据函数）
* 函数功能		   : 为LCD写入数据
* 输    入         : LCD_Data （输入数据）
* 输    出         : 无
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
* 函 数 名         : LCD_Initialization （LCD1602初始化函数）
* 函数功能		   : 液晶显示屏是初始化设置
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
extern void LCD_Initialization()   
{
    LCD_WriteCommand(0x01);	   //清屏
    LCD_WriteCommand(0x38);	   //设置显示两行、每个字符为5*7点阵、数据线为8根
	LCD_WriteCommand(0x06);	   //输入后地址指针右移
	LCD_WriteCommand(0x0c);	   //显示打开、光标关闭
}

/*******************************************************************************
* 函 数 名         : LCD_site （LCD确认显示位置函数）
* 函数功能		   : 输入坐标确认显示位置
* 输    入         : Line（显示横坐标，范围：1～2）
					 Cloumn（显示纵坐标，范围：1～16）
* 输    出         : 无
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
* 函 数 名         : LCD_ShowString （LCD显示字符串函数）
* 函数功能		   : 在输入显示位置开始显示字符串
* 输    入         : Line（显示横坐标，范围：1～2）
					 Cloumn（显示纵坐标，范围：1～16）
					 String（显示字符串）
* 输    出         : 无
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
* 函 数 名         : LCD_ShowNumber （LCD显示数字函数）
* 函数功能		   : 在输入显示位置显示数字
* 输    入         : Line（显示横坐标，范围：1～2）
					 Cloumn（显示纵坐标，范围：1～16）
					 Number（显示数字，范围：1~65535）
* 输    出         : 无
*******************************************************************************/
extern void LCD_ShowNumber(INT8U Line,INT8U Column,INT16U Number)
{
	INT8U x, LCD_Number[4];
	LCD_site(Line,Column);
	
	LCD_Number[0] = Number / 10000;                 //用于存放万位
	LCD_Number[1] = (Number % 10000) / 1000;		//用于存放千位
	LCD_Number[2] = (Number % 1000) / 100;			//用于存放百位
	LCD_Number[3] = (Number % 100) / 10;			//用于存放十位
	LCD_Number[4] = Number % 10;					//用于存放个位

	for(x = 0; x <= 2; x++)
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
* 函 数 名         : LCD_ShowNumber （LCD显示数字函数）
* 函数功能		   : 在输入显示位置显示数字
* 输    入         : Line（显示横坐标，范围：1～2）
					 Cloumn（显示纵坐标，范围：1～16）
					 Number（显示数字，范围：1~65535）
* 输    出         : 无
*******************************************************************************/
extern void LCD_ShowChar(INT8U Line,INT8U Column,INT8U LCD_Char)
{
	LCD_site(Line,Column);
	LCD_WriteData(LCD_Char);
}