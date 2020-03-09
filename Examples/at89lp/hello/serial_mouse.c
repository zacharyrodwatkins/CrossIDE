#include <stdio.h>
#include <at89lp51rd2.h>

// ~C51~  

#define CLK 22118400L
#define BAUD 1200L
#define TIMER_2_RELOAD (0x10000L-(CLK/(32L*BAUD)))

// timer 0 used for system clock
#define TIMER0_RELOAD_VALUE (65536L-(CLK/(12*1000L)))

volatile unsigned int ms;
volatile bit ms_flag;
volatile unsigned int tick;

#define DTR P1_1
#define RTS P1_2
#define BUTTON P2_0
unsigned char _c51_external_startup(void)
{
	// Configure ports as a bidirectional with internal pull-ups.
	P0M0=0;	P0M1=0;
	P1M0=0;	P1M1=0;
	P2M0=0;	P2M1=0;
	P3M0=0;	P3M1=0;
	AUXR=0B_0001_0001; // 1152 bytes of internal XDATA, P4.4 is a general purpose I/O
	P4M0=0;	P4M1=0;
    setbaud_timer2(TIMER_2_RELOAD); // Initialize serial port using timer 2

	TMOD =(TMOD&0xf0)|0x01; // T0=16bit timer
	TL0=RL0=TIMER0_RELOAD_VALUE&0xff;
	TH0=RH0=TIMER0_RELOAD_VALUE>>8;
	TR0=1; // start timer 0 (bit 4 in TCON)
	ET0=1; // enable timer 0 interrupt
	EA=1; // enable global interrupt
    
    // Make pins input
    DTR=1;
    RTS=1;
    BUTTON=1;
    
    return 0;
}

void ClockIrqHandler (void) interrupt 1 using 1
{
	ms++;
	ms_flag=1;
	tick++;
}

unsigned int Read_ms(void)
{
	unsigned int j;
	do {
		ms_flag=0;
		j=ms;
	} while (ms_flag==1);
	return j;
}

void Write_ms(unsigned int j)
{
	do {
		ms_flag=0;
		ms=j;
	} while (ms_flag==1);
}

void waitms (unsigned int n)
{
	Write_ms(0);
	while(Read_ms()<n);
}

// Seven bit version of putchar.  We just need the most significant bit set to one
void putchar (char c)
{
	if (c=='\n')
	{
		while (!TI);
		TI=0;
		SBUF=('\r'|0x80);
	}
	while (!TI);
	TI=0;
	SBUF=(c|0x80);
}

void main (void)
{
	bit got_reset=0;

	while(1)
	{	
		while ((RTS==1))
		{
			got_reset=1;
		}		
		
		if(got_reset)
		{
			got_reset=0;
			waitms(14);
			putchar('M');
		}
				
		if(BUTTON==0)
		{
			putchar(0b_1110_0000);
			putchar(0b_1000_0000);
			putchar(0b_1000_0000);
			while (BUTTON==0);
			putchar(0b_1100_0000);
			putchar(0b_1000_0000);
			putchar(0b_1000_0000);
		}
	}
}
