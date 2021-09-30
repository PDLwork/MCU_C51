//OLED的显存
//存放格式如下.
//[0]0 1 2 3 ... 127	上面为低位
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127

#include <REGX52.H>
#include "UserDef.H"
#include "Oled.H"
#include "I2C.H"
#include "OledDefineCode.H"

/*******************************************************************************
* 函 数 名		: Oled_WriteCommand（Oled写命令函数） 
* 函数功能		: 向Oled写入命令
* 输    入 		: Oled_Command（写入命令内容）
* 输    出		: 无
*******************************************************************************/
static void Oled_WriteCommand(INT8U Oled_Command)
{
	I2C_Start();
	I2C_SendByte(0x78);			//发送从机地址 读写位R/W#=0  SA0=0
	I2C_ReceiveAck();
	I2C_SendByte(0x00);			//write command  命令数据位D/C#=0;
	I2C_ReceiveAck();
	I2C_SendByte(Oled_Command);
	I2C_ReceiveAck();
	I2C_Stop();
}

/*******************************************************************************
* 函 数 名		: Oled_WriteData（Oled写数据函数） 
* 函数功能		: 向Oled写入数据
* 输    入 		: Oled_WriteData（写入数据内容）
* 输    出		: 无
*******************************************************************************/
static void Oled_WriteData(INT8U Oled_Data)
{
	I2C_Start();
	I2C_SendByte(0x78);			//发送从机地址 读写位R/W#=0  SA0=0
	I2C_ReceiveAck();
	I2C_SendByte(0x40);			//writedata  命令数据位D/C#=1;
	I2C_ReceiveAck();
	I2C_SendByte(Oled_Data);
	I2C_ReceiveAck();
	I2C_Stop();
}

/*******************************************************************************
* 函 数 名		: Oled_Initialization（Oled初始化函数）
* 函数功能		: 将Oled初始化后才可以使用该液晶显示屏（暂时没搞懂）
* 输    入 		: 无
* 输    出		: 无
*******************************************************************************/
extern void Oled_Initialization(void)
{
	Oled_WriteCommand(0xAE);//--display off
	Oled_WriteCommand(0x00);//---set low column address
	Oled_WriteCommand(0x10);//---set high column address
	Oled_WriteCommand(0x40);//--set start line address  
	Oled_WriteCommand(0xB0);//--set page address
	Oled_WriteCommand(0x81);// contract control
	Oled_WriteCommand(0xFF);//--128   
	Oled_WriteCommand(0xA1);//set segment remap 
	Oled_WriteCommand(0xA6);//--normal / reverse
	Oled_WriteCommand(0xA8);//--set multiplex ratio(1 to 64)
	Oled_WriteCommand(0x3F);//--1/32 duty
	Oled_WriteCommand(0xC8);//Com scan direction
	Oled_WriteCommand(0xD3);//-set display offset
	Oled_WriteCommand(0x00);//
	
	Oled_WriteCommand(0xD5);//set osc division
	Oled_WriteCommand(0x80);//
	
	Oled_WriteCommand(0xD8);//set area color mode off
	Oled_WriteCommand(0x05);//
	
	Oled_WriteCommand(0xD9);//Set Pre-Charge Period
	Oled_WriteCommand(0xF1);//
	
	Oled_WriteCommand(0xDA);//set com pin configuartion
	Oled_WriteCommand(0x12);//
	
	Oled_WriteCommand(0xDB);//set Vcomh
	Oled_WriteCommand(0x30);//
	
	Oled_WriteCommand(0x8D);//set charge pump enable
	Oled_WriteCommand(0x14);//
	
	Oled_WriteCommand(0xAF);//--turn on oled panel
}

/*******************************************************************************
* 函 数 名		: Oled_SetPosition（设置显示位置函数）
* 函数功能		: 输入显示页数和列数就可以确定显示位置
* 输    入 		: X（显示的列数，范围：0-127）
				  Y（显示页数，范围：0-7）
* 输    出		: 无
*******************************************************************************/
static void Oled_SetPosition(INT8U X, Y)
{
	Oled_WriteCommand(0xB0 + Y);
	Oled_WriteCommand(((X & 0xf0) >> 4) | 0x10);
	Oled_WriteCommand(X & 0x0f);
}

