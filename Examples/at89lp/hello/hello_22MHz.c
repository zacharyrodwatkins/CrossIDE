#include <stdio.h>
#include <at89lp52.h>

// ~C51~   

#define CLK 22118400L
#define BAUD 115200L

sfr16 at (0xcdcc) TMR2;
sfr16 at (0xcbca) TMR2RELOAD;

void autobaud (void)
{
	unsigned char i;
	// The input frequency for timer 2 depends if it is used as a baud
	// rate generator or not.  So for autobaud to work, make sure the
	// UART baud rate is selected to be from timer 2:
	T2CON=0x30;
	TMR2=0;
	while(RXD==1);
	TR2=1; // Start timer 2
	for(i=0; i<4; i++) // We are receiving 0x55: four zeros and four ones.
	{
		while(RXD==0);
		while(RXD==1);
	}
	TR2=0; // Stop timer 2
	TMR2RELOAD=-((TMR2+8)>>7); // This is equivalent to 65536-(((TMR2+1)/8)/16)
	TR2=1; // Let timer 2 run freely
	SCON=0x52; // Serial port in mode 1, ren, txrdy, rxempty
}

unsigned char _c51_external_startup(void)
{
	// Configure ports as bidirectional with internal pull-ups.
	PMOD=0;
	AUXR=0B_0001_0001; // 1152 bytes of internal XDATA, P4.4 is a general purpose I/O
    setbaud_timer2(0x10000L-((CLK/(((CLKREG&0x0E)>>1)+1))/(16L*BAUD))); // Initialize serial port using timer 2
    return 0;
}

void main (void)
{
    printf( "Hello, world!\r\n" );
    printf("TMR2RELOAD=%04x, CLKREG=%02x\r\n", TMR2RELOAD, CLKREG);
}
