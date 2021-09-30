#ifndef __Buzzer_H__
#define	__Buzzer_H__

//引脚定义
sbit Buzzer = P1^1;

//外部调用函数
extern void Buzzer_Ring(INT16U Time_ms);

#endif