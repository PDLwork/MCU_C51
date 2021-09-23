#ifndef __AT24C02_H__
#define	__AT24C02_H__

//外部调用函数
extern void AT24C02_WriteByte(INT8U WordAddress, Data);
extern INT8U AT24C02_ReadByte(INT8U WordAddress);

#endif