#include <stdio.h>
#include <at89lp51rd2.h>

#define LCD_RS P3_7
#define LCD_E  P3_6

#define CLK 22118400L
#define BAUD 115200L
#define TIMER_2_RELOAD (0x10000L-(CLK/(32L*BAUD)))

// timer 0 used for systemclock
#define TIMER0_RELOAD_VALUE -CLK/12/1000 // 0.99938916ms for 22.1184Mhz

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


void main(void)
{
	#define TOUT 500

	setbaud_timer2(TIMER_2_RELOAD); // Initialize serial port using timer 2
	printf("Hello, World!\n");

	P0=0xff;
	P1=0xff;
	P2=0xff;
	P3=0xff;
	
	while(1)
	{
		P4_2=0; WaitXms(TOUT); P4_2=1;

		P0_0=0; WaitXms(TOUT); P0_0=1;
		P0_1=0; WaitXms(TOUT); P0_1=1;
		P0_2=0; WaitXms(TOUT); P0_2=1;
		P0_3=0; WaitXms(TOUT); P0_3=1;
		P0_4=0; WaitXms(TOUT); P0_4=1;
		P0_5=0; WaitXms(TOUT); P0_5=1;
		P0_6=0; WaitXms(TOUT); P0_6=1;
		P0_7=0; WaitXms(TOUT); P0_7=1;

		P4_0=0; WaitXms(TOUT); P4_0=1;
		P4_4=0; WaitXms(TOUT); P4_4=1;
		
		P2_7=0; WaitXms(TOUT); P2_7=1;
		P2_6=0; WaitXms(TOUT); P2_6=1;
		P2_5=0; WaitXms(TOUT); P2_5=1;
		P2_4=0; WaitXms(TOUT); P2_4=1;
		P2_3=0; WaitXms(TOUT); P2_3=1;
		P2_2=0; WaitXms(TOUT); P2_2=1;
		P2_1=0; WaitXms(TOUT); P2_1=1;
		P2_0=0; WaitXms(TOUT); P2_0=1;

		P4_3=0; WaitXms(TOUT); P4_3=1;
		
		P3_7=0; WaitXms(TOUT); P3_7=1;
		P3_6=0; WaitXms(TOUT); P3_6=1;
		P3_5=0; WaitXms(TOUT); P3_5=1;
		P3_4=0; WaitXms(TOUT); P3_4=1;
		P3_3=0; WaitXms(TOUT); P3_3=1;
		P3_2=0; WaitXms(TOUT); P3_2=1;
		//P3_1=0; WaitXms(TOUT); P3_1=1;
		//P3_0=0; WaitXms(TOUT); P3_0=1;

		P4_1=0; WaitXms(TOUT); P4_1=1;
		
		P1_7=0; WaitXms(TOUT); P1_7=1;
		P1_6=0; WaitXms(TOUT); P1_6=1;
		P1_5=0; WaitXms(TOUT); P1_5=1;
		P1_4=0; WaitXms(TOUT); P1_4=1;
		P1_3=0; WaitXms(TOUT); P1_3=1;
		P1_2=0; WaitXms(TOUT); P1_2=1;
		P1_1=0; WaitXms(TOUT); P1_1=1;
		P1_0=0; WaitXms(TOUT); P1_0=1;
	}

}
