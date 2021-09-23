#ifndef __LCD1602_H__
#define __LCD1602_H__	
//用户引脚定义

sbit LCD_RS = P2^6;
sbit LCD_RW = P2^5; 
sbit LCD_E = P2^7;

#define LCD_DataPort P0
//用户调用函数

extern void LCD_ShowNumber(INT8U Line, INT8U Column, unsigned int LCD_number);
extern void LCD_ShowChar(INT8U Line, INT8U Column, INT8U LCD_char);
extern void LCD_ShowString(INT8U Line, INT8U Column, INT8U String[]);
extern void LCD_Initialization();

#endif
