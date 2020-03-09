// Serial_Mouse_Test_debug.c: Emulates the Microsoft's serial mouse.
// This version was used to find the times at which the RTS# signal
// are toggled.  It uses a LCD and an ISR for timer 2 to find
// and display such times.
//
// By:  Jesus Calvino-Fraga (c) 2015
//
// The next line clears the "C51 command line options:" field when compiling with CrossIDE
//  ~C51~  

#include <C8051f38x.h>
#include <stdio.h>
#include <limits.h>

#define RTS    P0_2
#define BR     P0_1
#define BL     P0_0
#define MU     P2_7
#define MD     P2_6
#define ML     P2_5
#define MR     P2_4
#define CLKOUT P2_3 // Must be 500Hz

#define LCD_RS P2_2
#define LCD_RW P2_1 // Not used in this code
#define LCD_E  P2_0
#define LCD_D0 P1_7
#define LCD_D1 P1_6
#define LCD_D2 P1_5
#define LCD_D3 P1_4
#define LCD_D4 P1_3
#define LCD_D5 P1_2
#define LCD_D6 P1_1
#define LCD_D7 P1_0
#define CHARS_PER_LINE 16

#define SYSCLK      24000000L  // SYSCLK frequency in Hz
#define BAUDRATE        1200L  // Baud rate of UART in bps

volatile unsigned int msCount;
volatile bit msCount_flag;

void PORT_Init (void)
{
	P0MDOUT|=0x10; // Enable Uart TX as push-pull output
	P1MDOUT|=0b_1111_1111; // LCD's D0 to D7 are connected to P1.7 to P1.0
	P2MDOUT|=0b_0000_1111; // P2.2 is LCD's RS, P2.1 is LCD's RW, P2.0 is LCD's E
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

void Timer2_Init (void)
{
	// Initialize timer 2 for periodic interrupts
	TMR2CN=0x00;   // Stop Timer2; Clear TF2;
	// The input for Timer 2 is selected as SYSCLK by setting T2ML (bit 4) of CKCON:
	CKCON|=0b_0001_0000;
	TMR2RL=(-(SYSCLK/1000L)); // Initialize reload value for one millisecond (1000Hz)
	TMR2=0xffff;   // Set to reload immediately
	ET2=1;         // Enable Timer2 interrupts
	TR2=1;         // Start Timer2

	EA=1; // Enable interrupts
}

void Timer2_ISR (void) interrupt 5
{
	TF2H = 0; // Clear Timer2 interrupt flag
	CLKOUT=!CLKOUT;
	msCount++;
}

void Set_msCount (unsigned int x) {
    do {
        msCount_flag=0;
        msCount=x;
    } while (msCount_flag);
}

unsigned int Get_msCount (void){
    volatile unsigned int x;
    do {
        msCount_flag=0;
        x=msCount;
    } while (msCount_flag);
    return x;
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

void LCD_pulse (void)
{
	LCD_E=1;
	Timer3us(40);
	LCD_E=0;
}

void LCD_byte (unsigned char x)
{
	// The accumulator in the C8051F381 is bit addressable!
	ACC=x;
	LCD_D0=ACC_0;
	LCD_D1=ACC_1;
	LCD_D2=ACC_2;
	LCD_D3=ACC_3;
	LCD_D4=ACC_4;
	LCD_D5=ACC_5;
	LCD_D6=ACC_6;
	LCD_D7=ACC_7;
	LCD_pulse();
}

void WriteData (unsigned char x)
{
	LCD_RS=1;
	LCD_byte(x);
	waitms(2);
}

void WriteCommand (unsigned char x)
{
	LCD_RS=0;
	LCD_byte(x);
	waitms(5);
}

void LCD_8BIT (void)
{
	LCD_E=0;  // Resting state of LCD's enable is zero
	LCD_RW=0; // We are only writing to the LCD in this program
	waitms(20);
	// First make sure the LCD is in 8-bit mode
	WriteCommand(0x33);
	WriteCommand(0x33);
	WriteCommand(0x33); // Stay in 8-bit mode

	// Configure the LCD
	WriteCommand(0x38);
	WriteCommand(0x0c);
	WriteCommand(0x01); // Clear screen command (takes some time)
	waitms(20); // Wait for clear screen command to finsih.
}

void LCDprint(char * string, unsigned char line, bit clear)
{
	int j;

	WriteCommand(line==2?0xc0:0x80);
	waitms(5);
	for(j=0; string[j]!=0; j++)	WriteData(string[j]);// Write the message
	if(clear) for(; j<CHARS_PER_LINE; j++) WriteData(' '); // Clear the rest of the line
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
	bit gotRTS=0, sBL=0, sBR=0;
	unsigned char j;
	char x=0, y=0;
	unsigned char RTS_count=0;
	unsigned int ms[8];
	char buff[17];
	
	PCA0MD &= ~0x40; // WDTE = 0 (clear watchdog timer enable)
	PORT_Init();     // Initialize Port I/O
	SYSCLK_Init ();  // Initialize Oscillator
	Timer2_Init();
	Set_msCount(0);
	UART0_Init();    // Initialize UART0

	// Configure the LCD (note: configuring the LCD and displaying
	// the initial message has no impact in the timming as the first
	// RTS# toggle occurs after about 400ms
	LCD_8BIT();
	
   	// Display something in the LCD
	LCDprint("Serial Mouse", 1, 1);
	LCDprint("Test", 2, 1);
	
	while(1)
	{	
		while(RTS==1) gotRTS=1; // Reset state
		
		if(gotRTS)
		{
			if(RTS_count<8)
			{
				ms[RTS_count++]=Get_msCount();
			}
			gotRTS=0; 
			putchar('M');
		}
		
		if(Get_msCount()>4000)
		{
			TR2=0; // Stop Timer2
			Set_msCount(0);
			// Display the times at which the 'M' was sent
			sprintf(buff,"%d:%4d,%4d,%4d", RTS_count, ms[0], ms[1], ms[2]);
			LCDprint(buff, 1, 1);  
			sprintf(buff,"%4d,%4d,%4d", ms[3], ms[4], ms[5]);
			LCDprint(buff, 2, 1);  
		}
		
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


 