#ifndef __OLED_H__
#define	__OLED_H__

#define SmallSize 0
#define MediumSize 1

extern void Oled_Initialization();
extern void Oled_ShowChar(INT8U X, Y, Oled_Char, bit FontSize);
extern void Oled_Clear();
extern void Oled_ShowString(INT8U X, Y,INT8U *Oled_String, bit FontSize);
extern void Oled_ShowPhoto();
extern void Oled_ShowChinse(INT8U X, Y, Chinse_Number);

#endif