#ifndef __DS1302_H__
#define	__DS1302_H__

//���Ŷ���
sbit DS1302_CE = P1^0;
sbit DS1302_IO = P1^1;
sbit DS1302_SCLK = P1^2;

//�ⲿ����
extern INT8U Year, Month, Date, Hour, Minute, Second, Day;  //�ֱ����ڴ���ꡢ�¡��ա�ʱ���֡��롢��
extern void DS1302_Initialization();
extern void DS1302_ReadTime();
extern void DS1302_SetTime();

#endif