#include <stdio.h>
#include <at89lp4052.h>

// ~C51~  

void mydelay (void)
{
	unsigned long int j;
	for(j=0; j<100000; j++);
}

void main (void)
{
	P1M0=0;
	P1M1=0;
	while(1)
	{
		P1_0=0;
		mydelay();
		P1_0=1;
		mydelay();
	}
}
