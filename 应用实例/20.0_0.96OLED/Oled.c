//OLED的显存
//存放格式如下.
//[0]0 1 2 3 ... 127	
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

static void Oled_SetPosition(INT8U X, Y)
{
	Oled_WriteCommand(0xB0 + Y);
	Oled_WriteCommand(((X & 0xf0) >> 4) | 0x10);
	Oled_WriteCommand(X & 0x0f);
}

extern void Oled_ShowChar(INT8U X, Y, Oled_Char)
{
	INT8U OffsetAddress, i;
	
	OffsetAddress = Oled_Char - ' ';	//得到偏移后的值,空格为ASCⅡ码的初始位置
	
	Oled_SetPosition(X, Y);
	
	for(i = 0; i < 6; i++)
		Oled_WriteData(ASC2Code6x8[OffsetAddress][i]);
	
//		if(Char_Size ==16)
//			{
//			OLED_Set_Pos(x,y);	
//			for(i=0;i<8;i++)
//			OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
//			OLED_Set_Pos(x,y+1);
//			for(i=0;i<8;i++)
//			OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
//			}
//			else {	
//				OLED_Set_Pos(x,y);
//				for(i=0;i<6;i++)
//				OLED_WR_Byte(F6x8[c][i],OLED_DATA);
//				
//			}
}

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