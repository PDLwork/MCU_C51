#include <reg52.h>
#include"userdef.h"
#include"alarm.h"
#include"ds18b20.h"
#include"keypad.h"

extern void buz_led_alarm(void)
{
	int temp_compare_hig;
	int temp_compare_low;
	int re_value = tvalue;
	temp_compare_hig = higtemp * 100;
	temp_compare_low = lowtemp * 100;

	if(tflag==1)		//如果是负数
		re_value = re_value * -1;

	if(re_value>temp_compare_hig)
	{
		BUZ = 0;
	}
	else
	{
		if(re_value<temp_compare_low)
			BUZ = 0;
		else
			BUZ = 1;	
	}	
}