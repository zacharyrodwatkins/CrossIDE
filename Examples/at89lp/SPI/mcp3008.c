#include <stdio.h>
#include <at89lp6440.h>

// ~C51~  

#define CLK 3686400L
#define BAUD 115200L
#define TIMER_2_RELOAD (0x10000L-(CLK/(16L*BAUD)))

void SPIWrite(unsigned char value)
{
	SPIF=0;
	SPDR=value;
	while(SPIF==0); //Wait for transmission to end
}

/*Read 10 bits from ithe MCP3004 ADC converter*/
unsigned int volatile GetADC(char channel)
{
	unsigned int adc;

	// initialize the SPI port to read the MCH3008 ADC attached to it.
	SSIG=1;
	SPCR=SPE|MSTR|CPOL|CPHA|SPR1|SPR0; //Mode (1,1): see figure 6-1 of MCP3004 datasheet.
	
	P1_4=0; //Select the MCP3004 converter.
	
	SPIWrite(0x01);//Send the start bit.
	SPIWrite((channel*0x10)|0x80);	//Send single/diff* bit,  D2, D1, and D0 bits.
	adc=((SPDR & 0x03)*0x100);//SPDR contains now the high part of the result.
	SPIWrite(0x55);//Dont' care what you send now.  0x55 looks good on the oscilloscope though!
	adc+=SPDR;//SPDR contains now the lows part of the result. 
	
	P1_4=1; //Deselect the MCP3004 converter.
		
	return adc;
}
 
void main (void)
{
	CLKREG=0x00; // TPS=0000B
	setbaud_timer2(TIMER_2_RELOAD); // Initialize serial port using timer 2 
	printf("\n\nAT89LP6440 SPI test program.\n");
	
	while(1)
	{
		printf("V=%5.3f\r", (GetADC(0)*3.323)/1023.0);
	}
}
