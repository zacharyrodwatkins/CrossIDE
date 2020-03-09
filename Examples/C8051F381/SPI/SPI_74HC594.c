#include <stdio.h>
#include <stdlib.h>
#include <c8051f330.h>

#define SYSCLK 24500000L    // Internal oscillator frequency in Hz
#define F_SCK_MAX 2000000L  // Max SCK freq (Hz)

#define BIN(x)                              \
  (  ((0x##x##L & 0x00000001L) ? 0x01 : 0)  \
   | ((0x##x##L & 0x00000010L) ? 0x02 : 0)  \
   | ((0x##x##L & 0x00000100L) ? 0x04 : 0)  \
   | ((0x##x##L & 0x00001000L) ? 0x08 : 0)  \
   | ((0x##x##L & 0x00010000L) ? 0x10 : 0)  \
   | ((0x##x##L & 0x00100000L) ? 0x20 : 0)  \
   | ((0x##x##L & 0x01000000L) ? 0x40 : 0)  \
   | ((0x##x##L & 0x10000000L) ? 0x80 : 0))

char _c51_external_startup (void)
{
	PCA0MD&=(~0x40) ;    // DISABLE WDT: clear Watchdog Enable bit
	
	VDM0CN=0x80;       // enable VDD monitor
	RSTSRC=0x02|0x04;  // Enable reset on missing clock detector and VDD
	OSCICN|=0x03;      // Configure internal oscillator for its maximum frequency

	// P0.0: SCK
	// P0.1: MISO
	// P0.2: MOSI
	// P0.3: NSS
	// P0.4: TX0
	// P0.5: RX0
	
	P0MDOUT=BIN(00011101);//SCK, MOSI, P0.3, TX0 are puspull, all others open-drain
	XBR0=BIN(00000011);//SPI0E=1, URT0E=1
	XBR1=BIN(01000000);//XBARE=1
	
	// Configure serial port and baud rate
	TR1=0;        // Disable timer 1
	TMOD=0x20;    // Set timer 1 as 8-bit autoreload
	CKCON=0x08;   // T1M = 1; SCA1:0 = xx
	TH1=0x96;     // for 115200 baud; check table 16.1 in C8051F330 manual
	TR1=1;        // Enable timer 1
	SCON=0x52;

	// SPI inititialization
	SPI0CFG = BIN(01000000); //SPI in master mode
	SPI0CN  = BIN(00000001); //SPI enabled and in three wire mode
	SPI0CKR = (SYSCLK/(2*F_SCK_MAX))-1;
	
	return 0;
}

void putchar (char c)
{
	while (!TI);
	TI=0;
	SBUF=c;
}

char getchar (void)
{
	while (!RI);
	RI=0;
	return SBUF;
}

void MyDelay (void)
{
	unsigned int j, k;
	for(k=0; k<10; k++)
		for (j=0; j<40000; j++);
}

void SendByteSPI (unsigned char x)
{
	SPI0DAT = x;
	while(!SPIF);
	SPIF = 0;
	P0_3 = 1; //Latch the output with one!
	P0_3 = 0;
}

void main (void)
{
	unsigned char j=0, x=0;
	
	printf ("\n\n\rSPI test program\n\r"
	        "File: %s\n\r"
	        "Compiled: %s, %s\n\r",
	        __FILE__, __DATE__, __TIME__);

	while(1)
	{
		switch(j)
		{
			case 0: x=~0x01; break;
			case 1: x=~0x02; break;
			case 2: x=~0x04; break;
			case 3: x=~0x08; break;
			case 4: x=~0x10; break;
			case 5: x=~0x20; break;
			case 6: x=~0x40; break;
			case 7: x=~0x80; break;
		}
		j++;
		if(j>7) j=0;
		SendByteSPI(x);
		MyDelay();
	}  
}	
