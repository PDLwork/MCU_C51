#ifndef _ds18b20_H_
#define _ds18b20_H_

sbit LCE_DQ=P2^4; 

extern uint tvalue;//�¶�ֵ
extern bit tflag;//�¶�������־

extern uchar read_temp(uchar);

#endif