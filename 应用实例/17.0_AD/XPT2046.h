#ifndef __XPT2046_H__
#define __XPT2046_H__

//�������ã�
sbit XPT2046_DCLK = P2^0;
sbit XPT2046_CS = P2^1;
sbit XPT2046_DIN = P2^2;
sbit XPT2046_DOUT = P2^3;

//�궨��  �ֱ�Ϊת��XPT1046�ĸ������ŵ�������
//8λ����
#define XPT2046_XP_8 		0x9C
#define XPT2046_YP_8 		0xDC
#define XPT2046_VBAT_8 		0xAC
#define XPT2046_AUX_8 		0xEC

//12λ����
#define XPT2046_XP_12 		0x94
#define XPT2046_YP_12 		0xD4
#define XPT2046_VBAT_12 	0xA4
#define XPT2046_AUX_12 		0xE4

//�ⲿ����
extern INT16U XPT2046_ReadAD(INT8U Command);

#endif
