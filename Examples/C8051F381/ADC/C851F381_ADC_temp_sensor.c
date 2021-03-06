// C8051F381_ADC_temp_sensor.c:  Shows how to use the 10-bit ADC.  This program
// measures the temperature using the built-in sensor in the C8051F38x.
//
// (c) 2008-2014, Jesus Calvino-Fraga
//

#include <stdio.h>
#include <stdlib.h>
#include <c8051f38x.h>

// ~C51~  

#define SYSCLK 48000000L
#define BAUDRATE 115200L

char _c51_external_startup (void)
{
	PCA0MD&=(~0x40) ;    // DISABLE WDT: clear Watchdog Enable bit
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
	OSCICN |= 0x03; // Configure internal oscillator for its maximum frequency
	
	// Init ADC multiplexer to read the voltage between the temperature sensor and ground.
	// IMPORTANT: check section 6.5 in datasheet.  The constants for each input to the
	// multiplexer are available in "c8051f38x.h" both for the 32 and 48 pin packages.
	AMX0P = LQFP32_MUX_TEMP; // Select positive input from temperature sensor
	AMX0N = LQFP32_MUX_GND;  // GND is negative input (Single-ended Mode)
	
	// Init ADC
	ADC0CF=0xF8; // SAR clock = 31, Right-justified result
	ADC0CN=0b_1000_0000; // AD0EN=1, AD0TM=0
  	REF0CN=0b_0000_1100; //Select VDD as the voltage reference for the converter and turn temperature sensor on
  
	VDM0CN=0x80;       // enable VDD monitor
	RSTSRC=0x02|0x04;  // Enable reset on missing clock detector and VDD
	P0MDOUT|=0x10;     // Enable Uart TX as push-pull output
	P1MDOUT|=0x30;     // Initialize RLED and GLED as push-pull outputs
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

#define VDD 3.325 // The measured value of VDD in volts

void main (void)
{
	unsigned int temp_val;
	float vtemp, temp;

	printf("\x1b[2J"); // Clear screen using ANSI escape sequence.
	
	printf ("ADC test using built-in temperature sensor\n"
	        "File: %s\n"
	        "Compiled: %s, %s\n\n",
	        __FILE__, __DATE__, __TIME__);

	AD0BUSY = 1;     //  Start ADC 0 conversion to measure temperature
	while (AD0BUSY); //  Wait for conversion

	while(1)
	{
		AD0BUSY = 1;     //  Start ADC 0 conversion to measure temperature
		while (AD0BUSY); //  Wait for conversion

		temp_val = ADC0L + (ADC0H * 0x100);
		vtemp=(temp_val*VDD)/1024.0; // this is in volts
		
		// To get the temperature, use the formula in the datasheet from Figure 6.2. "Typical
		// Temperature Sensor Transfer Function" and the typical constants from
		// Table 5.11. "Temperature Sensor Electrical Characteristics":
		// vtemp(mv) = Slope(mv/oC)*temp + Offset(mV), were Slope=2.87 and Offset=764
		temp=(vtemp*1000.0-764.0)/2.87;

		printf ("Temperature=%4.2f C\r", temp);
		waitms(100);
	 }  
}	

