#include <STC12C5A60S2.H>
#include <intrins.h>

void delay(unsigned int n)
{
	unsigned int i = 0;
	unsigned int j = 0;
	for (i=0; i<n; i++)
	{
		for (j=0; j<120; j++)
		{
			
		}
	}
}
int ii = 0;
void main(void)
{
	EA = 1;
	EX0 = 1;	
	IT0 = 1;
	P1 = 0xfe;
	
	
	
	while (1)
	{
		if (ii % 2 == 0)
		{
			
			P1 = _crol_(P1, 1);
			delay(2000);
		}
		if (ii % 2 == 1)
		{
			
			P1 = _crol_(P1, 7);
			delay(2000);
		}
	}
}
void Int0_Routine(void) interrupt 0
{
	delay(2000);
	if(P3^4 == 0)
	{
		delay(2000);
		ii++;
	}
}
