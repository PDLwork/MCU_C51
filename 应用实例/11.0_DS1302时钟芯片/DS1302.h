#ifndef __DS1302_H__
#define	__DS1302_H__

//引脚定义
sbit DS1302_CE = P1^0;
sbit DS1302_IO = P1^1;
sbit DS1302_SCLK = P1^2;

//外部调用
extern INT8U Year, Month, Date, Hour, Minute, Second, Day;  //分别用于存放年、月、日、时、分、秒、周
extern void DS1302_Initialization();
extern void DS1302_ReadTime();
extern void DS1302_SetTime();

#endif