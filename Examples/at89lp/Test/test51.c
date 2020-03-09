#include <stdio.h>
#include <at89lp51rd2.h>
#include <ctype.h>
#include <string.h>

#include "test.h"

#define EQ(A,B) !strcmp((A),(B))
#define LCD_RS P1_2
#define LCD_E  P1_3

#define CLK 22118400L
#define BAUD 115200L
#define TIMER_2_RELOAD (0x10000L-(CLK/(16L*BAUD)))

// timer 0 used for systemclock
#define TIMER0_RELOAD_VALUE -CLK/12/1000 // 0.99938916ms for 22.1184Mhz

unsigned char IE_save;

code char * code cmdtbl[]={
	"",
	"HELP",
	"?",
	"QUIT",
	"EXIT",
	"LCD1",
	"LCD2",
	"COUNT",
	"CLEAR",
	"CLS",
	"ADC",
	"V",
	"MAP",
	"BREAK"
};

typedef enum cmd_ID {
	ID_empty,
	ID_help,
	ID_qm,
	ID_quit,
	ID_exit,
	ID_lcd1,
	ID_lcd2,
	ID_count,
	ID_clear,
	ID_cls,
	ID_adc,
	ID_v,
	ID_map,
	ID_break,
	ID_invalid
};

unsigned int timer_count;

static long data milliSeconds;
volatile unsigned int Timer0_count;
volatile bit ISR_Timer0_flag;

void ClockIrqHandler (void) interrupt 1 using 1
{
	TL0 = TIMER0_RELOAD_VALUE&0xff;
	TH0 = TIMER0_RELOAD_VALUE>>8;
	Timer0_count++;
	ISR_Timer0_flag=1;
}

void Set_ISR_Timer0_Count (unsigned int x)
{
    do {
        ISR_Timer0_flag=0;
        Timer0_count=x;
    } while (ISR_Timer0_flag);
}

unsigned int Get_ISR_Timer0_Count (void)
{
    volatile unsigned int x;
    do {
        ISR_Timer0_flag=0;
        x=Timer0_count;
    } while (ISR_Timer0_flag);
    return x;
}

void WaitXms (unsigned int x)
{ 
    Set_ISR_Timer0_Count(0);
    while (Get_ISR_Timer0_Count()< x) ; 
}

unsigned char _c51_external_startup(void)
{
	setbaud_timer2(TIMER_2_RELOAD); // Initialize serial port using timer 2
	// initialize timer0 for system clock
	TR0=0; // stop timer 0
	TMOD =(TMOD&0xf0)|0x01; // T0=16bit timer
	// timeout is xtal/12
	TL0 = -TIMER0_RELOAD_VALUE&0xff;
	TH0 = -TIMER0_RELOAD_VALUE>>8;
	milliSeconds=0; // reset system time
	TR0=1; // start timer 0 (bit 4 in TCON)
	ET0=1; // enable timer 0 interrupt
	
	EA=1; // enable global interrupt
	
	return 0;
}


//If this is not present the monitor will complain, and this program will
//probably hang if ran with the monitor.
void need_by_the_monitor (void) interrupt 3 
{
	printf("CMON51 not present! Can not exit or break.\n");
}

void Delay_LCD(unsigned int mseg)
{
	unsigned char j;
	while(--mseg)
	{
		for(j=0; j<100; j++);
	}
}

void LCD_pulse (void)
{
	LCD_E=1;
	Delay_LCD(5);
	LCD_E=0;
	Delay_LCD(5);
}

void WriteData (unsigned char x)
{
	//Send high nible
	LCD_RS=1;
	P0=x;
	LCD_pulse();
	//Send low nible
	P0=x*0x10;
	LCD_pulse();
}

void WriteCommand (unsigned char x)
{
	//Send high nible
	LCD_RS=0;
	P0=x;
	LCD_pulse();
	//Send low nible
	P0=x*0x10;
	LCD_pulse();
}

void LCD_4BIT (void)
{
	WaitXms(100);
	// First make sure the LCD is in 8-bit mode
	LCD_RS=0;
	P0=0x30;
	// Three writes ensure 8-bit mode
	LCD_pulse();
	LCD_pulse();
	LCD_pulse();
	
	// Now we can set the LCD to 4-bit mode!
	P0=0x20;
	LCD_pulse();
	
	WriteCommand(0x28);
	WriteCommand(0x0c);
	WriteCommand(0x01); // Clear screen command
}

void LCDprint(char * string, unsigned char line, bit clear)
{
	int j;

	if(clear)
	{
		WriteCommand(line==2?0xc0:0x80);/*Go to the first column*/
		Delay_LCD(5);

		for(j=0; j<=24; j++) /*Clear the whole line*/
		{
			WriteData(' ');
			Delay_LCD(5);
		}
	}

	WriteCommand(line==2?0xc0:0x80);
	Delay_LCD(5);

	for(j=0; string[j]!=0; j++)	/*Write the message*/
	{
		WriteData(string[j]);
		Delay_LCD(5);
	}
}

