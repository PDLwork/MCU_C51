#include <REGX52.H>
#include "UserDef.H"
#include "138showLEDsite.H"

void main(void)
{
	while(1)
	{
		_74HC138_ShowSignedNumber(5,-99);
	}
}