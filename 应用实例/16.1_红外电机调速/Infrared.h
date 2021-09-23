#ifndef __Infrared_H__
#define	__Infrared_H__

//宏定义
#define Infrared_POWER			0x45
#define Infrared_MODE			0x46
#define Infrared_MUTE			0x47
#define Infrared_START_STOP		0x44
#define Infrared_PREVIOUS		0x40
#define Infrared_NEXT			0x43
#define Infrared_EQ				0x07
#define Infrared_VOL_MINUS		0x15
#define Infrared_VOL_ADD		0x09
#define Infrared_0				0x16
#define Infrared_RPT			0x19
#define Infrared_USD			0x0D
#define Infrared_1				0x0C
#define Infrared_2				0x18
#define Infrared_3				0x5E
#define Infrared_4				0x08
#define Infrared_5				0x1C
#define Infrared_6				0x5A
#define Infrared_7				0x42
#define Infrared_8				0x52
#define Infrared_9				0x4A

//引脚定义
sbit Infrared = P3^2;

//外部调用
extern bit Infrared_RepeatFlag, Infrared_DataFlag;
extern INT8U Infrared_Command, Infrared_Address;
extern void Infrared_Initialization();

#endif