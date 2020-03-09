// F38x_I2C_Nunchuck_Serial_Mouse_No_RTS.c: Reads the WII nunchuck using the hardware I2C port
// available in the C8051F38x and reports it so to behave as a serial mouse.  This version 
// doesn't use the RTS# signal to determine when to send the mouse ID.  Instead it used time
// delays.
//
// http://wiibrew.org/wiki/Wiimote/Extension_Controllers
// http://wiibrew.org/wiki/Wiimote/Extension_Controllers/Nunchuck
//
// Some good information was found also here:
//
// http://forum.arduino.cc/index.php/topic,45924.0.html
//
// By:  Jesus Calvino-Fraga (c) 2010-2015
//
// The next line clears the "C51 command line options:" field when compiling with CrossIDE
//  ~C51~  

#include <C8051F38x.h>
#include <stdio.h>

#define  SYSCLK         24000000L // System clock frequency in Hz
#define  BAUDRATE       1200L     // The serial mouse uses 1200 baud
#define  SMB_FREQUENCY  100000L   // I2C SCL clock rate (10kHz to 100kHz)

#define MINCLIP 15
#define MAXCLIP (255-MINCLIP)

// This startup function is called automatically before the main() function
// in order to initialize the hardware.
char _c51_external_startup (void)
{
	PCA0MD&=(~0x40) ;  // DISABLE WDT: clear Watchdog Enable bit
	VDM0CN=0x80;       // Enable VDD monitor
	RSTSRC=0x02|0x04;  // Enable reset on missing clock detector and VDD

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
	TMOD &= 0x0f;  // Mask out timer 1 bits
	TMOD |= 0x20;  // TMOD: timer 1 in 8-bit autoreload                     
	TR1 = 1;       // Start timer1
	SCON = 0x52;

	// Initialize Crossbar and GPIO
	P0MDOUT = 0x10;           // Enable Uart TX as push-pull output
	XBR0 = 0b0000_0101;       // Enable SMBus pins and UART pins P0.4(TX) and P0.5(RX)
	XBR1 = 0x40;              // Enable crossbar and weak pull-ups
	
	// Configure Timer 0 as the I2C clock source
	CKCON |= 0x04; // Timer0 clock source = SYSCLK
	TMOD &= 0xf0;  // Mask out timer 1 bits
	TMOD |= 0x02;  // Timer0 in 8-bit auto-reload mode
	// Timer 0 configured to overflow at 1/3 the rate defined by SMB_FREQUENCY
	TL0 = TH0 = 256-(SYSCLK/SMB_FREQUENCY/3);
	TR0 = 1; // Enable timer 0
	
	// Configure and enable SMBus
	SMB0CF = INH | EXTHOLD | SMBTOE | SMBFTE ;
	SMB0CF |= ENSMB;  // Enable SMBus

	return 0;
}

// Uses Timer4 to delay <ms> mili-seconds. 
void Timer4ms(unsigned int ms)
{
	unsigned int i;// msec counter
	unsigned char k;
	
	k=SFRPAGE;
	SFRPAGE=0xf;
	// The input for Timer 4 is selected as SYSCLK by setting bit 0 of CKCON1:
	CKCON1|=0b_0000_0001;
	
	TMR4RL = 65536-(SYSCLK/1000L); // Set Timer4 to overflow in 1 ms.
	TMR4 = TMR4RL;                 // Initialize Timer4 for first overflow
	
	TMR4CN = 0x04;                 // Start Timer4 and clear overflow flag
	for (i = 0; i < ms; i++)       // Count <ms> overflows
	{
		while (!(TMR4CN & 0x80));  // Wait for overflow
		TMR4CN &= ~(0x80);         // Clear overflow indicator
	}
	TMR4CN = 0 ;                   // Stop Timer4 and clear overflow flag
	SFRPAGE=k;	
}

void I2C_write (unsigned char output_data)
{
	SMB0DAT = output_data; // Put data into buffer
	SI0 = 0;
	while (!SI0); // Wait until done with send
}

unsigned char I2C_read (void)
{
	unsigned char input_data;

	SI0 = 0;
	while (!SI0); // Wait until we have data to read
	input_data = SMB0DAT; // Read the data

	return input_data;
}

void I2C_start (void)
{
	ACK0 = 1;
	STA0 = 1;     // Send I2C start
	STO0 = 0;
	SI0 = 0;
	while (!SI0); // Wait until start sent
	STA0 = 0;     // Reset I2C start
}

void I2C_stop(void)
{
	STO0 = 1;  	// Perform I2C stop
	SI0 = 0;	// Clear SI
	//while (!SI0);	   // Wait until stop complete (Doesn't work???)
}