/*******************************************************************************
* 函 数 名		: Oled_Clear（Oled清屏指令）
* 函数功能		: 将Oled显示屏内容清除
* 输    入 		: 无
* 输    出		: 无
*******************************************************************************/
extern void Oled_Clear(void)
{
	INT8U i,j;
	for(i = 0; i < 8; i++)
	{
		Oled_WriteCommand(0xB0 + i);
		Oled_WriteCommand(0x00);
		Oled_WriteCommand(0x10);
		for(j = 0; j < 128; j++)
			Oled_WriteData(0); 
	}
}

/*******************************************************************************
* 函 数 名		: Oled_ShowChar（显示字符函数）
* 函数功能		: 输入显示位置与显示
* 输    入 		: X（显示的列数，范围：0-127）
				  Y（显示页数，范围：0-7）
				  Oled_Char（显示的字符）
				  FontSize（字体大小，可选SmallSize、MediumSize）
* 输    出		: 无
*******************************************************************************/
extern void Oled_ShowChar(INT8U X, Y, Oled_Char, bit FontSize)
{
	INT8U OffsetAddress, i;
	
	OffsetAddress = Oled_Char - ' ';	//得到偏移后的值,空格为ASCⅡ码的初始位置
	
	if(FontSize == SmallSize)
	{
		Oled_SetPosition(X, Y);
		
		for(i = 0; i < 8; i++)
			Oled_WriteData(ASC2Code8x8[OffsetAddress][i]);
	}
	if(FontSize == MediumSize)
	{
		Oled_SetPosition(X, Y);
		
		for(i = 0; i < 8; i++)
			Oled_WriteData(ASC2Code8x16[OffsetAddress][i]);
		
		Oled_SetPosition(X, Y + 1);
		
		for(i = 8; i < 16; i++)
			Oled_WriteData(ASC2Code8x16[OffsetAddress][i]);
	}
}

/*******************************************************************************
* 函 数 名		: Oled_ShowString（显示字符串函数）
* 函数功能		: 输入显示位置与显示内容跟显示字体大小就可以显示字符串且拥有自动换行功能
* 输    入 		: X（显示的列数，范围：0-127）
				  Y（显示页数，范围：0-7）
				  Oled_String（显示的字符串数组）
				  FontSize（字体大小，可选SmallSize、MediumSize）
* 输    出		: 
*******************************************************************************/
extern void Oled_ShowString(INT8U X, Y, INT8U *Oled_String, bit FontSize)
{
	INT8U i, j, OffsetAddress;
	
	if(FontSize == SmallSize)
	{
		Oled_SetPosition(X, Y);
		
		for(i = 0; Oled_String[i] != '\0'; i++)
		{
			OffsetAddress = Oled_String[i] - ' ';
			
			for(j = 0; j < 8; j++)
				Oled_WriteData(ASC2Code8x8[OffsetAddress][j]);
			
			X += 8;
			if(X > 120)
			{
				X = 0;
				Y ++;
				Oled_SetPosition(X, Y);
			}
		}
	}
	if(FontSize == MediumSize)
	{
		for(i = 0; Oled_String[i] != '\0'; i++)
		{
			Oled_ShowChar(X,Y, Oled_String[i], FontSize);
			
			X += 8;
			if(X > 120)
			{
				X = 0;
				Y += 2;
				Oled_SetPosition(X, Y);
			}
		}
	}
}

/*******************************************************************************
* 函 数 名		: Oled_ShowPhoto（显示图片函数）
* 函数功能		: 在Oled上显示预先取模的图片
* 输    入 		: 无
* 输    出		: 无
*******************************************************************************/
extern void Oled_ShowPhoto(void)
{
	INT8U i, j, z;
	for(i = 0; i < 64; i++)
	{
		z = i / 8;
		if(i % 8 == 0)
			Oled_SetPosition(0, z);
		for(j = 0; j < 16; j++)
			Oled_WriteData(Photo[i][j]);
	}
}

/*******************************************************************************
* 函 数 名		: Oled_ShowChinse（显示中文函数）
* 函数功能		: 可以显示预先设置好的中文，可在OledDefineCode.H中查询对应中文代号
* 输    入 		: X（显示的列数，范围：0-127）
				  Y（显示页数，范围：0-7）
				  Oled_ShowChinse（显示的中文代号）
* 输    出		: 无
*******************************************************************************/
extern void Oled_ShowChinse(INT8U X, Y, Chinse_Number)
{
	INT8U i;
	
	Oled_SetPosition(X, Y);
	
	for(i = 0; i < 16; i++)
		Oled_WriteData(Chinese[Chinse_Number][i]);
	
	Oled_SetPosition(X, Y + 1);
	
	for(i = 16; i < 32; i++)
		Oled_WriteData(Chinese[Chinse_Number][i]);
}