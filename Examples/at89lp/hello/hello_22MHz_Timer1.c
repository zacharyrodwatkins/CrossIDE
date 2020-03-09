#include <stdio.h>
#include <at89lp52.h>

// ~C51~   

#define CLK 22118400L
#define BAUD 115200L

#define CLK 22118400L
#define PUSHBUTTON PSEN
#define BAUD 115200L
#define TIMER1_RELOAD (256-((CLK*2L)/(32L*BAUD)))

unsigned char _c51_external_startup(void)
{
	// Configure ports as bidirectional with internal pull-ups.
	PMOD=0;
    // Initialize serial port using timer 1
    TR1=0;
	TMOD=(TMOD&0x0f)|0x20;
	PCON|=0x80;
	TH1=TL1=TIMER1_RELOAD;
	TR1=1;
	SCON=0x52;
    
    return 0;
}

void main (void)
{
    printf( "Hello, world!\r\n" );
    printf("TIMER1_RELOAD=%04x, CLKREG=%02x\r\n", TIMER1_RELOAD, CLKREG);
}
