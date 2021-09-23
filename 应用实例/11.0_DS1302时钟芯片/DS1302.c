#include <REGX52.H>
#include "UserDef.H"
#include "DS1302.H"


/*******************************************************************************
* 函 数 名		: DS1302_Initialization 时钟芯片初始化函数
* 函数功能		: 将时钟芯片管脚置于默认电平
* 输    入 		: 无
* 输    出		: 无
*******************************************************************************/
extern void DS1302_Initialization(void)
{
	DS1302_CE = 0;
	DS1302_SCLK = 0;
}

/*******************************************************************************
* 函 数 名		: DS1302_WriteByte 1302写入字节函数
* 函数功能		: 给1302规定寄存器写入字节
* 输    入 		: Command（写入地址）
				  Data（写入数据）
* 输    出		: 无
*******************************************************************************/
static void DS1302_WriteByte(INT8U Command, Data)
{
	INT8U i;
	DS1302_CE = 1;
	for(i = 0; i < 8; i++)
	{
		DS1302_IO = Command & (0x01 << i);
		DS1302_SCLK = 0;
		DS1302_SCLK = 1;
	}
	for(i = 0; i < 8; i++)
	{
		DS1302_IO = Data & (0x01 << i);
		DS1302_SCLK = 0;
		DS1302_SCLK = 1;
	}
	DS1302_IO = 0;
	DS1302_SCLK = 0;
	DS1302_CE = 0;
}

/*******************************************************************************
* 函 数 名		: DS1302_ReadByte 1302读字节函数
* 函数功能		: 读取相应地址的数据
* 输    入 		: command（读取地址）
* 输    出		: DS1302_Data（返回该地址数据）
*******************************************************************************/
static INT8U DS1302_ReadByte(INT8U command)
{
	INT8U i, DS1302_Data = 0x00;
	DS1302_CE = 1;
	for(i = 0; i < 8; i++)
	{
		DS1302_IO = command & (0x01 << i);
		DS1302_SCLK = 0;
		DS1302_SCLK = 1;
	}
	for(i = 0; i < 8; i++)
	{
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
		if(DS1302_IO)
			DS1302_Data |= (0x01 << i);
	}
	DS1302_CE = 0;
	DS1302_IO=0;
	DS1302_Data = (DS1302_Data / 16) *10 + DS1302_Data % 16;  //BCD转10进制
	return DS1302_Data;
}

/*******************************************************************************
* 函 数 名		: DS1302_SetTime  1302设置时间函数
* 函数功能		: 将时间写入1302芯片中
* 输    入 		: 无
* 输    出		: 无
*******************************************************************************/
extern void DS1302_SetTime(void)
{
	DS1302_WriteByte(0x8E, 0X00);		//关闭写保护功能
	DS1302_WriteByte(0x8C, (Year / 10) *16 + Year % 10); 		//10进制转换16进制，写入年份
	DS1302_WriteByte(0x88, (Month / 10) *16 + Month % 10); 		//写入月
	DS1302_WriteByte(0x86, (Date / 10) *16 + Date % 10); 		//写入日
	DS1302_WriteByte(0x84, (Hour / 10) *16 + Hour % 10); 		//写入时
	DS1302_WriteByte(0x82, (Minute / 10) *16 + Minute % 10); 	//写入分
	DS1302_WriteByte(0x80, (Second / 10) *16 + Second % 10); 	//写入秒
	DS1302_WriteByte(0x8A, (Day / 10) *16 + Day % 10); 			//写入周
	DS1302_WriteByte(0x8E, 0x80);		//打开写保护功能
}

/*******************************************************************************
* 函 数 名		: DS1302_ReadTime  1302读时间函数
* 函数功能		: 读取1302内部时间
* 输    入 		: 无
* 输    出		: 无
*******************************************************************************/
extern void DS1302_ReadTime(void)
{
	Year = DS1302_ReadByte(0x8D);		//读取年
	Month = DS1302_ReadByte(0x89);		//读取月
	Date = DS1302_ReadByte(0x87);		//读取日
	Hour = DS1302_ReadByte(0x85);		//读取时
	Minute = DS1302_ReadByte(0x83);		//读取分
	Second = DS1302_ReadByte(0x81);		//读取秒
	Day = DS1302_ReadByte(0x8B);		//读取周
}