#ifndef __LCD1602_H__
#define __LCD1602_H__

//引脚配置：
sbit LCD_RS=P2^6;
sbit LCD_RW=P2^5;
sbit LCD_E=P2^7; 
#define LCD_DataPort P0

//外部调用：
extern void LCD_Initialization();
extern void LCD_ShowString(INT8U Line,INT8U Column,INT8S String[]);
extern void LCD_ShowNumber(INT8U Line,INT8U Column,INT16U Number, INT8U Length);
extern void LCD_ShowChar(INT8U Line,INT8U Column,INT8U LCD_Char);

#endif
