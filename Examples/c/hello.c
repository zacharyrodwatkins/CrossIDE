// ~C51~   

#include <stdio.h>
#include <ctype.h>
#include <DE2_8052.h>

//The DE2-8052 soft processor clock is 33.33MHz
#define CLK 33333333L
#define BAUD 115200L
#define TIMER_2_RELOAD (0x10000L-(CLK/(32L*BAUD)))

void main (void)
{
	// Turn off all LEDs (they are really anoying!)
	LEDRA=0;
	LEDRB=0;
	LEDRC=0;
	LEDG=0;
	setbaud_timer2(TIMER_2_RELOAD); // Initialize serial port using timer 2 
	printf("Hello, world!\n");
}