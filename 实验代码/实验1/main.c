#include<reg51.h>
sbit P2_1 = P2^1;
void Delay1000ms(void)
{
	unsigned char data i, j, k;

	i = 8;
	j = 154;
	k = 122;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
void main(void)
{
	P2_1 = 1;
	Delay1000ms();
	P2_1 = 0;
	while(1);
}
