#include <stdio.h>
#include <at89lp51rd2.h>

#define CLK 22118400L
#define BAUD 115200L
#define BRG_VAL (0x100-(CLK/(32L*BAUD)))

#define BASE_ROW 2
#define BASE_COL 32

// timer 0 used for systemclock
#define TIMER0_RELOAD_VALUE -CLK/12/1000 // 0.99938916ms for 22.1184Mhz

/* ANSI colors */
#define	COLOR_BLACK		0
#define	COLOR_RED		1
#define	COLOR_GREEN		2
#define	COLOR_YELLOW	3
#define	COLOR_BLUE		4
#define	COLOR_MAGENTA	5
#define	COLOR_CYAN		6
#define	COLOR_WHITE		7

/* Some ANSI escape sequences */
#define CURSOR_ON "\x1b[?25h"
#define CURSOR_OFF "\x1b[?25l"
#define CLEAR_SCREEN "\x1b[2J"
#define GOTO_YX "\x1B[%d;%dH"
#define CLR_TO_END_LINE "\x1B[K"
/* Black foreground, white background */
#define BKF_WTB "\x1B[0;30;47m"
#define FORE_BACK "\x1B[0;3%d;4%dm"
#define RESET_ATTRIBUTES "\x1B[0m"
#define BRIGHT "\x1B[1m"
#define DIM "\x1B[2m"
#define UNDERSCORE "\x1B[4m"
#define BLINK "\x1B[5m"
#define REVERSE "\x1B[7m"
#define HIDDEN "\x1B[8m"

unsigned int timer_count;

static long data milliSeconds;
volatile unsigned int Timer0_count;
volatile unsigned int cnt;
volatile bit ISR_Timer0_flag;
volatile unsigned char nerrors;

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

    // Initialize the serial port and baud rate generator
    PCON|=0x80;
	SCON = 0x52;
    BDRCON=0;
    BRL=BRG_VAL;
    BDRCON=BRR|TBCK|RBCK|SPD;
    
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
	if (P0_7==0) j++;

	if (P1_0==0) j++;
	if (P1_1==0) j++;
	if (P1_2==0) j++;
	if (P1_3==0) j++;
	if (P1_4==0) j++;
	if (P1_5==0) j++;
	if (P1_6==0) j++;
	if (P1_7==0) j++;

	if (P2_0==0) j++;
	if (P2_1==0) j++;
	if (P2_2==0) j++;
	if (P2_3==0) j++;
	if (P2_4==0) j++;
	if (P2_5==0) j++;
	if (P2_6==0) j++;
	if (P2_7==0) j++;

	//if (P3_0==0) j++;
	//if (P3_1==0) j++;
	if (P3_2==0) j++;
	if (P3_3==0) j++;
	if (P3_4==0) j++;
	if (P3_5==0) j++;
	if (P3_6==0) j++;
	if (P3_7==0) j++;

	if (P4_0==0) j++;
	if (P4_1==0) j++;
	if (P4_2==0) j++;
	if (P4_3==0) j++;
	if (P4_4==0) j++;
	//if (P4_5==0) j++;
	//if (P4_6==0) j++;
	//if (P4_7==0) j++;

	return j;
}

#define DO_TEST(PORT1, PORT2, y1, y2) \
	allone();\
	PORT1=0;\
	if (PORT2==1) dofail(y1);\
	else if (countzero()!=2) dofail(y1);\
	else dopass(y1);\
	allone();\
	PORT2=0;\
	if (PORT1==1) dofail(y2);\
	else if (countzero()!=2) dofail(y2);\
	else dopass(y2)

void dofail(char y)
{
	nerrors++;
	printf( FORE_BACK BLINK, COLOR_RED, COLOR_WHITE );
	printf(GOTO_YX "FAIL", y&0x7f, (y&0x80)?BASE_COL-4:BASE_COL+16);
}

void dopass(char y)
{
	printf( FORE_BACK , COLOR_GREEN, COLOR_WHITE );
	printf(GOTO_YX "PASS", y&0x7f, (y&0x80)?BASE_COL-4:BASE_COL+16);
}

/*
° ± ² ³ ´ µ ¶ · ¸ ¹ º » ¼ ½ ¾ ¿

À Á Â Ã Ä Å Æ Ç È É Ê Ë Ì Í Î Ï

Ð Ñ Ò Ó Ô Õ Ö × Ø Ù Ú Û Ü Ý Þ ß

*/

