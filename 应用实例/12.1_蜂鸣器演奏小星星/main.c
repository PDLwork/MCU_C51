#include <REGX52.H>
#include "UserDef.H"
#include "Delay.H"
#include "Timer.H"

sbit Buzzer = P2^4;

INT8U Music_Seclect, Pitch_Seclect;	//分别用于乐谱指针与频率指针

INT16U code Pitch[] = 
{ 	0,	//0表示空拍,此频率表为C调
	63628, 63731, 63835, 63928, 64021, 64103, 64185, 64260, 64331, 64400, 64463, 64528, 	//低音
	64580, 64633, 64684, 64732, 64777, 64820, 64860, 64898, 64934, 64968, 65000, 65030,		//中央C
	65058, 65085, 65110, 65134, 65157, 65178, 65198, 65217, 65235, 65252, 65268, 65283		//高音
};

//通常为1拍
//播放速度，值为四分音符的时长(ms)
#define Beat_Speed	500

//音符与索引对应表，P：休止符，L：低音，M：中音，H：高音，下划线：升半音符号#
#define P	0
#define L1	1
#define L1_	2
#define L2	3
#define L2_	4
#define L3	5
#define L4	6
#define L4_	7
#define L5	8
#define L5_	9
#define L6	10
#define L6_	11
#define L7	12
#define M1	13
#define M1_	14
#define M2	15
#define M2_	16
#define M3	17
#define M4	18
#define M4_	19
#define M5	20
#define M5_	21
#define M6	22
#define M6_	23
#define M7	24
#define H1	25
#define H1_	26
#define H2	27
#define H2_	28
#define H3	29
#define H4	30
#define H4_	31
#define H5	32
#define H5_	33
#define H6	34
#define H6_	35
#define H7	36

//乐谱
INT8U code Music[] = 
{  
	M1, 4,		M1, 4,		M5, 4,		M5, 4,
	M6, 4,		M6, 4,		M5, 4+4,
	M4, 4,		M4, 4,		M3, 4,		M3, 4,
	M2, 4,		M2, 4,		M1, 4+4,
	M5, 4,		M5, 4,		M4, 4,		M4, 4,
	M3, 4,		M3, 4,		M2, 4+4,
	M5, 4,		M5, 4,		M4, 4,		M4, 4,
	M3, 4,		M3, 4,		M2, 4+4,
	M1, 4,		M1, 4,		M5, 4,		M5, 4,
	M6, 4,		M6, 4,		M5, 4+4,
	M4, 4,		M4, 4,		M3, 4,		M3, 4,
	M2, 4,		M2, 4,		M1, 4+4,
	0xFF	//终止标志
};

/*******************************************************************************
* 函 数 名         :  main （主函数）
* 函数功能		   :  主程循环执行
* 输    入         :  无
* 输    出         :  无
*******************************************************************************/
void main(void)
{
	Timer0_Initialization();
	while(1)
	{
		Pitch_Seclect = Music[Music_Seclect];
		Music_Seclect++;
		DelayXms( Beat_Speed / 4 * Music[Music_Seclect] - 5);	//选择音符对应的时值
		Music_Seclect++;
		TR0 = 0;		//关闭中断并延时达到松手效果
		DelayXms(5);
		TR0 = 1;
		if(Music[Music_Seclect] == 0xFF)
		{
			TR0 = 0;
			while(1);
		}
	}
}

/*******************************************************************************
* 函 数 名         : Timer_Routine 定时器主函数
* 函数功能		   : 计时器计时一定时间执行内容
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void Timer0_Routine() interrupt 1
{
	TL0 = Pitch[Pitch_Seclect] % 256;
	TH0 = Pitch[Pitch_Seclect] / 256;
	Buzzer = !Buzzer;
}