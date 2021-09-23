#ifndef __ButtonScan_H__
#define	__ButtonScan_H__

//引脚定义
sbit Button1 = P1^0;
sbit Button2 = P1^1;
sbit Button3 = P1^2;
sbit Button4 = P1^3;
sbit Button5 = P1^4;
sbit Button6 = P1^5;
sbit Button7 = P1^6;
sbit Button8 = P1^7;

//外部调用
extern INT8U Button_Value;
extern INT8U ButtonScan();

#endif