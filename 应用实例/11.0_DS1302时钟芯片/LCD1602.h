#ifndef __LCD1602_H__
#define __LCD1602_H__

//�������ã�
sbit LCD_RS=P2^6;
sbit LCD_RW=P2^5;
sbit LCD_E=P2^7; 
#define LCD_DataPort P0

//�ⲿ���ã�
extern INT8U DS1302_Time[];  //�ֱ����ڴ���ꡢ�¡��ա�ʱ���֡��롢��
extern void LCD_Initialization();
extern void LCD_ShowString(INT8U Line,INT8U Column,INT8S String[]);
extern void LCD_ShowNumber(INT8U Line,INT8U Column,INT16U Number);
extern void LCD_ShowChar(INT8U Line,INT8U Column,INT8U LCD_Char);

#endif
