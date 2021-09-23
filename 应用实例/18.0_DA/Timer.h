#ifndef __TIMER_H__
#define	__TIMER_H__

//引脚定义
sbit LED = P1^0;
sbit DA_PWM = P1^1;

//外部调用
extern INT8S Compare;
extern void Timer0_Initialization();

#endif