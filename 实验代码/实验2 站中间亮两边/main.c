#include<reg52.h>
unsigned char table[4]={0xE7,0xDB,0xBD,0x7E};
unsigned int i,j;
void Delay(void)
{
	for(i=0;i<=50000;i++);
}

void main (void)
{
	while(1)
	{
		j=0;
		while(j<=3)
		{
			P1 = table[j];
			Delay();
			j++;
		}
	}
}
		
	