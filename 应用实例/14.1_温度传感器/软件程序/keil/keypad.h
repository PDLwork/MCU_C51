#ifndef _keypad_H_
#define _keypad_H_

sbit SW_1 = P1^0;
sbit SW_2 = P1^1;
sbit SW_3 = P1^2;
sbit SW_4 = P1^3;
sbit SW_5 = P1^4;
sbit SW_6 = P1^5;

extern bit dismod_change;	 //显示模式设置，1为时时显示模式，0为设置报警模式
extern bit temp_change;	   //温度设置标志位，1为设置上限，0为设置下限
extern char higtemp;		 //存放温度报警上限
extern char lowtemp;		 //存放温度报警下限


extern void keypadscan(void);

#endif