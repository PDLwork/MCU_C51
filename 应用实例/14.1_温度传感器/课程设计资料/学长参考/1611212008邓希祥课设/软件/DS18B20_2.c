#include <DS18B20_2.h>

bit flag_fu2=0;
/***************�����ǲ��³���*****************/
void delay_18B20_2(unsigned int i)//��ʱ����
{
 while(i--);
}
//18b20��ʼ������
static void Init_DS18B20(void)
{
 unsigned char x=0;
 DQ_2 = 1;    //DQ_2��λ
 delay_18B20_2(8);  //������ʱ
 DQ_2 = 0;    //��Ƭ����DQ_2����
 delay_18B20_2(80); //��ȷ��ʱ ���� 480us
 DQ_2 = 1;    //��������
 delay_18B20_2(10);
 x=DQ_2;      //������ʱ�� ���x=0���ʼ���ɹ� x=1���ʼ��ʧ��
 delay_18B20_2(5);
}

//��һ���ֽ�
static unsigned char ReadOneChar(void)
{
unsigned char i=0;
unsigned char dat = 0;
for (i=8;i>0;i--)
 {
  DQ_2 = 0; // �������ź�
  dat>>=1;
  DQ_2 = 1; // �������ź�
  if(DQ_2)
   dat|=0x80;
  delay_18B20_2(5);
 }
 return(dat);
}
//дһ���ֽ�
static void WriteOneChar(unsigned char dat)
{
 unsigned char i=0;
 for (i=8; i>0; i--)
 {
  DQ_2 = 0;
  DQ_2 = dat&0x01;
  delay_18B20_2(5);
  DQ_2 = 1;
  dat>>=1;
 }
delay_18B20_2(5);
}
//��ȡ�¶�
int ReadTemperature_2(void)
{
	int value; //����¶���ֵ
	unsigned int tmpvalue;

	unsigned char a=0;
	unsigned char b=0;
	float t;

	Init_DS18B20();
	WriteOneChar(0xCC); // ����������кŵĲ���
	WriteOneChar(0x44); // �����¶�ת��
	delay_18B20_2(100);
	Init_DS18B20();
	WriteOneChar(0xCC); //����������кŵĲ��� 
	WriteOneChar(0xBE); //��ȡ�¶ȼĴ����ȣ����ɶ�9���Ĵ����� ǰ���������¶�
	a=ReadOneChar();
	b=ReadOneChar();	
	if((b&0xf8)==0xf8) //���ֽڵĸ�5λΪ1ʱ���¶�Ϊ��
		{flag_fu2=1;}
	else
		{flag_fu2=0;}

    //���ߵ������ֽںϳ�һ�����α���
    //������ж��ڸ��������ò�������ʾ��
    //���Ǹ�ֵ, ��ȡ��������ֵ���ò����ʾ��, ��ֱ�Ӹ�ֵ��int�͵�value
    tmpvalue = b;
    tmpvalue <<= 8;
    tmpvalue |= a;
    value = tmpvalue;
	if(flag_fu2==1)  //�¶�Ϊ��ֵ
	{
		value=(~value)+1; //ȡ���ټ�1
	}
 
    //ʹ��DS18B20��Ĭ�Ϸֱ���12λ, ��ȷ��Ϊ0.0625��, ���������ݵ����λ����0.0625��
    t = value * 0.0625;
 
    value = t * 100 + (value > 0 ? 0.5 : -0.5); //����0��0.5, С��0��0.5
	
    return value;
}