#include <reg52.h>
typedef unsigned char u8;
typedef unsigned int u16;
sbit led = P1^0;

u16 tick = 0;//系统节拍，每5ms+1
bit run_flag = 1;//总开关
u8 mode = 0;//0:熄灭 1：500ms闪烁 2：1s闪烁


void Timer0_Init(void)
{
	TMOD |= 0x01;
	TH0 = 0xEE;
	TL0 = 0x00;// 5ms@11.0592MHz
	ET0 = 1;
	TR0 = 1;
	EA = 1;
}

void Int0_Init(void)
{
	IT0 = 1;
	EX0 = 1;
	EA = 1;
}


void Int1_Init(void)
{
	IT1 = 1;
	EX1 = 1;
	EA = 1;
}

void Timer0_ISR(void) interrupt 1//负责tick计数，不做业务
{
	TH0 = 0xEE;
	TL0 = 0x00;
	tick++;
}

void Int0_ISR(void) interrupt 0//只改标志,实现模式转换
{
	mode++;
	if(mode >= 3)
		mode = 0;
}

void Int1_ISR(void) interrupt 2//程序启停开关
{
	run_flag = !run_flag;
}


void main(void)
{
	u16 t_buf1 = 0,t_buf2 = 0;
	Timer0_Init();
	Int0_Init();
	Int1_Init();
	while(1)
	{
		if(!run_flag)
		continue;
			switch(mode)
			{
				case 0: led = 1;break;
				case 1:
					if(tick - t_buf1 >= 100)//500ms
					{
						t_buf1 = tick;
						led = ~led;
					}
					break;
				case 2:
					if(tick - t_buf2 >= 200)//1000ms
					{
						t_buf2 = tick;
						led = ~led;
					}
					break;
				}
			}
	}
			

