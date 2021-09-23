#ifndef _ds18b20_H_
#define _ds18b20_H_

sbit LCE_DQ=P2^4; 

extern uint tvalue;//温度值
extern bit tflag;//温度正负标志

extern uchar read_temp(uchar);

#endif