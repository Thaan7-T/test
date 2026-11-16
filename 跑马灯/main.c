#include<reg51.h>
sbit P1_0 = P1^0;
sbit P1_1 = P1^1;
sbit P1_2 = P1^2;
sbit P1_3= P1^3;
unsigned int cnt = 0;
bit stop_flag = 0;

void Delay10ms(void)	//@12.000MHz
{
	unsigned char data i, j;

	i = 117;
	j = 184;
	do
	{
		while (--j);
	} while (--i);
}

void Init_Timer0(void)
{
	TMOD = 0x01;
  TH0 = 0x3c;
	TL0 = 0xB0;
	ET0 = 1;
	TR0 = 1;
	EA = 1;
}
void main(void)
{
	Init_Timer0();
	while(1)
	{
		if(stop_flag)
		{
			continue;
		}
		P1_3 = 0;
		P1_0 = ~P1_0;
		Delay10ms();
		P1_1 = ~P1_1;
		Delay10ms();
		P1_2 = ~P1_2;
		Delay10ms();
	}
}
void Timer0_ISR(void) interrupt 1
{
	TH0 = 0x3c;
	TL0 = 0xB0;
	cnt++;
	if(cnt>=100)
	{
		cnt = 0;
		P1 = 0x08;
		stop_flag = 1;
	}
}


