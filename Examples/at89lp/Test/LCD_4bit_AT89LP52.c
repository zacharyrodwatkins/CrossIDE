//  AT89LP52 with LCD in 4-bit interface mode
//  Copyright (c) 2008-2015 Jesus Calvino-Fraga
//  ~C51~

#include <stdio.h>
#include <at89lp52.h>

#define CLK    22118400L // SYSCLK frequency in Hz
#define BAUD     115200L // Baud rate of UART in bps

#define LCD_RS P1_2
#define LCD_RW P1_3 // Not used in this code
#define LCD_E  P1_4
#define LCD_D4 P3_2
#define LCD_D5 P3_3
#define LCD_D6 P3_4
#define LCD_D7 P3_5
#define CHARS_PER_LINE 16

#define CDV (1<<((CLKREG&0x0E)>>1))
#define TPS ((CLKREG>>4)+1)

unsigned int one_usec_reload;

unsigned char _c51_external_startup(void)
{
	PMOD=0; // Configure ports as bidirectional with internal pull-ups.
	//CLKREG=0b01010010; // Default value in compatibility mode
    setbaud_timer2(0x10000L-CLK/(CDV*16L*BAUD)); // Initialize serial port using timer 2
    
    one_usec_reload=CLK/(CDV*TPS*1000000L);
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
	char buff[17];
	// Configure the LCD
	LCD_4BIT();
	
   	// Display something in the LCD
	LCDprint("LCD 4-bit test:", 1, 1);
	LCDprint("Hello, World!", 2, 1);
	
	printf("Hello, World!\n");
	
	sprintf(buff, "TPS=%d, CDV=%d", TPS, CDV);
	LCDprint(buff, 2, 1);
	
	while(1)
	{
		P3_7=0;
		waitms(300);
		P3_7=1;
		waitms(300);
	}
}
