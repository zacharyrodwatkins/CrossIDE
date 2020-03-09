#include <stdio.h>
#include <stdlib.h>
#include <c8051f38x.h>

#define SYSCLK 24000000L    // Internal oscillator frequency in Hz
#define BAUDRATE 115200L
#define F_SCK_MAX 2000000L  // Max SCK freq (Hz)

// Pins used by the SPI interface:
// 	P0.0: SCK
// 	P0.1: MISO
// 	P0.2: MOSI
// 	P0.3: SS*

#define ADC_CE P0_3
	
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
	
	VDM0CN=0x80;       // enable VDD monitor
	RSTSRC=0x02|0x04;  // Enable reset on missing clock detector and VDD
	OSCICN|=0x03;      // Configure internal oscillator for its maximum frequency

	P0MDOUT=0b_00011101;//SCK, MOSI, P0.3, TX0 are puspull, all others open-drain
	XBR0=0b_00000011;//SPI0E=1, URT0E=1
	XBR1=0b_01000000;//XBARE=1
	
	// Configure the serial port
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

	// SPI inititialization
	SPI0CFG = 0b_01000000; //SPI in master mode
	SPI0CN  = 0b_00000001; //SPI enabled and in three wire mode
	SPI0CKR = (SYSCLK/(2*F_SCK_MAX))-1;
	
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
void SPIWrite (unsigned char x)
{
   SPI0DAT=x;
   while(!SPIF);
   SPIF=0;
}

// Read 10 bits from ithe MCP3008 ADC converter using the recomended
// format in the datasheet.
unsigned int volatile GetADC(char channel)
{
	unsigned int adc;

	ADC_CE=0; //Select the MCP3008 converter.
	
	SPIWrite(0x01);//Send the start bit.
	SPIWrite((channel*0x10)|0x80);	//Send single/diff* bit,  D2, D1, and D0 bits.
	adc=((SPI0DAT & 0x03)*0x100);//SPI0DAT contains now the high part of the result.
	SPIWrite(0x55);//Dont' care what you send now.  0x55 looks good on the oscilloscope though!
	adc+=SPI0DAT;//SPI0DAT contains now the low part of the result. 
	
	ADC_CE=1; //Deselect the MCP3008 converter.
		
	return adc;
}

// Read 10 bits from ithe MCP3008 ADC converter using a
// longer sampling time.
unsigned int volatile GetADC_New(char channel)
{
	unsigned int adc;

	ADC_CE=0; //Select the MCP3008 converter.
	
	SPIWrite(0b0001_1000|channel);//Send the start bit, single/diff* bit,  D2, D1, and D0 bits.
	Timer3us(10); // Optional delay for longer sampling time
	SPIWrite(0x55);	//Dont' care what you send now.  0x55 looks good on the oscilloscope though!
	adc=((SPI0DAT & 0b0011_1111)*0x100);//SPI0DAT contains bits 9 downto 4.
	SPIWrite(0x55);//Dont' care what you send now.  0x55 looks good on the oscilloscope though!
	adc+=SPI0DAT;//SPI0DAT contains bits 3 downto 0.
	adc>>=4; // The result is shifted left four bits, therefore we shift it right four times.
	
	ADC_CE=1; //Deselect the MCP3008 converter.
		
	return adc;
}

// The Voltage reference input to the MCP3008, the '4.6V_out' pin
// from the F38x board, was measured as:
#define VREF 4.69
 
void main (void)
{
	printf("\x1b[2J"); // Clear screen using ANSI escape sequence.
	
	printf ("C805F38x SPI/MCP3008 test program\n"
	        "File: %s\n"
	        "Compiled: %s, %s\n\n",
	        __FILE__, __DATE__, __TIME__);
	
	while(1)
	{
		printf("V0=%5.3f, V1=%5.3f\r", (GetADC_New(0)*VREF)/1023.0, (GetADC_New(1)*VREF)/1023.0);
	}
}

