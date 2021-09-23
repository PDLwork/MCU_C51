#include <REGX52.H>
#include "UserDef.H"
#include "XPT2046.H"

/*******************************************************************************
* �� �� ��		: XPT2046_ReadADģ��ת������
* ��������		: �����ȡ�����ּ��ɽ���Ӧ���ŵ�ģ����ת��Ϊ������
* ��    �� 		: Command	�����������
* ��    ��		: ��
*******************************************************************************/
extern INT16U XPT2046_ReadAD(INT8U Command)
{
	INT16U ADValue = 0;
	INT8U i;
	
	XPT2046_DCLK = 0;		//ʱ���ʼ��
	XPT2046_CS = 0;			//ƬѡоƬ
	
	for(i = 0; i < 8; i++)		//д��������
	{
		XPT2046_DIN = Command & (0x80 >>i);
		XPT2046_DCLK = 1;
		XPT2046_DCLK = 0;
	}
	
	for(i = 0; i < 16; i++)		//��ȡ16λADֵ�����ȷ�8λ��12λ��ĩλ����
	{
		XPT2046_DCLK = 1;
		XPT2046_DCLK = 0;
		if(XPT2046_DOUT == 1)
			ADValue |= (0x8000 >> i);
	}
	
	XPT2046_CS = 1;			//��ȡ����ͷ�оƬ
	
	if(Command & 0x08)		//�жϵ�ǰת�����ȣ��ڽ����ʵ���λ
		return ADValue >> 8;
	else
		return ADValue >> 4;
}