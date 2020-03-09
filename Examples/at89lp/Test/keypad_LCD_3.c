#include <stdio.h>
#include <at89lp51rd2.h>

#define LCD_RS P3_7
#define LCD_E  P3_6

#define CLK 22118400L
#define BAUD 115200L
#define TIMER_2_RELOAD (0x10000L-(CLK/(32L*BAUD)))

// timer 0 used for systemclock
#define TIMER0_RELOAD_VALUE -CLK/12/1000 // 0.99938916ms for 22.1184Mhz

//  ~C51~

unsigned int timer_count;

static long data milliSeconds;
volatile unsigned int Timer0_count;
volatile unsigned int cnt;
volatile bit ISR_Timer0_flag;

void ClockIrqHandler (void) interrupt 1 using 1
{
	TL0 = TIMER0_RELOAD_VALUE&0xff;
	TH0 = TIMER0_RELOAD_VALUE>>8;
	cnt++;
	if(cnt>500)
	{
		P4_4=!P4_4;
		cnt=0;
	}
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
	// Configure ports as a bidirectional with internal pull-ups.
	P0M0=0;	P0M1=0;
	P1M0=0;	P1M1=0;
	P2M0=0;	P2M1=0;
	P3M0=0;	P3M1=0;
	AUXR=0B_0001_0001; // 1152 bytes of internal XDATA, P4.4 is a general purpose I/O
	P4M0=0;	P4M1=0;

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
	Delay_LCD(10);
	LCD_E=0;
	Delay_LCD(10);
}

void WriteData (unsigned char x)
{
	LCD_RS=1;
	P2=x|0xf; //Send high nible
	LCD_pulse();
	P2=(x*0x10)|0xf; //Send low nible
	LCD_pulse();
}

void WriteCommand (unsigned char x)
{
	LCD_RS=0;
	P2=x|0xf; //Send high nible
	LCD_pulse();
	P2=(x*0x10)|0xf; //Send low nible
	LCD_pulse();
}

void LCD_4BIT (void)
{
	WaitXms(100);
	// First make sure the LCD is in 8-bit mode
	LCD_RS=0;
	P2=0x30;
	// Three writes ensure 8-bit mode
	LCD_pulse();
	LCD_pulse();
	LCD_pulse();
	
	// Now we can set the LCD to 4-bit mode!
	P2=0x20;
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

char key (void)
{
	char x=0;
	
	
	P2=0b_0000_1111;
	//WaitXms(2);
	if((P2&0x0f)==0x0f) return x;
	WaitXms(50);
	if((P2&0x0f)==0x0f) return x;
	
	P2=0b_0111_1111;
	//WaitXms(2);
	if(P2_3==0) x='D';
	if(P2_2==0) x='C';
	if(P2_1==0) x='B';
	if(P2_0==0) x='A';
	
	P2=0b_1011_1111;
	//WaitXms(2);
	if(P2_3==0) x='#';
	if(P2_2==0) x='9';
	if(P2_1==0) x='6';
	if(P2_0==0) x='3';

	P2=0b_1101_1111;
	//WaitXms(2);
	if(P2_3==0) x='0';
	if(P2_2==0) x='8';
	if(P2_1==0) x='5';
	if(P2_0==0) x='2';

	P2=0b_1110_1111;
	//WaitXms(2);
	if(P2_3==0) x='*';
	if(P2_2==0) x='7';
	if(P2_1==0) x='4';
	if(P2_0==0) x='1';

	P2=0b_0000_1111;
	//WaitXms(2);
	while((P2&0x0f)!=0x0f);
	return x;
}


void main(void)
{
	char x;

	/*Configure the LCD*/
	LCD_4BIT();
	
	setbaud_timer2(TIMER_2_RELOAD); // Initialize serial port using timer 2
	printf("Hello, World!\n");

   	/*Display something in the LCD*/
	LCDprint("Keypad/LCD test", 1, 1);
	LCDprint("", 2, 1);
	while(1)
	{
		x=key();
		if(x!=0) WriteData(x);
		if(P4_5==0) LCDprint("", 2, 1);
	}
}
