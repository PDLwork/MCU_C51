#ifndef __OLED_H__
#define	__OLED_H__

extern void Oled_Initialization();
extern void Oled_ShowChar(INT8U X, Y, Oled_Char);
extern void Oled_Clear();
extern void Oled_ShowString(INT8U X, Y,INT8U *Oled_String);
extern void Oled_Test();

#endif