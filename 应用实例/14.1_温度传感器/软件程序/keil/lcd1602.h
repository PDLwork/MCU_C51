#ifndef _lcd1602_H_
#define _lcd1602_H_

sbit LCD_E = P2^2;
sbit LCD_RW = P2^1;
sbit LCD_RS = P2^0;

extern void lcd_init();
extern void lcd_write_com(uchar com);
extern void lcd_dis_mod(uchar x);
extern void lcd_disp_18b20(uchar);
extern void lcd_disp_alarm(char xx);

#endif