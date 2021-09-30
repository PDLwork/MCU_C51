#include <REGX52.H>
#include "UserDef.H"
#include "Buzzer.H"
#include "Delay.H"

extern void Buzzer_Ring(INT16U Time_ms)
{	
	Buzzer = 0;			//·äÃùÆ÷Ïì
	
	DelayXms(Time_ms);
	
	Buzzer = 1;			//·äÃùÆ÷¹Ø±Õ
}