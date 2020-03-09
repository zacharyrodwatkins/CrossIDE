//  AT89LP51RC2 with LCD in 4-bit interface mode
//  Copyright (c) 2008-2018 Jesus Calvino-Fraga
//  ~C51~

#include <stdio.h>
#include <at89lp51rd2.h>

#define CLK    22118400L // SYSCLK frequency in Hz
#define BAUD     115200L // Baud rate of UART in bps

#define LCD_RS P1_1
#define LCD_RW P1_2 // Not used in this code
#define LCD_E  P1_3
#define LCD_D4 P3_2
#define LCD_D5 P3_3
#define LCD_D6 P3_4
#define LCD_D7 P3_5
#define CHARS_PER_LINE 16

#define XX (CLK/(16L*BAUD))

unsigned int one_usec_reload;

unsigned char _c51_external_startup(void)
{
	// If the ports are configured in compatibility mode, this is not needed.
	//P0M0=0; P0M1=0;
	//P1M0=0; P1M1=0;
	//P2M0=0; P2M1=0;
	//P3M0=0; P3M1=0;
	#if ((CLK/(16L*BAUD))>0x10000L)
	#error "Can not set baud rate because (CLK/(16L*BAUD)) > 0x10000L "
	#endif
    setbaud_timer2(0x10000L-CLK/(16L*BAUD)); // Initialize serial port using timer 2 (fast mode)
    
    one_usec_reload=CLK/1000000L;
    return 0;
}

void wait_us (unsigned char x)
{
	unsigned int j;
	
	TR0=0; // Stop timer 0
	TMOD&=0xf0; // Clear the configuration bits for timer 0
	TMOD|=0x01; // Mode 1: 16-bit timer
	
	if(x>5) x-=5; // Subtract the overhead
	else x=1;
	
	j=-one_usec_reload*x;
	TF0=0;
	TH0=j/0x100;
	TL0=j%0x100;
	TR0=1; // Start timer 0
	while(TF0==0); //Wait for overflow
}

void waitms (unsigned int ms)
{
	unsigned int j;
	unsigned char k;
	for(j=0; j<ms; j++)
		for (k=0; k<4; k++) wait_us(250);
}

void LCD_pulse (void)
{
	LCD_E=1;
	wait_us(40);
	LCD_E=0;
}

void LCD_byte (unsigned char x)
{
	// The accumulator in the 8051 is bit addressable!
	ACC=x; //Send high nible
	LCD_D7=ACC_7;
	LCD_D6=ACC_6;
	LCD_D5=ACC_5;
	LCD_D4=ACC_4;
	LCD_pulse();
	wait_us(40);
	ACC=x; //Send low nible
	LCD_D7=ACC_3;
	LCD_D6=ACC_2;
	LCD_D5=ACC_1;
	LCD_D4=ACC_0;
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

void LCD_4BIT (void)
{
	LCD_E=0; // Resting state of LCD's enable is zero
	LCD_RW=0; // We are only writing to the LCD in this program
	waitms(20);
	// First make sure the LCD is in 8-bit mode and then change to 4-bit mode
	WriteCommand(0x33);
	WriteCommand(0x33);
	WriteCommand(0x32); // Change to 4-bit mode

	// Configure the LCD
	WriteCommand(0x28);
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

void main (void)
{
	// Configure the LCD
	LCD_4BIT();
	
   	// Display something in the LCD
	LCDprint("LCD 4-bit test:", 1, 1);
	LCDprint("Hello, World!", 2, 1);
	
	printf("Hello, World!\n");
	
	while(1)
	{
		P3_7=0;
		waitms(500);
		P3_7=1;
		waitms(500);
	}
}
