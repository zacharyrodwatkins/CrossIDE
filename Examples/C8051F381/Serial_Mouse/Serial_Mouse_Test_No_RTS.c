// Serial_Mouse_Test_No_RTS.c: Emulates a Microsoft's serial mouse.
// This version doesn't check the RTS signal before sending the
// ID key.  Instead, it uses the times at which the RTS toggles 
// which were found experimentally.
//
// By:  Jesus Calvino-Fraga (c) 2015
//
// The next line clears the "C51 command line options:" field when compiling with CrossIDE
//  ~C51~  

#include <C8051f38x.h>
#include <stdio.h>
#include <limits.h>

#define BR     P0_1 // Right Button
#define BL     P0_0 // Left Button
#define MU     P2_7 // Move cursor up push button
#define MD     P2_6 // Move cursor down push button
#define ML     P2_5 // Move cursor left push button
#define MR     P2_4 // Move cursor right push button

#define SYSCLK      24000000L  // SYSCLK frequency in Hz
#define BAUDRATE        1200L  // Baud rate of UART in bps

void PORT_Init (void)
{
	P0MDOUT |= 0x10; // Enable Uart TX as push-pull output
	XBR0     = 0x01; // Enable UART on P0.4(TX) and P0.5(RX)                     
	XBR1     = 0x40; // Enable crossbar and weak pull-ups
}

void SYSCLK_Init (void)
{
	// CLKSEL&=0b_1111_1000; // Not needed because CLKSEL==0 after reset
#if (SYSCLK == 12000000L)
	//CLKSEL|=0b_0000_0000;  // SYSCLK derived from the Internal High-Frequency Oscillator / 4 
#elif (SYSCLK == 24000000L)
	CLKSEL|=0b_0000_0010; // SYSCLK derived from the Internal High-Frequency Oscillator / 2.
#elif (SYSCLK == 48000000L)
	CLKSEL|=0b_0000_0011; // SYSCLK derived from the Internal High-Frequency Oscillator / 1.
#else
	#error SYSCLK must be either 12000000L, 24000000L, or 48000000L
#endif
	OSCICN |= 0x03;   // Configure internal oscillator for its maximum frequency
	RSTSRC  = 0x04;   // Enable missing clock detector
}
 
void UART0_Init (void)
{
	SCON0 = 0x10;
   
#if (SYSCLK/BAUDRATE/2L/256L < 1)
	TH1 = 0x10000-((SYSCLK/BAUDRATE)/2L);
	CKCON &= ~0x0B;                  // T1M = 1; SCA1:0 = xx
	CKCON |=  0x08;
#elif (SYSCLK/BAUDRATE/2L/256L < 4)
	TH1 = 0x10000-(SYSCLK/BAUDRATE/2L/4L);
	CKCON &= ~0x0B; // T1M = 0; SCA1:0 = 01                  
	CKCON |=  0x01;
#elif (SYSCLK/BAUDRATE/2L/256L < 12)
	TH1 = 0x10000-(SYSCLK/BAUDRATE/2L/12L);
	CKCON &= ~0x0B; // T1M = 0; SCA1:0 = 00
#else
	#if ( (SYSCLK/BAUDRATE/2L/48L) > 255)
	#error Timer 1 can not be set to the desired baud rate
	#endif
	TH1 = 0x10000-(SYSCLK/BAUDRATE/2L/48L);
	CKCON &= ~0x0B; // T1M = 0; SCA1:0 = 10
	CKCON |=  0x02;
#endif
	TL1 = TH1;      // Init Timer1
	TMOD &= ~0xf0;  // TMOD: timer 1 in 8-bit autoreload
	TMOD |=  0x20;                       
	TR1 = 1; // START Timer1
	TI = 1;  // Indicate TX0 ready
}

// Uses Timer3 to delay <us> micro-seconds. 
void Timer3us(unsigned char us)
{
	unsigned char i;               // usec counter
	
	// The input for Timer 3 is selected as SYSCLK by setting T3ML (bit 6) of CKCON:
	CKCON|=0b_0100_0000;
	
	TMR3RL = (-(SYSCLK)/1000000L); // Set Timer3 to overflow in 1us.
	TMR3 = TMR3RL;                 // Initialize Timer3 for first overflow
	
	TMR3CN = 0x04;                 // Sart Timer3 and clear overflow flag
	for (i = 0; i < us; i++)       // Count <us> overflows
	{
		while (!(TMR3CN & 0x80));  // Wait for overflow
		TMR3CN &= ~(0x80);         // Clear overflow indicator
	}
	TMR3CN = 0 ;                   // Stop Timer3 and clear overflow flag
}

void waitms (unsigned int ms)
{
	unsigned int j;
	unsigned char k;
	for(j=0; j<ms; j++)
		for (k=0; k<4; k++) Timer3us(250);
}

// Seven bit version of putchar.  We just need the most significant bit set to one
void putchar (char c)
{
	while (!TI);
	TI=0;
	SBUF=(c|0x80);
}

void main (void) 
{
	bit sBL=0, sBR=0;
	unsigned char j;
	char x=0, y=0;
	
	PCA0MD &= ~0x40; // WDTE = 0 (clear watchdog timer enable)
	PORT_Init();     // Initialize Port I/O
	SYSCLK_Init ();  // Initialize Oscillator
	UART0_Init();    // Initialize UART0
	
	waitms(500); // Actually 400, but we have a window of 200ms to respond.
	putchar('M');
	waitms(600);
	putchar('M');
	waitms(400);
	putchar('M');
	waitms(600);
	putchar('M');
	waitms(400);
	putchar('M');
	waitms(600);
	putchar('M');
	
	while(1)
	{	
		if(MR==0)
		{
			if(x<SCHAR_MAX) x++;
		}
		if(ML==0)
		{
			if(x>SCHAR_MIN) x--;
		}
		if(MU==0)
		{
			if(y>SCHAR_MIN) y--;
		}
		if(MD==0)
		{
			if(y<SCHAR_MAX) y++;
		}

		/* Microsoft Serial Mouse data format:
		byte d6  d5  d4  d3  d2  d1  d0
		   1  1  lb  rb dy7 dy6 dx7 dx6
		   2  0 dx5 dx4 dx3 dx2 dx1 dx0
		   3  0 dy5 dy4 dy3 dy2 dy1 dy0
		*/
	
		if((BL!=sBL) || (BR!=sBR) || (x!=0) || (y!=0) )
		{
			sBL=BL;
			sBR=BR;

			j=0b_100_0000;
			if (BR==0) j|=0b_010_0000;
			if (BL==0) j|=0b_001_0000;
			if (x&0b_1000_0000) j|=0b_000_0010;
			if (x&0b_0100_0000) j|=0b_000_0001;
			if (y&0b_1000_0000) j|=0b_000_1000;
			if (y&0b_0100_0000) j|=0b_000_0100;

			putchar(j);
			putchar(x&0b_0011_1111);
			putchar(y&0b_0011_1111);
			x=0;
			y=0;
		}
	}
}
 