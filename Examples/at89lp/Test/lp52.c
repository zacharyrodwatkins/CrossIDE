#include <stdio.h>
#include <at89lp52.h>
//  ~C51~

#define CLK 22118400L
#define BAUD 115200L
#define TIMER_2_RELOAD (0x10000L-(CLK/(16L*BAUD)))

// timer 0 used for systemclock
#define TIMER0_RELOAD_VALUE -CLK/1000 // 0.99938916ms for 22.1184Mhz

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
	PMOD=0; // Configure ports as bidirectional with internal pull-ups.

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


void allone (void)
{
	P0=0xff;
	P1=0xff;
	P2=0xff;
	P3=0xff;
	P4=0xff;
}

unsigned char countzero(void)
{
	unsigned char j;
	
	j=0;
	
	if (P0_0==0) j++;
	if (P0_1==0) j++;
	if (P0_2==0) j++;
	if (P0_3==0) j++;
	if (P0_4==0) j++;
	if (P0_5==0) j++;
	if (P0_6==0) j++;
	//if (P0_7==0) j++;

	if (P1_0==0) j++;
	//if (P1_1==0) j++;
	if (P1_2==0) j++;
	if (P1_3==0) j++;
	if (P1_4==0) j++;
	if (P1_5==0) j++;
	if (P1_6==0) j++;
	if (P1_7==0) j++;

	if (P2_0==0) j++;
	if (P2_1==0) j++;
	if (P2_2==0) j++;
	//if (P2_3==0) j++;
	if (P2_4==0) j++;
	if (P2_5==0) j++;
	if (P2_6==0) j++;
	if (P2_7==0) j++;

	//if (P3_0==0) j++;
	//if (P3_1==0) j++;
	//if (P3_2==0) j++;
	//if (P3_3==0) j++;
	if (P3_4==0) j++;
	if (P3_5==0) j++;
	if (P3_6==0) j++;
	if (P3_7==0) j++;

	//if (P4_0==0) j++;
	//if (P4_1==0) j++;
	//if (P4_2==0) j++;
	//if (P4_3==0) j++;
	//if (P4_4==0) j++;
	//if (P4_5==0) j++;
	//if (P4_6==0) j++;
	//if (P4_7==0) j++;

	return j;
}

#define DO_TEST(PORT1, PORT2) \
	allone();\
	PORT1=0;\
	WaitXms(2);\
	if (PORT2==1) dofail(#PORT2);\
	if (countzero()!=2) dofailb(#PORT2);\
	dopass(#PORT2);\
	allone();\
	PORT2=0;\
	WaitXms(2);\
	if (PORT1==1) dofail(#PORT1);\
	if (countzero()!=2) dofailb(#PORT1);\
	dopass(#PORT1)

void dofail(char * s)
{
	printf("%s FAILED\n", s);
	while(1);
}

void dofailb(char * s)
{
	printf("%s FAILED WITH SHORT\n", s);
	while(1);
}

void dopass(char *s)
{
	printf("%s, ", s);
}

void main(void)
{
	#define TOUT 500

	setbaud_timer2(TIMER_2_RELOAD); // Initialize serial port using timer 2
	printf("\n\nLP51B board autotest\n");

	DO_TEST(P1_0, P2_1);
	//DO_TEST(P1_1, P4_2);
	DO_TEST(P1_2, P0_0);
	DO_TEST(P1_3, P0_1);
	printf("\n");
	DO_TEST(P1_4, P0_2);
	DO_TEST(P1_5, P0_3);
	DO_TEST(P1_6, P0_4);
	DO_TEST(P1_7, P0_5);
	printf("\n");
	//DO_TEST(P4_1, P0_7);
	//DO_TEST(P3_2, P4_0);
	//DO_TEST(P3_3, P4_4);
	DO_TEST(P3_4, P2_7);
	printf("\n");
	DO_TEST(P3_5, P2_6);
	DO_TEST(P3_6, P2_5);
	DO_TEST(P3_7, P2_4);
	//DO_TEST(P4_3, P2_3);
	printf("\n");
	DO_TEST(P0_6, P2_2);
	
	printf("\n\nSuccess!\n");
	
	while(1)
	{
		P2_0=0;
		WaitXms(TOUT);
		P2_0=1;
		WaitXms(TOUT);
	}

}