void main (void)
{
	printf( FORE_BACK , COLOR_BLACK, COLOR_WHITE );
	printf( CLEAR_SCREEN );

	printf(GOTO_YX " LP51B PIN TEST ",  BASE_ROW-1 , BASE_COL);
	printf(GOTO_YX " ÚÄÄÄÄÄÄÄÄÄÄÄÄ¿ ",  BASE_ROW+0 , BASE_COL);
	printf(GOTO_YX "Ä´P1.0     +5VÃÄ",  BASE_ROW+1 , BASE_COL);
	printf(GOTO_YX "Ä´P1.1    P4.2ÃÄ",  BASE_ROW+2 , BASE_COL);
	printf(GOTO_YX "Ä´P1.2    P0.0ÃÄ",  BASE_ROW+3 , BASE_COL);
	printf(GOTO_YX "Ä´P1.3    P0.1ÃÄ",  BASE_ROW+4 , BASE_COL);
	printf(GOTO_YX "Ä´P1.4    P0.2ÃÄ",  BASE_ROW+5 , BASE_COL);
	printf(GOTO_YX "Ä´P1.5    P0.3ÃÄ",  BASE_ROW+6 , BASE_COL);
	printf(GOTO_YX "Ä´P1.6    P0.4ÃÄ",  BASE_ROW+7 , BASE_COL);
	printf(GOTO_YX "Ä´P1.7    P0.5ÃÄ",  BASE_ROW+8 , BASE_COL);
	printf(GOTO_YX "Ä´RST     P0.6ÃÄ",  BASE_ROW+9 , BASE_COL);
	printf(GOTO_YX "Ä´P4.1    P0.7ÃÄ",  BASE_ROW+10, BASE_COL);
	printf(GOTO_YX "Ä´P3.2    P4.0ÃÄ",  BASE_ROW+11, BASE_COL);
	printf(GOTO_YX "Ä´P3.3    P4.4ÃÄ",  BASE_ROW+12, BASE_COL);
	printf(GOTO_YX "Ä´P3.4    P2.7ÃÄ",  BASE_ROW+13, BASE_COL);
	printf(GOTO_YX "Ä´P3.5    P2.6ÃÄ",  BASE_ROW+14, BASE_COL);
	printf(GOTO_YX "Ä´P3.6    P2.5ÃÄ",  BASE_ROW+15, BASE_COL);
	printf(GOTO_YX "Ä´P3.7    P2.4ÃÄ",  BASE_ROW+16, BASE_COL);
	printf(GOTO_YX "Ä´P4.3    P2.3ÃÄ",  BASE_ROW+17, BASE_COL);
	printf(GOTO_YX "Ä´VCC     P2.2ÃÄ",  BASE_ROW+18, BASE_COL);
	printf(GOTO_YX "Ä´GND     P2.1ÃÄ",  BASE_ROW+19, BASE_COL);
	printf(GOTO_YX "Ä´GND     P2.0ÃÄ",  BASE_ROW+20, BASE_COL);
	printf(GOTO_YX " ÀÄÄÄÄÄÄÄÄÄÄÄÄÙ ",  BASE_ROW+21, BASE_COL);
	
	nerrors=0;
	DO_TEST(P1_0, P2_1, 0x80 | BASE_ROW+1,  BASE_ROW+19);
	DO_TEST(P1_1, P4_2, 0x80 | BASE_ROW+2,  BASE_ROW+2);
	DO_TEST(P1_2, P0_0, 0x80 | BASE_ROW+3,  BASE_ROW+3);
	DO_TEST(P1_3, P0_1, 0x80 | BASE_ROW+4,  BASE_ROW+4);
	DO_TEST(P1_4, P0_2, 0x80 | BASE_ROW+5,  BASE_ROW+5);
	DO_TEST(P1_5, P0_3, 0x80 | BASE_ROW+6,  BASE_ROW+6);
	DO_TEST(P1_6, P0_4, 0x80 | BASE_ROW+7,  BASE_ROW+7);
	DO_TEST(P1_7, P0_5, 0x80 | BASE_ROW+8,  BASE_ROW+8);
	DO_TEST(P4_1, P0_7, 0x80 | BASE_ROW+10, BASE_ROW+10);
	DO_TEST(P3_2, P4_0, 0x80 | BASE_ROW+11, BASE_ROW+11);
	DO_TEST(P3_3, P4_4, 0x80 | BASE_ROW+12, BASE_ROW+12);
	DO_TEST(P3_4, P2_7, 0x80 | BASE_ROW+13, BASE_ROW+13);
	DO_TEST(P3_5, P2_6, 0x80 | BASE_ROW+14, BASE_ROW+14);
	DO_TEST(P3_6, P2_5, 0x80 | BASE_ROW+15, BASE_ROW+15);
	DO_TEST(P3_7, P2_4, 0x80 | BASE_ROW+16, BASE_ROW+16);
	DO_TEST(P4_3, P2_3, 0x80 | BASE_ROW+17, BASE_ROW+17);
	DO_TEST(P0_6, P2_2, BASE_ROW+9, BASE_ROW+18);

	if (nerrors==0)
		printf( FORE_BACK BLINK, COLOR_GREEN, COLOR_WHITE );
	else
		printf( FORE_BACK, COLOR_BLACK, COLOR_WHITE );
	printf(GOTO_YX "LED", BASE_ROW+20, BASE_COL+16);
	printf( FORE_BACK , COLOR_BLACK, COLOR_WHITE );

	#define TOUT 500
	
	if (nerrors==0) while(1)
	{
		P2_0=0;
		WaitXms(TOUT);
		P2_0=1;
		WaitXms(TOUT);
	}

}
