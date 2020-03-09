//  C8051F38c (16k Flash) bootloader
//  Copyright (c) 2008-2014 Jesus Calvino-Fraga
//  Compile with C51 using ~C51~  --acall-ajmp --code-loc 0x3e00 --code-size 0x200
//  Always make sure that this bootloader fits in one page (512 bytes)

#define BOOT_START 0x3e00

#include <C8051F38x.h>

#define putc(c) { while(!TI); TI=0; SBUF=c; }

#define FLASHBYTE(X,Y) \
{ 	FLKEY  = 0xA5; \
	FLKEY  = 0xF1; \
	PSCTL  = 0x01; \
	*((unsigned char xdata *) X)=Y; \
	PSCTL  = 0x00;}

#define ERASEPAGE(X) \
{	FLKEY  = 0xA5; \
	FLKEY  = 0xF1; \
	PSCTL  = 0x03; \
	*((unsigned char xdata *) X)=0; \
	PSCTL  = 0x00;	}
	
#define READBYTE(X) (*((unsigned char code *) X))

#define SYSCLK    24000000L // SYSCLK frequency in Hz
#define BAUDRATE    115200L // Baud rate of UART in bps

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
	    jnb _P0_4, do_main ; Bootloader required after reset?
		ljmp (BOOT_START-3) ; Run user code. The first three bytes of user code were moved here.
	    do_main:
        ; Disable the WDT ASAP!
        anl _PCA0MD, #not(0x40) ; Clear Watchdog Enable Bit
	    mov	sp, #_stack_start-1
	    do_wait_release:
	    jnb _P0_4, do_wait_release
	    acall	_main
    _endasm;
}

void loadintelhex (void)
{
	volatile unsigned int address;
	unsigned int i;
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
				if(j<MAXBUFF) buff[j]=n; //  Don't overrun the buffer
				checksum+=n;
			}
			
			checksum+=getbyte();
			if(size>MAXBUFF) checksum=1; // Force a checksum error
	
			if(checksum==0) switch(type)
			{
				case 4: // Erase command.
					//Erase each page of flash IN REVERSE ORDER!  This way either
					//the original ljmp to the bootloader at address 0x0000 is preserved,
					//or a bunch of MOV A,R7 (opcode 0xff) will be in memory if something
					//happens (cancel, power failure, etc.).  In either case the
					//bootloader will eventualy run with the next reset!
					address=BOOT_START;
					while(address!=0)
					{
						address-=0x200;
					    ERASEPAGE(address);
					} 
					
					// Since we erased page 0, put a ljmp to the bootloader
					// at address 0x0000.  Notice that there is no 'break' after
					// the assigments below, therefore 'case 0:' follows and flashes
					// a ljmp to the bootloader: 02 fa 00 = ljmp 0xfa00
					size=3;
					buff[0]=0x02;
					buff[1]=BOOT_START/0x100;
					buff[2]=BOOT_START%0x100;

				case 0: // Write to flash command.
					for(j=0; j<size; j++)
					{
						if(address<BOOT_START) // Don't overwrite the bootloader!
						{
							i=address;
							if((i<3) && (type==0)) i+=(BOOT_START-3); // Save user code start address
							FLASHBYTE(i, buff[j]); // Write flash using MOVX
							if (READBYTE(i)!=buff[j]) echo='!'; // Read flash using MOVC
						}
						address++;
					}
				break;
				
				case 3: // Send ID number command.
					putc('3');
					putc('8');
					putc('C');
				break;
				
				case 1: // End record command; ignore it!
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
	VDM0CN=0x80; // enable VDD monitor
	RSTSRC=0x02|0x04; // Enable reset on missing clock detector and VDD
	
	P0MDOUT|=0x10; // Enable Uart TX as push-pull output
	XBR0=0x01; // Enable UART on P0.4(TX) and P0.5(RX)                     
	XBR1=0x40; // Enable crossbar and weak pull-ups
	
	// CLKSEL&=0b_1111_1000; // Not needed because CLKSEL==0 after reset
#if (SYSCLK == 12000000L)
   //CLKSEL|=0b_0000_0000;  // SYSCLK derived from the Internal High-Frequency Oscillator / 4 
#elif (SYSCLK == 24000000L)
	CLKSEL|=0b_0000_0010;   // SYSCLK derived from the Internal High-Frequency Oscillator / 2.
#elif (SYSCLK == 48000000L)
	CLKSEL|=0b_0000_0011;   // SYSCLK derived from the Internal High-Frequency Oscillator / 1.
#else
#error SYSCLK must be either 12000000L, 24000000L, or 48000000L
#endif
	OSCICN |= 0x03;   // Configure internal oscillator for its maximum frequency

	// Configure serial port and baud rate
	TR1=0; // Disable timer 1
	TMOD &= 0x0f;  // TMOD: timer 1 in 8-bit autoreload
	TMOD |= 0x20;                       
#if (SYSCLK/BAUDRATE/2L/256L < 1)
	TH1 = 0x10000-((SYSCLK/BAUDRATE)/2L);
	CKCON &= ~0x0B; // T1M = 1; SCA1:0 = xx
	CKCON |=  0x08;
#elif (SYSCLK/BAUDRATE/2L/256L < 4)
	TH1 = 0x10000-(SYSCLK/BAUDRATE/2L/4L);
	CKCON &= ~0x0B; // T1M = 0; SCA1:0 = 01                  
	CKCON |=  0x01;
#elif (SYSCLK/BAUDRATE/2L/256L < 12)
	TH1 = 0x10000-(SYSCLK/BAUDRATE/2L/12L);
	CKCON &= ~0x0B; // T1M = 0; SCA1:0 = 00
#else
	TH1 = -(SYSCLK/BAUDRATE/2/48);
	CKCON &= ~0x0B; // T1M = 0; SCA1:0 = 10
	CKCON |=  0x02;
#endif
	TR1=1; // Enable timer 1
	SCON=0x52;

	loadintelhex();
}

// On power-on reset, jump to the bootloader at address BOOT_START
void bootloader (void) _naked
{
	_asm
		CSEG at 0x0000
	    ljmp BOOT_START
	    CSEG at 0x3fff ; Lock byte location
	    db 0xff ; Do not lock any pages
	_endasm;
}