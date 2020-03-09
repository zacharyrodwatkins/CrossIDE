//  at89lp* bootloader common functions
//  Copyright (c) 2008-2012 Jesus Calvino-Fraga

#include <stdio.h>
#ifndef CLK
#define CLK 22118400L
#endif
#define BAUD 115200L
#define TIMER_2_RELOAD (0x10000L-(CLK/(16L*BAUD))) // Baud rate with clock = fosc/1
#define LOW(X)  (X%0x100)
#define HIGH(X) (X/0x100)

#define putc(c) { while(!TI); TI=0; SBUF=c; }
#define READBYTE(X) (*((unsigned char code *) X))
#ifndef PUSHBUTTON
#define PUSHBUTTON P3_1
#endif
#define RXD P3_0

sfr16 at (0xcdcc) TMR2;
sfr16 at (0xcbca) TMR2RELOAD;

void erasepage (unsigned int address)
{
	address;
	MEMCON=IAP|AERS|MWEN ;
	ACC=0xff;
	_asm
		movx @DPTR, A
	_endasm;
	//MEMCON=0;
}

void flashbuffer (unsigned int address, unsigned char value)
{
	if((address&(BUFFER_SIZE-1))==(BUFFER_SIZE-1)) // If last byte of buffer do flash
		MEMCON=IAP|MWEN;
	else
		MEMCON=IAP|MWEN|LDPG; // If not last byte of buffer save to buffer
	ACC=value;
	_asm
		movx @DPTR, A
	_endasm;
}

char getchar(void)
{
	char c;
	while (!RI);
	RI=0;
	c=SBUF;
	putc(c);
	return c;
}


unsigned char chartohex(char c)
{
	if(c & 0x40) c+=9; //  a to f or A to F
	return (c & 0xf);
}

// Get a byte from the serial port without echo
unsigned char getbyte (void)
{
	volatile unsigned char j; // volatile variable eliminates some push/pop instrutions

	j=chartohex(getchar())*0x10;
	j|=chartohex(getchar());
	return j;
}

void nocrtinit (void) _naked
{
	_asm
	    rseg R_GSINIT
	    public _crt0
	    _crt0:
	    mov	sp,#_stack_start-1
	    acall	_main
    _endasm;
}

void loadintelhex (void)
{
	volatile unsigned int address;
	volatile unsigned char j, size, type, checksum, n;
	#define MAXBUFF 64
	unsigned char buff[MAXBUFF];
	volatile char echo;

	while(1)
	{
		n=getchar();
		
		if(n==':')
		{
			echo='.'; // If everything works out, send a period...
			size=getbyte();
			checksum=size;
			
			address=getbyte();
			checksum+=address;
			address*=0x100;
			n=getbyte();
			checksum+=n;
			address+=n;
			
			type=getbyte();
			checksum+=type;

			for(j=0; j<size; j++)
			{
				n=getbyte();
				if(j<MAXBUFF) //  Don't overrun the buffer
				{
					buff[j]=n; 
					checksum+=n;
				}
			}
			checksum+=getbyte();
	
			if(checksum==0) switch(type)
			{
				case 3: // Erase command.
					if(buff[0]==0x07)
					{
						//Erase each flash page IN REVERSE ORDER!  This way either
						//the original ljmp to the bootloader at address 0x0000 is preserved,
						//or a bunch of MOV A,R7 (opcode 0xff) will be in memory if something
						//happens (cancel, power failure, etc.).  In either case the
						//bootloader will eventualy run with the next reset!
						address=BOOT_START;
						while(address!=0)
						{
							address-=PAGE_SIZE;
							erasepage(address);
						}
					}
					
				break;
				
				case 0: // Write to flash command.
					for(j=0; j<size; j++)
					{
						if(address<BOOT_START) // Don't overwrite the bootloader!
						{
							flashbuffer(address++, buff[j]); // Write flash using MOVX
						}
					}
					//MEMCON=0;
				break;
				
				case 5: // Read command
					if(buff[0]==0x00)
					{
						putc(ID_STR[buff[1]*2]);
						putc(ID_STR[buff[1]*2+1]);
					}
				break;
				
				case 1: // End record command
				break;
				
				default: // Unknown command;
					echo='?';
				break;
			}
			else echo='X'; // Checksum error
			
			putc(echo);
		}
	}
}

void main (void)
{
	unsigned char i;
	
	
	if(PUSHBUTTON==0) // Button pressed?
	{
#ifdef REG_AT89LP52_H
		CLKREG=0x52; // Works both for compatibility and fast mode
#endif
		while(PUSHBUTTON==0); // Wait for the button to be released
		PMOD=0; // Configure ports as bidirectional with internal pull-ups.
		// The POR values of CLKREG is zero, that is why it is commented here:
		// CLKREG=0x00; // TPS=0000B
		
		// Autobaud: Measure the width of 8 bits and divide it by 16*8.
		// The host must send 0x55 for this to work.

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
		loadintelhex();
	}
	else // Run user program with default power-on SFR values
	{
		_asm
			usercode:
			mov sp, #0x7 ; Default stack on power on reset
			ljmp BOOT_START-3 ; The first three bytes of user code were moved here
		_endasm;
	}
}

// On power-on reset, jump to the bootloader at address MAX_ADDRESS-512
void bootloader (void) _naked
{
	_asm
	    CSEG at 0
	    ljmp BOOT_START
	_endasm;
}