void SPIinit (void)
{
	SPSTA=REMAP;
	SPCON=0;
	SPCON=MSTR|CPOL|CPHA|SPR1|SPR0|SSDIS;
	SPCON|=SPEN;
}

void SPIWrite(unsigned char value)
{
	SPSTA&=(~SPIF); //Clear the SPIF flag in SPSR
	SPDAT=value; //Send the start bit
	while((SPSTA & SPIF)!=SPIF); //Wait for transmission to end
}

/*Read 12 bits from ithe MCP3208 ADC converter*/
unsigned int volatile GetADC(char channel)
{
	unsigned int adc;

	P1_4=0; //Select the MCP3208 converter.
	
	SPIWrite((channel>3)?0x07:0x06);//Send the start bit, single/diff* bit, and D2 bit
	SPIWrite(channel*0x40);	//Send D1 and D2 bits
	adc=((SPDAT & 0x0f)*0x100);//SPDR contains now the high part of the result.
	SPIWrite(0x55);//Dont' care what you send now.  0x55 looks good on the oscilloscope though!
	adc+=SPDAT;//SPDAT contains now the low part of the result. 
	
	P1_4=1; //Deselect the MCP3208 converter.
		
	return adc;
}
 
void main(void)
{
	int j, k;
	#define BUFFSIZE 40
	idata char buff[BUFFSIZE+1];
	int line;
	unsigned char cmd;
	
	/*Disable the MCP3208 ADC*/
	P1_4=1;
	// initialize the SPI port to read the MCH3208 ADC attached to it.
	SPIinit(); //Mode (1,1): see figure 6-2 of MCP3208 datasheet.

	/*Configure the LCD*/
	LCD_4BIT();
	
   	/*Display something in the LCD*/
	LCDprint(" EECE202 Board", 1, 1);
	LCDprint(" C51 test/demo program ", 2, 1);
    puts(BANNER);
    P2_0=1;

    while(1)
    {
    	if(P2_0)
    	{
	        printf("p51> ");
	    	gets(buff);
	        /*Remove extra spaces*/
	        for(j=0; isspace(buff[j]) && (j<BUFFSIZE); j++);
	        for(k=0; (buff[j]!=0)&&(!isspace(buff[j])); j++, k++) buff[k]=buff[j];
	        buff[k]=0;
	        for(j=0; buff[j]!=0; j++) buff[j]=toupper(buff[j]);
	
		    LCDprint(buff, 1, 1); //Just for showing...
			//Find the command in the command table
			for(cmd=0; cmd<ID_invalid; cmd++) if(EQ(buff, cmdtbl[cmd])) break;
		}
		else cmd=ID_v;

		switch(cmd)
		{
			case ID_empty:
				printf("\n");
			break;
			
			case ID_help:
			case ID_qm:
				puts(HELP);
				break;
				
			case ID_quit:
			case ID_exit:
				printf("\nGoodbye!\n");
				putchar(' ');
				//Go back to CMON51 is present!
				_asm
					lcall 0x001b
				_endasm;
				break;
				
			case ID_lcd1:
			case ID_lcd2:
				line=(buff[3]=='1')?1:2;
	        	printf("\nLine %d text: ", line);
	        	gets(buff);
	        	buff[24]=0;
	       		LCDprint(buff, line, 1);
	       		printf("\n");
	       		break;

        	case ID_count:
	            
	            EA=1;
	            ET0=1;
	         	printf("\nIE=0x%02x\n", IE);
	         	Set_ISR_Timer0_Count(0);
	         	while(1)
	            {
	            	timer_count=Get_ISR_Timer0_Count();
	                printf("%d\r", timer_count);
	                if(timer_count>1000) break;
	            }
	         	printf("\n");
	         	break;
         	
         	case ID_clear:
         	case ID_cls:
        		for(j=0; j<45; j++) printf("\n");
        		break;
        		
        	case ID_adc:
	        	for(j=0; j<8; j++)
	        	{
	        		printf("V%d=%5.3fV\n", j, GetADC(j)*5.0/4095.0);
	        	}
	        	break;
	        	
        	case ID_v:
        		printf("\nPress any key to return\n");
	        	while(!RI)
	        	{
		        	for(j=0; j<4; j++)
		    		{	
		    			sprintf(&buff[j*6], "%5.3f ", GetADC(j)*(5.0/4095.0) );
			    		
		    		}
					LCDprint(buff, 1, 0);
					for(j=0; j<4; j++)
		    		{
		    			sprintf(&buff[j*6], "%5.3f ", GetADC(j+4)*(5.0/4095.0) );	
		    		}
					LCDprint(buff, 2, 0);
					WaitXms(200);
				}
				RI=0;
				break;
			
        	case ID_map:
	        	puts(WORLDMAP);
	        	break;
	        	
	        case ID_break:
	        	puts("About to break");
	        	_asm
	        	lcall 0x1b
	        	_endasm;
	        	puts("Back from break");
	        	break;
	        	
			default:
				printf("\nUnknown command.\n");
				break;
		}
    }
}
