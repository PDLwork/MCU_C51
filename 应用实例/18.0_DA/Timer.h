#ifndef __TIMER_H__
#define	__TIMER_H__

//���Ŷ���
sbit LED = P1^0;
sbit DA_PWM = P1^1;

//�ⲿ����
extern INT8S Compare;
extern void Timer0_Initialization();

#endif