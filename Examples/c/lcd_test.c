// ~C51~   

#include <DE2_8052.h>

void Wait40us(void)
{
	_asm
		push AR0
		mov R0, #200
	X1: 
		nop
		nop
		nop
		nop
		nop
		nop
		djnz R0, X1 ; 9 machine cycles-> 9*30ns*200>40us
	    pop AR0
    _endasm;
}

// These are the available LCD commands

/*
0x01        Clear display screen
0x02        Return Home
0x04        Decrement cursor (shift cursor to left)
0x05        Increment cursor (shift cursor to right)
0x06        shift display right
0x07        shift display left
0x08        Display off, cursor off
0x0A        Display off, cursor on
0x0C        Display on, cursor off
0x0E        Display on, cursor blinking
0x0F        Display on, cursor blinking
0x10        Shift cursor position to left
0x14        Shift cursor position to right
0x18        Shift the entire display to the left
0x1C        Shift the entire display to the right
0x80        Force cursor to the beginning of 1st line
0xC0        Force cursor to the beginning of 2nd line
0x38        8-bits interface, 2 lines, 5x7 characters*/

void LCD_command (unsigned char c)
{
	LCD_DATA=c;
	LCD_RS=0;
	LCD_EN=1;
	LCD_EN=0;
	Wait40us();
}

void LCD_data (unsigned char c)
{
	LCD_DATA=c;
	LCD_RS=1;
	LCD_EN=1;
	LCD_EN=0;
	Wait40us();
}


void LCD_puts(char * str)
{
	char j;
	for(j=0; str[j]!=0; j++)
	{
		LCD_data(str[j]);
	}
}

void main (void)
{
	char j;
	
	//Turn off all LEDs
	HEX0=0xff;
	HEX1=0xff;
	HEX2=0xff;
	HEX3=0xff;
	HEX4=0xff;
	HEX5=0xff;
	HEX6=0xff;
	HEX7=0xff;
	LEDRA=0;
	LEDRB=0;
	LEDRC=0;
	LEDG=0;
	
	//Quick test of the LCD
	
	LCD_ON=1; // Turn LCD on, and wait a bit.
	Wait40us();

	LCD_MOD=0xff; // Use LCD_DATA as output port
	LCD_RW=0; // Only writing to the LCD in this code.
	
	LCD_command(0x0c); // Display on command
	LCD_command(0x38); // 8-bits interface, 2 lines, 5x7 characters
	LCD_command(0x01); // Clear screen (Warning, very slow command!)
	for(j=0; j<100; j++) Wait40us(); // Delay loop needed for 'clear screen' command above

	LCD_command(0x80); // Move to first column of first row
	LCD_puts("Hello World!");

	LCD_command(0xC0); // Move to first column of second row
	LCD_puts("Second LCD line.");
}
