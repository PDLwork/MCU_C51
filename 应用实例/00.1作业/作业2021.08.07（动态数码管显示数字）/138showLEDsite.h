#ifndef __138showLEDsite_H__
#define	__138showLEDsite_H__

//引脚定义
sbit _138_A = P2^0;
sbit _138_B = P2^1;
sbit _138_C = P2^2;
#define Nixie P0

//外部调用
extern void _74HC138_ShowNumber(INT8U Show_site, INT16U Show_Number);
extern void _74HC138_ShowSignedNumber(INT8U Show_site, INT8S Show_Number);
#endif