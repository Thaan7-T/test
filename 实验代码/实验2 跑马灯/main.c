#include <reg52.h>
unsigned char	t;
void Delay(void)
{
	unsigned int i =0;
	for( ;i <= 50000;i++);
}

void main(void)
{
	t = 0xFE;
	P1 = t;
	while(1)
	{
		Delay();
		t=(t<<1)|(t>>7);
		P1 = t;		
	}
}