void nunchuck_init(void)
{
	unsigned char i, buf[6];
	
	// Older initialization format that works only for older nunchucks
	//I2C_start();
	//I2C_write(0xA4);
	//I2C_write(0x40);
	//I2C_write(0x00);
	//I2C_stop();
	
	// Newer initialization format that works for all nunchucks
	I2C_start();
	I2C_write(0xA4);
	I2C_write(0xF0);
	I2C_write(0x55);
	I2C_stop();
	Timer4ms(1);
	 
	I2C_start();
	I2C_write(0xA4);
	I2C_write(0xFB);
	I2C_write(0x00);
	I2C_stop();
	Timer4ms(1);

	// Read the extension type from the register block.  For the Nunchuk it should be
	// 00 00 a4 20 00 00       
	I2C_start();
	I2C_write(0xA4);
	I2C_write(0xFA); // extension type register
	I2C_stop();
	Timer4ms(3); // 3 ms required to complete acquisition

	I2C_start();
	I2C_write(0xA5);
	
	// Receive values
	for(i=0; i<6; i++)
	{
		buf[i]=I2C_read();
	}
	ACK0=0;
	I2C_stop();
	Timer4ms(3);
	
	printf("Extension type: %02x  %02x  %02x  %02x  %02x  %02x\n", 
		buf[0],  buf[1], buf[2], buf[3], buf[4], buf[5]);

	// Send the crypto key (zeros), in 3 blocks of 6, 6 & 4.

	I2C_start();
	I2C_write(0xA4);
	I2C_write(0xF0);
	I2C_write(0xAA);
	I2C_stop();
	Timer4ms(1);

	I2C_start();
	I2C_write(0xA4);
	I2C_write(0x40);
	I2C_write(0x00);
	I2C_write(0x00);
	I2C_write(0x00);
	I2C_write(0x00);
	I2C_write(0x00);
	I2C_write(0x00);
	I2C_stop();
	Timer4ms(1);

	I2C_start();
	I2C_write(0xA4);
	I2C_write(0x40);
	I2C_write(0x00);
	I2C_write(0x00);
	I2C_write(0x00);
	I2C_write(0x00);
	I2C_write(0x00);
	I2C_write(0x00);
	I2C_stop();
	Timer4ms(1);

	I2C_start();
	I2C_write(0xA4);
	I2C_write(0x40);
	I2C_write(0x00);
	I2C_write(0x00);
	I2C_write(0x00);
	I2C_write(0x00);
	I2C_stop();
	Timer4ms(1);
}

void nunchuck_getdata(unsigned char * s)
{
	unsigned char i;

	// Start measurement
	I2C_start();
	I2C_write(0xA4);
	I2C_write(0x00);
	I2C_stop();
	Timer4ms(3); 	// 3 ms required to complete acquisition

	// Request values
	I2C_start();
	I2C_write(0xA5);
	
	// Receive values
	for(i=0; i<6; i++)
	{
		s[i]=(I2C_read()^0x17)+0x17; // Read and decrypt
	}
	ACK0=0;
	I2C_stop();
}

// Seven bit version of putchar.  Just set the most significant bit to one.
void putchar (char c)
{
	while (!TI);
	TI=0;
	SBUF=(c|0x80);
}

void main (void)
{
	unsigned char rbuf[6], j;
 	char x, y, offx, offy;
 	bit BL, BR, sBL=0, sBR=0, gotRTS=0;
 	
	Timer4ms(800);
	putchar('M');
	Timer4ms(600);
	putchar('M');
	Timer4ms(400);
	putchar('M');
	Timer4ms(600);
	putchar('M');
	Timer4ms(400);
	putchar('M');
	Timer4ms(600);
	putchar('M');

	nunchuck_init();
	Timer4ms(100);
	
		nunchuck_getdata(rbuf);
		
	//clip top and bottom
	if(rbuf[0]>MAXCLIP) rbuf[0]=MAXCLIP;
	if(rbuf[0]<MINCLIP) rbuf[0]=MINCLIP;
	if(rbuf[1]>MAXCLIP) rbuf[1]=MAXCLIP;
	if(rbuf[1]<MINCLIP) rbuf[1]=MINCLIP;
	
	offx=((int)rbuf[0]-127);
	offy=-1*(((int)rbuf[1]-127));
	
	while(1)
	{
		nunchuck_getdata(rbuf);
		
		//clip top and bottom
		if(rbuf[0]>MAXCLIP) rbuf[0]=MAXCLIP;
		if(rbuf[0]<MINCLIP) rbuf[0]=MINCLIP;
		if(rbuf[1]>MAXCLIP) rbuf[1]=MAXCLIP;
		if(rbuf[1]<MINCLIP) rbuf[1]=MINCLIP;
		
		x=((int)rbuf[0]-127);
		y=-1*(((int)rbuf[1]-127));
		x-=offx;
		y-=offy;
		BL=(rbuf[5] & 0x01)?0:1;
		BR=(rbuf[5] & 0x02)?0:1;
		x/=8;
		y/=8;

		/*		
		Data is sent in 3 byte packets for each event (a button is pressed
		or released or the mouse moves):
		       D7 D6 D5 D4 D3 D2 D1 D0
		Byte 1 X  1  LB RB Y7 Y6 X7 X6
		Byte 2 X  0  X5 X4 X3 X2 X1 X0
		Byte 3 X  0  Y5 Y4 Y3 Y2 Y1 Y0
		*/
		
		if((BL!=sBL) || (BR!=sBR) || (x!=0) || (y!=0) )
		{
			sBL=BL;
			sBR=BR;

			j=0b_100_0000;
			if (BR) j|=0b_010_0000;
			if (BL) j|=0b_001_0000;
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
		else
		{
			Timer4ms(5); // The numchuck requires a delay between readings.
		}
	}
}
