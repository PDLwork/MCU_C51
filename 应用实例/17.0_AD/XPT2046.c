#include <REGX52.H>
#include "UserDef.H"
#include "XPT2046.H"

/*******************************************************************************
* 函 数 名		: XPT2046_ReadAD模数转换函数
* 函数功能		: 输入读取命令字即可将对应引脚的模拟量转换为数字量
* 输    入 		: Command	输入的命令字
* 输    出		: 无
*******************************************************************************/
extern INT16U XPT2046_ReadAD(INT8U Command)
{
	INT16U ADValue = 0;
	INT8U i;
	
	XPT2046_DCLK = 0;		//时序初始化
	XPT2046_CS = 0;			//片选芯片
	
	for(i = 0; i < 8; i++)		//写入命令字
	{
		XPT2046_DIN = Command & (0x80 >>i);
		XPT2046_DCLK = 1;
		XPT2046_DCLK = 0;
	}
	
	for(i = 0; i < 16; i++)		//读取16位AD值，精度分8位和12位，末位补零
	{
		XPT2046_DCLK = 1;
		XPT2046_DCLK = 0;
		if(XPT2046_DOUT == 1)
			ADValue |= (0x8000 >> i);
	}
	
	XPT2046_CS = 1;			//读取完毕释放芯片
	
	if(Command & 0x08)		//判断当前转换精度，在进行适当移位
		return ADValue >> 8;
	else
		return ADValue >> 4;
}