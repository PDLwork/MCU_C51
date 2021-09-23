#ifndef __TIMER_H__
#define	__TIMER_H__

sbit Motor = P2^2;

//外部调用
extern INT8U Compare;
extern void Timer1_Initialization();
extern void Timer0_Initialization();
extern void Timer0_Run();
extern INT16U Timer0_GetCounter();

#endif