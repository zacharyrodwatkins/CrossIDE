/*  mathtest.c: Test floating point functions

    Copyright (C) 2001  Jesus Calvino-Fraga, jesusc@ieee.org 

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA */

/* Version 1.0 - Initial release */

// ~C51~  --model-large

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <DE2_8052.h>

//The DE1-8052 softcore clock is 33.33MHz
#define CLK 33333333L
#define BAUD 115200L
#define TIMER_2_RELOAD (0x10000L-(CLK/(32L*BAUD)))
#define LOW(X)  (X%0x100)
#define HIGH(X) (X/0x100)

void putchar (char c)
{
	if (c=='\n')
	{
		while (!TI);
		TI=0;
		SBUF='\r';
	}
	while (!TI);
	TI=0;
	SBUF=c;
}

char getchar (void)
{
	char c;
	
	while (!RI);
	RI=0;
	c=SBUF;
	return c;
}
void exit (int j)
{
	while(1);
	j;
}

// timer 0 used for systemclock
#define TIMER0_RELOAD_VALUE -CLK/22/1000 // 0.999348ms for 11.059Mhz

static long data milliSeconds;

void ClockIrqHandler (void) interrupt 1
{
  TL0 = TIMER0_RELOAD_VALUE&0xff;
  TH0 = TIMER0_RELOAD_VALUE>>8;
  milliSeconds++;
}

// we can't just use milliSeconds
unsigned long ClockTicks(void) {
  unsigned long ms;
  ET0=0;
  ms=milliSeconds;
  ET0=1;
  return ms;
}

unsigned char _c51_external_startup()
{
	// initialize timer0 for system clock
	TR0=0; // stop timer 0
	TMOD =(TMOD&0xf0)|0x01; // T0=16bit timer
	// timeout is xtal/12
	TL0 = -TIMER0_RELOAD_VALUE&0xff;
	TH0 = -TIMER0_RELOAD_VALUE>>8;
	milliSeconds=0; // reset system time
	TR0=1; // start timer 0
	ET0=1; // enable timer 0 interrupt
  
	// initialize timer2 for baudrate
	RCAP2H=HIGH(TIMER_2_RELOAD);
	RCAP2L=LOW(TIMER_2_RELOAD);
	T2CON=0x34; // #00110100B
	SCON=0x52; // Serial port in mode 1, ren, txrdy, rxempty

	//EA=1; // enable global interrupt
	
	return 0;
}

int errno;  //Where should it be???

#define lt_testW printf("a=%5.2f; b=%5.2f ", a, b); if(a<b) puts("a<b WRONG");   else puts("a>=b correct")
#define lt_testR printf("a=%5.2f; b=%5.2f ", a, b); if(a<b) puts("a<b correct"); else puts("a>=b WRONG")

void main (void)
{
	static float x, y, z, ysin, ycos;
	static int i=2, n;
	static long etime, ltime;
	static int expo;
	static float mant;
	static float a, b;
	static long a1, b1;
	static union float_long fl;
 
	LEDRA=0;
	LEDRB=0;
	LEDRC=0;
	LEDG=0;

	puts("\nTesting mathf functions...");

	puts("\n*** Testing frexp ***");
	x=1000.0;
	mant=frexpf(x, &expo);
	printf("%11.8f=%11.8f*(2^%d)\n", x, mant, expo);

	puts("\n*** Testing ldexp ***");
	y=ldexpf(mant, expo);
	printf("%11.8f*(2^%d)=%11.8f\n", mant, expo, y);

	puts("\n*** Testing sqrt(x) ****");
	for(i=0; i<10; i++)
	{
		x=i;
		y=sqrtf(x);
		printf("%5.2f %11.8f\n", x, y);
	}
	
	puts("\n*** Testing log(x) and log10(x) ***");
	for(i=1; i<32; i++)
	{
		x=i*4.0;
		printf("%6.2f %11.8f %11.8f\n", x, logf(x), log10f(x));
	}

	puts("\n*** Testing pow(x) ***");
	for(i=0; i<25; i++)
	{
		x=i*0.1;
		y=powf(x, 2.0);
		printf("(%5.2f)^2= %11.8f\n", x, y);
	}

	puts("\n*** Testing sin(x) and cos(x) ***");

	for(i=0; i<35; i++)
	{
		x=i*0.2;

		ysin=sinf(x);
		ycos=cosf(x);

		printf("%5.2f %11.8f %11.8f\n", x, ysin, ycos);
	}

	puts("\n*** Testing tan(x) and cot(x) ***");
	for(i=0; i<35; i++)
	{
		x=i*0.2+0.1; // Avoid cot(0)=infinte.  It doesn't display well in the screen.
		printf("%5.2f %12.8f %12.8f\n", x, tanf(x), cotf(x));
	}

	puts("\n*** Testing asin(x) and acos(x) ***");
	for(i=-10; i<11; i++)
	{
		x=i*0.1;
		printf("%5.2f %12.8f %12.8f\n", x, asinf(x), acosf(x));
	}

	puts("\n*** Testing atan(x) ***");
	for(i=-10; i<11; i++)
	{
		x=i*0.5;
		printf("%5.2f %12.8f\n", x, atanf(x));
	}

	puts("\n*** Testing atan2(x) ***");
	printf("atan( 1.0,  1.0)=%12.8f\n", atan2f( 1.0,  1.0));
	printf("atan(-1.0,  1.0)=%12.8f\n", atan2f(-1.0,  1.0));
	printf("atan(-1.0, -1.0)=%12.8f\n", atan2f(-1.0, -1.0));
	printf("atan( 1.0, -1.0)=%12.8f\n", atan2f( 1.0, -1.0));

	puts("\n*** Testing sinh(x) and cosh(x) ***");
	for(i=0; i<16; i++)
	{
		x=i*0.5;
		printf("%5.2f %12.8f %12.8f\n", x, sinhf(x), coshf(x));
	}
			
	puts("\n*** Testing tanh(x) ***");
	for(i=0; i<22; i++)
	{
		x=i*0.5;
		printf("%5.2f %12.8f\n", x, tanhf(x));
	}

	puts("\n*** Testing exp(x) ***");
	for(i=0; i<20; i++)
	{
		x=i*(-1.0/10.0);
		printf("%5.2f %12.8f\n", x, expf(x));
	}

	puts("\n*** Testing floor(x), ceil(x), and modf(x) ***");
	puts("x     int   frc   floor  ceil");
	for(i=-10; i<11; i++)
	{
		x=i*0.5;
		z=modff(x, &y);
		printf("%5.2f %5.2f %5.2f %5.2f %5.2f\n",
		        x, y, z, floorf(x), ceilf(x));
	}
	puts("\nTest completed.");
}
