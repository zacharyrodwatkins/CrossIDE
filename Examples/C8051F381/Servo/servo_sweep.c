// servo_sweep.c:  Generates the PWM for servo motors.
//
// (c) 2008-2014, Jesus Calvino-Fraga
//
// ~C51~ 

#include <stdio.h>
#include <stdlib.h>
#include <c8051f38x.h>

#define MHZ 1000000L
#define SYSCLK (12*MHZ)  // Must be 12MHz in order to generate the slow 50Hz signal
#define BAUDRATE 115200L

#define HIGH(X) (X/0x100)
#define LOW(X) (X%0x100)

// For this macro, X is the time in seconds.  For example for 1.5ms, PCA_COUNT(1.5e-3)
#define PCA_COUNT(X) ((unsigned int)(X/(12.0/SYSCLK)))

//The two pins used to generate the signals
#define PWM1 P2_0
#define PWM2 P2_1

// ISR volatile variables
volatile unsigned char vCCAP1L;
volatile unsigned char vCCAP1H;
volatile unsigned char vCCAP2L;
volatile unsigned char vCCAP2H;
volatile unsigned char Cnt20ms;

char _c51_external_startup (void)
{
	PCA0MD&=(~0x40) ;    // DISABLE WDT: clear Watchdog Enable bit
	// CLKSEL&=0b_1111_1000; // Not needed because CLKSEL==0 after reset
	#if (SYSCLK == (12*MHZ))
		//CLKSEL|=0b_0000_0000;  // SYSCLK derived from the Internal High-Frequency Oscillator / 4 
	#elif (SYSCLK == (24*MHZ))
		CLKSEL|=0b_0000_0010; // SYSCLK derived from the Internal High-Frequency Oscillator / 2.
	#elif (SYSCLK == (48*MHZ))
		CLKSEL|=0b_0000_0011; // SYSCLK derived from the Internal High-Frequency Oscillator / 1.
	#else
		#error SYSCLK must be either 12MHZ, 24MHZ, or 48MHZ
	#endif
	OSCICN |= 0x03; // Configure internal oscillator for its maximum frequency
	
	VDM0CN=0x80;       // enable VDD monitor
	RSTSRC=0x02|0x04;  // Enable reset on missing clock detector and VDD
	P0MDOUT|=0x10;     // Enable Uart TX as push-pull output
	P2MDOUT|=0x03;     // P2.0 and P2.1 are the PWM outputs
	XBR0=0x01;         // Enable UART on P0.4(TX) and P0.5(RX)
	XBR1=0x40;         // Enable crossbar and weak pull-ups
	
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
		TH1 = 0x10000-(SYSCLK/BAUDRATE/2/48);
		CKCON &= ~0x0B; // T1M = 0; SCA1:0 = 10
		CKCON |=  0x02;
	#endif
	
	TL1 = TH1;     // Init timer 1
	TMOD &= 0x0f;  // TMOD: timer 1 in 8-bit autoreload
	TMOD |= 0x20;                       
	TR1 = 1;       // Start timer1
	SCON = 0x52;
	
	return 0;
}

void Servo_PWM_init(void)
{
	// Dissable interrupts
	EA=0;
	// Disable and clear everything in the PCA
	PCA0MD=0x00;
	// Initialize the PCA counter to zero
	PCA0L=0;
	PCA0H=0;
	// Configure PCA.  XTAL/12 is the frequency input for the PCA 
	PCA0MD=0x00;
	// Enable modules 0, 1, and 2 as comparators and to generate interrupts
	PCA0CPM0=PCA0CPM1=PCA0CPM2=ECOM|MAT|ECCF;
	// Module 0 is used to generate the 50Hz base frequency
	PCA0CPL0= LOW(PCA_COUNT(1.0/50.0)); //Always write low byte first!
	PCA0CPH0=HIGH(PCA_COUNT(1.0/50.0));
	// Set PWM 1 to 50%. According to the manual the pulse width
	// should be between 0.9ms and 2.1ms with the center at 1.5ms.
	PCA0CPL1= LOW(PCA_COUNT(1.5e-3)); //Always write low byte first!
	PCA0CPH1=HIGH(PCA_COUNT(1.5e-3));
	// PWM 2 to 50%
	PCA0CPL2= LOW(PCA_COUNT(1.5e-3)); //Always write low byte first!
	PCA0CPH2=HIGH(PCA_COUNT(1.5e-3));
	// Enable PCA counter
	CR=1;
	// Enable PCA interrupts	
	EIE1|=EPCA0;
	// Enable all interrupts
	EA=1;
}

void pwm_ISR (void) interrupt INTERRUPT_PCA0
{
	if(CCF0)
	{
		PCA0L=0;
		PCA0H=0;
		PWM1=PWM2=1;
		PCA0CPL1=vCCAP1L;
		PCA0CPH1=vCCAP1H;
		PCA0CPL2=vCCAP2L;
		PCA0CPH2=vCCAP2H;
		Cnt20ms++;
	}
	if (CCF1) PWM1=0;
	if (CCF2) PWM2=0;

	// Clear all the flags and leave the PCA enabled (CR=1, bit 6 of CCON)
	PCA0CN=0x40;
}

void wait (unsigned char max)
{
	Cnt20ms=0;
	while(Cnt20ms<max); // Cnt20ms is incremented at the rate of PCA's channel 0
}

void sweep(void)
{
	unsigned int pwmval;
	
	//This is more or less the range of the HS-422 servo
	#define min PCA_COUNT(0.6e-3)
	#define max PCA_COUNT(2.4e-3)
	#define inc ((max-min)/600)
	
	for(pwmval=min; pwmval<max; pwmval+=inc)
	{
		vCCAP1L= LOW(pwmval);
		vCCAP1H=HIGH(pwmval);
		wait(5); // 5*20ms = 100ms
	}
	for(pwmval=max; pwmval>min; pwmval-=inc)
	{
		vCCAP1L= LOW(pwmval);
		vCCAP1H=HIGH(pwmval);
		wait(5); // 5*20ms = 100ms
	}
}

void main (void)
{
	Servo_PWM_init();
				
	while (1)
	{
		sweep();
	}
}
