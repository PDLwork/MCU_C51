#ifndef __Buzzer_H__
#define	__Buzzer_H__

//引脚定义
sbit Buzzer = P2^4;

//外部调用
extern void Buzzer_Time(INT16U time);

#endif