#include <stdio.h>
#include <at89lp828.h>

// ~C51~  

#define CLK 3686400L
#define BAUD 115200L
#define TIMER_2_RELOAD (0x10000L-(CLK/(16L*BAUD)))

void mydelay (void)
{
	unsigned int j;
	for(j=0; j<50000; j++);
}

void main (void)
{
	CLKREG=0x00; // TPS=0000B
	setbaud_timer2(TIMER_2_RELOAD); // Initialize serial port using timer 2 
	printf("Hello, world!\n");
	while(1)
	{
		P2_1=0;
		mydelay();
		P2_1=1;
		mydelay();
	}
}
