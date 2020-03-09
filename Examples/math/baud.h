//For an oscillator frequency of 22.1184MHz...

//For timer 1, these are the correct values for TH1:
//For k=1:
#define TIMER1_K1_300      0x40 
#define TIMER1_K1_600      0xa0 
#define TIMER1_K1_1200     0xd0 
#define TIMER1_K1_2400     0xe8 
#define TIMER1_K1_4800     0xf4 
#define TIMER1_K1_9600     0xfa 
#define TIMER1_K1_19200    0xfd 
#define TIMER1_K1_57600    0xff 
//For k=2:
#define TIMER1_K2_600      0x40 
#define TIMER1_K2_1200     0xa0 
#define TIMER1_K2_2400     0xd0 
#define TIMER1_K2_4800     0xe8 
#define TIMER1_K2_9600     0xf4 
#define TIMER1_K2_19200    0xfa 
#define TIMER1_K2_38400    0xfd 
#define TIMER1_K2_57600    0xfe 
#define TIMER1_K2_115200   0xff 

//If timer 2 is used to generate the baud rate,
//these are the correct values for [RCAP2H, TCAP2L]:
#define TIMER2_150     0xee00 
#define TIMER2_300     0xf700 
#define TIMER2_600     0xfb80 
#define TIMER2_1200    0xfdc0 
#define TIMER2_2400    0xfee0 
#define TIMER2_4800    0xff70 
#define TIMER2_9600    0xffb8 
#define TIMER2_19200   0xffdc 
#define TIMER2_38400   0xffee 
#define TIMER2_57600   0xfff4 
#define TIMER2_115200  0xfffa 
