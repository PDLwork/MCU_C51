#ifndef __UART_H__
#define	__UART_H__

//外部调用
extern void Uart_Initialization(void);
extern void Uart_SendByte(INT8U Byte);
extern void Uart_SendString(INT8U Uart_String[]);

#endif