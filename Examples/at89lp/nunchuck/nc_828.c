#include <stdio.h>
#include <stdlib.h>
#include <at89lp828.h>

// ~C51~  

#define SDA P2_7
#define SCL P2_6
#define I2C_DELAY 0x10

#define CLK 3686400L
#define BAUD 115200L
#define TIMER_2_RELOAD (0x10000L-(CLK/(16L*BAUD)))
// timer 0 used for system clock
#define TIMER0_RELOAD_VALUE (65536L-(CLK/(1000L)))

volatile unsigned int ms;
volatile bit ms_flag;
volatile unsigned int tick;

void Init_Timer0(void)
{
	TR0=0; // stop timer 0
	TMOD =(TMOD&0xf0)|0x01; // T0=16bit timer
	TL0 = TIMER0_RELOAD_VALUE&0xff;
	TH0 = TIMER0_RELOAD_VALUE>>8;
	TR0=1; // start timer 0 (bit 4 in TCON)
	ET0=1; // enable timer 0 interrupt
	EA=1; // enable global interrupt
}

void ClockIrqHandler (void) interrupt 1 using 1
{
	TR0=0;
	TF0=0;
	TL0 = TIMER0_RELOAD_VALUE&0xff;
	TH0 = TIMER0_RELOAD_VALUE>>8;
	TR0=1;
	ms++;
	ms_flag=1;
	tick++;
}

unsigned int Read_ms(void)
{
	unsigned int j;
	do {
		ms_flag=0;
		j=ms;
	} while (ms_flag==1);
	return j;
}

void Write_ms(unsigned int j)
{
	do {
		ms_flag=0;
		ms=j;
	} while (ms_flag==1);
}

void Delay (unsigned int n)
{
	Write_ms(0);
	while(Read_ms()<n);
}

void I2C_delay(void)
{
	unsigned char i;
	for(i=0; i<I2C_DELAY; i++);
}

void I2C_clock(void)
{
	I2C_delay();
	SCL=1;
	I2C_delay();    
	SCL=0;
}

void I2C_start(void)
{
	if(SCL==1) SCL=0;
	SDA=1;
	SCL=1;
	I2C_delay(); 
	SDA=0;
	I2C_delay(); 
	SCL=0;
}

void I2C_stop(void)
{
	if(SCL==1) SCL=0;
	SDA=0;
	I2C_delay();
	SCL=1;
	I2C_delay();
	SDA=1;
}

bit I2C_write(unsigned char dat)
{
	bit saved_SDA;		
	unsigned char i;	

	for(i=0; i<8; i++)
	{
		SDA=(dat & 0x80)?1:0;
		I2C_clock();
		dat<<=1;  
	}

	SDA=1;
	I2C_delay();	
	SCL=1;
	I2C_delay();	
	saved_SDA=SDA; // Check acknowledge
	SCL=0;
	I2C_delay();

	return saved_SDA; // A valid write returns zero	 	
}

unsigned char I2C_read(void)
{
	unsigned char i, dat;

	dat=0x00;	

	for(i=0; i<8; i++)
	{
		I2C_delay();
		SCL=1;
		I2C_delay(); 
		dat<<=1;
		if (SDA) dat|=0x01;		
		SCL=0;
	}

	return dat;
}

void I2C_ack()
{
	SDA=0;
	I2C_delay();    
	I2C_clock();
	SDA=1;
}

void I2C_noack()
{
	SDA=1;
	I2C_delay();
	I2C_clock();
	SCL=1;
}

void nunchuck_init(void)
{
	do {
		I2C_start();
	} while(I2C_write(0xA4) != 0);
	I2C_write(0x40);	
	I2C_write(0x00);	
	I2C_stop();
}

void nunchuck_getdata(unsigned char * s)
{
	unsigned char i;

	// Start measurement
	do {
		I2C_start();
	}
	while(I2C_write(0xA4) != 0); 

	I2C_write(0x00);	
	I2C_stop();
	Delay(3); 	// 3 ms required to complete acquisition

	// Request values
	do {
  		I2C_start();
  	} while(I2C_write(0xA5) != 0);

	// Receive values
	for(i=0; i<6; i++)
	{
		s[i]=(I2C_read()^0x17)+0x17;  
		if(i==5)
			I2C_noack();
		else
			I2C_ack(); 
	}
	
	I2C_stop();
}

void main (void)
{
	unsigned char rbuf[6];
 	int joy_x, joy_y, acc_x, acc_y, acc_z;
 	char but1, but2;

	CLKREG=0x00; // TPS=0000B
	setbaud_timer2(TIMER_2_RELOAD); // Initialize serial port using timer 2
	Init_Timer0();
	
	P2M0|=0xc0;
	P2M1|=0xc0;
	
	printf("\n\nWII Nunchuck reader\n");

	Delay(200);
	nunchuck_init();
	Delay(100);
	
	while(1)
	{
		nunchuck_getdata(rbuf);

		joy_x=rbuf[0]-128;
		joy_y=rbuf[1]-128;
		acc_x=rbuf[2]*4; 
		acc_y=rbuf[3]*4;
		acc_z=rbuf[4]*4;

		but1=(rbuf[5] & 0x01)?'1':'0';
		but2=(rbuf[5] & 0x02)?'1':'0';
		if (rbuf[5] & 0x04) acc_x+=2;
		if (rbuf[5] & 0x08) acc_x+=1;
		if (rbuf[5] & 0x10) acc_y+=2;
		if (rbuf[5] & 0x20) acc_y+=1;
		if (rbuf[5] & 0x40) acc_z+=2;
		if (rbuf[5] & 0x80) acc_z+=1;

		printf("B1:%c B2:%c JX:%4d JY:%4d AX:%3d AY:%3d AZ:%3d\r",
			   but1, but2, joy_x, joy_y, acc_x, acc_y, acc_z);
	}
}
