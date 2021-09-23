#ifndef _keypad_H_
#define _keypad_H_

sbit SW_1 = P1^0;
sbit SW_2 = P1^1;
sbit SW_3 = P1^2;
sbit SW_4 = P1^3;
sbit SW_5 = P1^4;
sbit SW_6 = P1^5;

extern bit dismod_change;	 //��ʾģʽ���ã�1Ϊʱʱ��ʾģʽ��0Ϊ���ñ���ģʽ
extern bit temp_change;	   //�¶����ñ�־λ��1Ϊ�������ޣ�0Ϊ��������
extern char higtemp;		 //����¶ȱ�������
extern char lowtemp;		 //����¶ȱ�������


extern void keypadscan(void);

#endif