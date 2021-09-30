//OLED���Դ�
//��Ÿ�ʽ����.
//[0]0 1 2 3 ... 127	����Ϊ��λ
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
* �� �� ��		: Oled_WriteCommand��Oledд������� 
* ��������		: ��Oledд������
* ��    �� 		: Oled_Command��д���������ݣ�
* ��    ��		: ��
*******************************************************************************/
static void Oled_WriteCommand(INT8U Oled_Command)
{
	I2C_Start();
	I2C_SendByte(0x78);			//���ʹӻ���ַ ��дλR/W#=0  SA0=0
	I2C_ReceiveAck();
	I2C_SendByte(0x00);			//write command  ��������λD/C#=0;
	I2C_ReceiveAck();
	I2C_SendByte(Oled_Command);
	I2C_ReceiveAck();
	I2C_Stop();
}

/*******************************************************************************
* �� �� ��		: Oled_WriteData��Oledд���ݺ����� 
* ��������		: ��Oledд������
* ��    �� 		: Oled_WriteData��д���������ݣ�
* ��    ��		: ��
*******************************************************************************/
static void Oled_WriteData(INT8U Oled_Data)
{
	I2C_Start();
	I2C_SendByte(0x78);			//���ʹӻ���ַ ��дλR/W#=0  SA0=0
	I2C_ReceiveAck();
	I2C_SendByte(0x40);			//writedata  ��������λD/C#=1;
	I2C_ReceiveAck();
	I2C_SendByte(Oled_Data);
	I2C_ReceiveAck();
	I2C_Stop();
}

/*******************************************************************************
* �� �� ��		: Oled_Initialization��Oled��ʼ��������
* ��������		: ��Oled��ʼ����ſ���ʹ�ø�Һ����ʾ������ʱû�㶮��
* ��    �� 		: ��
* ��    ��		: ��
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
* �� �� ��		: Oled_SetPosition��������ʾλ�ú�����
* ��������		: ������ʾҳ���������Ϳ���ȷ����ʾλ��
* ��    �� 		: X����ʾ����������Χ��0-127��
				  Y����ʾҳ������Χ��0-7��
* ��    ��		: ��
*******************************************************************************/
static void Oled_SetPosition(INT8U X, Y)
{
	Oled_WriteCommand(0xB0 + Y);
	Oled_WriteCommand(((X & 0xf0) >> 4) | 0x10);
	Oled_WriteCommand(X & 0x0f);
}

/*******************************************************************************
* �� �� ��		: Oled_Clear��Oled����ָ�
* ��������		: ��Oled��ʾ���������
* ��    �� 		: ��
* ��    ��		: ��
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
* �� �� ��		: Oled_ShowChar����ʾ�ַ�������
* ��������		: ������ʾλ������ʾ
* ��    �� 		: X����ʾ����������Χ��0-127��
				  Y����ʾҳ������Χ��0-7��
				  Oled_Char����ʾ���ַ���
				  FontSize�������С����ѡSmallSize��MediumSize��
* ��    ��		: ��
*******************************************************************************/
extern void Oled_ShowChar(INT8U X, Y, Oled_Char, bit FontSize)
{
	INT8U OffsetAddress, i;
	
	OffsetAddress = Oled_Char - ' ';	//�õ�ƫ�ƺ��ֵ,�ո�ΪASC����ĳ�ʼλ��
	
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
* �� �� ��		: Oled_ShowString����ʾ�ַ���������
* ��������		: ������ʾλ������ʾ���ݸ���ʾ�����С�Ϳ�����ʾ�ַ�����ӵ���Զ����й���
* ��    �� 		: X����ʾ����������Χ��0-127��
				  Y����ʾҳ������Χ��0-7��
				  Oled_String����ʾ���ַ������飩
				  FontSize�������С����ѡSmallSize��MediumSize��
* ��    ��		: 
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
* �� �� ��		: Oled_ShowPhoto����ʾͼƬ������
* ��������		: ��Oled����ʾԤ��ȡģ��ͼƬ
* ��    �� 		: ��
* ��    ��		: ��
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
* �� �� ��		: Oled_ShowChinse����ʾ���ĺ�����
* ��������		: ������ʾԤ�����úõ����ģ�����OledDefineCode.H�в�ѯ��Ӧ���Ĵ���
* ��    �� 		: X����ʾ����������Χ��0-127��
				  Y����ʾҳ������Χ��0-7��
				  Oled_ShowChinse����ʾ�����Ĵ��ţ�
* ��    ��		: ��
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