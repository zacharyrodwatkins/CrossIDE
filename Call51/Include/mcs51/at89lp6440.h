/*-------------------------------------------------------------------------
   Register Declarations for Atmel's AT89LP6440/AT89LP3240
   
   Written By -  Jesus Calvino-Fraga / jesusc at ece.ubc.ca (April 2012)
   
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option); any later version.
   
   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.
   
   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
-------------------------------------------------------------------------*/

#ifndef REG_AT89LP6440_H
#define REG_AT89LP6440_H

#include <compiler.h>

// PORT Registers
SFR(P0, 0x80);
SFR(P0M0, 0xBA);
SFR(P0M1, 0xBB);
	SBIT(P0_7, 0x80, 7);
	SBIT(P0_6, 0x80, 6);
	SBIT(P0_5, 0x80, 5);
	SBIT(P0_4, 0x80, 4);
	SBIT(P0_3, 0x80, 3);
	SBIT(P0_2, 0x80, 2);
	SBIT(P0_1, 0x80, 1);
	SBIT(P0_0, 0x80, 0);

SFR(P1, 0x90);
SFR(P1M0, 0xC2);
SFR(P1M1, 0xC3);
	SBIT(P1_7, 0x90, 7);
	SBIT(P1_6, 0x90, 6);
	SBIT(P1_5, 0x90, 5);
	SBIT(P1_4, 0x90, 4);
	SBIT(P1_3, 0x90, 3);
	SBIT(P1_2, 0x90, 2);
	SBIT(P1_1, 0x90, 1);
	SBIT(P1_0, 0x90, 0);
	SBIT(SCK,  0x90, 7);
	SBIT(MISO, 0x90, 6);
	SBIT(MOSI, 0x90, 5);
	SBIT(SSB,  0x90, 4);
	SBIT(SCL,  0x90, 3);
	SBIT(SDA,  0x90, 2);
	SBIT(T2EX, 0x90, 1);
	SBIT(T2,   0x90, 0);

SFR(P2, 0xA0); 
SFR(P2M0, 0xC4);
SFR(P2M1, 0xC5);
	SBIT(P2_7, 0xA0, 7);
	SBIT(P2_6, 0xA0, 6);
	SBIT(P2_5, 0xA0, 5);
	SBIT(P2_4, 0xA0, 4);
	SBIT(P2_3, 0xA0, 3);
	SBIT(P2_2, 0xA0, 2);
	SBIT(P2_1, 0xA0, 1);
	SBIT(P2_0, 0xA0, 0);
	SBIT(CCD,  0xA0, 3);
	SBIT(CCC,  0xA0, 2);
	SBIT(CCB,  0xA0, 1);
	SBIT(CCA,  0xA0, 0);

SFR(P3, 0xB0);
	SFR(P3M0, 0xC5);
	SFR(P3M1, 0xC6);
	SBIT(P3_7, 0xB0, 7);
	SBIT(P3_6, 0xB0, 6);
	SBIT(P3_5, 0xB0, 5);
	SBIT(P3_4, 0xB0, 4);
	SBIT(P3_3, 0xB0, 3);
	SBIT(P3_2, 0xB0, 2);
	SBIT(P3_1, 0xB0, 1);
	SBIT(P3_0, 0xB0, 0);
	SBIT(RD,   0xB0, 7);
	SBIT(WR,   0xB0, 6);
	SBIT(T1,   0xB0, 5);
	SBIT(T0,   0xB0, 4);
	SBIT(INT1, 0xB0, 3);
	SBIT(INT0, 0xB0, 2);
	SBIT(TXD,  0xB0, 1);
	SBIT(RXD,  0xB0, 0);

SFR(P4, 0xC0);
	SFR(P4M0, 0xBE);
	SFR(P4M1, 0xBF);
	SBIT(P4_7,  0xC0, 7);
	SBIT(P4_6,  0xC0, 6);
	SBIT(P4_5,  0xC0, 5);
	SBIT(P4_4,  0xC0, 4);
	SBIT(P4_3,  0xC0, 3);
	SBIT(P4_2,  0xC0, 2);
	SBIT(P4_1,  0xC0, 1);
	SBIT(P4_0,  0xC0, 0);
	SBIT(ALE,   0xC0, 4);
	SBIT(XTAL2, 0xC0, 1);
	SBIT(XTAL1, 0xC0, 0);

// Program Status register

SFR(PSW, 0xD0);       
	SBIT(CY,  0xD0, 7);
	SBIT(AC,  0xD0, 6);
	SBIT(F0,  0xD0, 5);
	SBIT(RS1, 0xD0, 4);
	SBIT(RS0, 0xD0, 3);
	SBIT(OV,  0xD0, 2);
	SBIT(UD,  0xD0, 1);
	SBIT(P,   0xD0, 0);

// CPU registers

SFR(ACC,   0xE0);       
	SBIT(ACC_7, 0xE0, 7);
	SBIT(ACC_6, 0xE0, 6);
	SBIT(ACC_5, 0xE0, 5);
	SBIT(ACC_4, 0xE0, 4);
	SBIT(ACC_3, 0xE0, 3);
	SBIT(ACC_2, 0xE0, 2);
	SBIT(ACC_1, 0xE0, 1);
	SBIT(ACC_0, 0xE0, 0);
SFR(AX,    0xE1);       
SFR(B,     0xF0); 
	SBIT(B_7, 0xF0, 7);
	SBIT(B_6, 0xF0, 6);
	SBIT(B_5, 0xF0, 5);
	SBIT(B_4, 0xF0, 4);
	SBIT(B_3, 0xF0, 3);
	SBIT(B_2, 0xF0, 2);
	SBIT(B_1, 0xF0, 1);
	SBIT(B_0, 0xF0, 0);
SFR(BX,    0xF7); 
SFR(SP,    0x81);
SFR(SPX,   0x9E);
SFR(DPL,   0x82);       
SFR(DPH,   0x83);       
SFR(DP0L,  0x82);       
SFR(DP0H,  0x83);       
SFR(DP1L,  0x84);       
SFR(DP1H,  0x85);       
SFR(AUXR,  0x8E);
SFR(AUXR1, 0xA2);
SFR(DPCF,  0xA2);
   #define DPU1  0x80
   #define DPU0  0x40
   #define DPD1  0x20
   #define DPD0  0x10
   #define SIGEN 0x08
   #define DPS   0x01
SFR(DSPR,  0xE2);
SFR(FIRD,  0xE3);
SFR(MACL,  0xE4);
SFR(MACH,  0xE5);
SFR(PAGE,  0x86);

// Timer registers
SFR(TCON, 0x88);
	SBIT(TF1, 0x88, 7); // Timer 1 Overflow Flag
	SBIT(TR1, 0x88, 6); // Timer 1 On/Off Control
	SBIT(TF0, 0x88, 5); // Timer 0 Overflow Flag
	SBIT(TR0, 0x88, 4); // Timer 0 On/Off Control
	SBIT(IE1, 0x88, 3); // Ext. Interrupt 1 Edge Flag
	SBIT(IT1, 0x88, 2); // Ext. Interrupt 1 Type
	SBIT(IE0, 0x88, 1); // Ext. Interrupt 0 Edge Flag
	SBIT(IT0, 0x88, 0); // Ext. Interrupt 0 Type

SFR(TMOD, 0x89);      

SFR (T2CON, 0xC8);
	SBIT(TF2,    0xC8, 7);
	SBIT(EXF2,   0xC8, 6);
	SBIT(RCLK,   0xC8, 5);
	SBIT(TCLK,   0xC8, 4);
	SBIT(EXEN2,  0xC8, 3);
	SBIT(TR2,    0xC8, 2);
	SBIT(C_T2,   0xC8, 1);
	SBIT(CP_RL2, 0xC8, 0);

SFR(T2MOD,  0xC9);     
SFR(TL0,    0x8A);       
SFR(TL1,    0x8B);       
SFR(TL2,    0xCC);       
SFR(TH0,    0x8C);       
SFR(TH1,    0x8D);       
SFR(TH2,    0xCD);       
SFR(TCONB,  0x91);     
SFR(RL0,    0x92);       
SFR(RL1,    0x93);       
SFR(RH0,    0x94);       
SFR(RH1,    0x95);       
SFR(RCAP2L, 0xCA);    
SFR(RCAP2H, 0xCB);    
SFR(WDTRST, 0xA6);    
SFR(WDTCON, 0xA7);    

// UART registers
SFR(SCON, 0x98);      
	SBIT(SM0, 0x98, 7);
	SBIT(FE, 0x98, 7);
	SBIT(SM1, 0x98, 6);
	SBIT(SM2, 0x98, 5);
	SBIT(REN, 0x98, 4);
	SBIT(TB8, 0x98, 3);
	SBIT(RB8, 0x98, 2);
	SBIT(TI, 0x98, 1);
	SBIT(RI, 0x98, 0);

SFR(SBUF, 0x99);      
SFR(SADEN, 0xB9);     
SFR(SADDR, 0xA9);     

// Interrupt registers
SFR(IE, 0xA8);      
	SBIT(EA, 0xA8, 7);
	SBIT(EC, 0xA8, 6);
	SBIT(ET2, 0xA8, 5);
	SBIT(ES, 0xA8, 4);
	SBIT(ET1, 0xA8, 3);
	SBIT(EX1, 0xA8, 2);
	SBIT(ET0, 0xA8, 1);
	SBIT(EX0, 0xA8, 0);

SFR(IP, 0xB8);      
	SBIT(PC, 0xB8, 6);
	SBIT(PT2, 0xB8, 5);
	SBIT(PS, 0xB8, 4);
	SBIT(PT1, 0xB8, 3);
	SBIT(PX1, 0xB8, 2);
	SBIT(PT0, 0xB8, 1);
	SBIT(PX0, 0xB8, 0);

SFR(IPH,  0xB7);      
SFR(IE2,  0xB4);      
SFR(IP2,  0xB5);      
SFR(IPH2, 0xB6);      

// CCA registers
SFR(T2CCA, 0xD1);      
SFR(T2CCL, 0xD2);      
SFR(T2CCH, 0xD3);
SFR(T2CCC, 0xD4);
SFR(T2CCF, 0xD5);

// TWI registers
SFR(TWCR, 0xAA);
SFR(TWSR, 0xAB);
SFR(TWAR, 0xAC);
SFR(TWDR, 0xAD);
SFR(TWBR, 0xAE);

// Oscillator control registers
SFR(PCON,   0x87);      
SFR(CLKREG, 0x8F);

// Keyboard control registers
SFR(GPMOD, 0x9A);
SFR(GPLS,  0x9B);
SFR(GPIEN, 0x9C);
SFR(GPIF,  0x9D);

// SPI registers
SFR(SPSR, 0xE8 );
	SBIT(SPIF,  0xE8, 7);
	SBIT(WCOL,  0xE8, 6);
	SBIT(MODF,  0xE8, 5);
	SBIT(TXE,   0xE8, 4);
	SBIT(SSIG,  0xE8, 2);
	SBIT(DISSO, 0xE8, 1);
	SBIT(ENH,   0xE8, 0);
SFR(SPCR, 0xE9);
	#define TSCK 0x80
	#define SPE  0x40
	#define DORD 0x20
	#define MSTR 0x10
	#define CPOL 0x08
	#define CPHA 0x04
	#define SPR1 0x02
	#define SPR0 0x01
SFR(SPDR, 0xEA);

// Flash Data registers
SFR(MEMCON, 0x96);
	#define IAP    0x80
	#define AERS   0x40
	#define LDPG   0x20
	#define MWEN   0x10
	#define DMEN   0x08
	#define ERR    0x04
	#define WRTINH 0x01

// Comparator registers
SFR(ACSRA, 0x97);
SFR(ACSRB, 0x9F);
SFR(AREF,  0xAF);

//-- ADC / DAC  registers
SFR(DADC, 0xD9); // DADC Control register
	#define ADIF   0x80
	#define GO_BSY 0x40
	#define DAC    0x20
	#define ADCE   0x10
	#define LADJ   0x08
	#define ACK2   0x04
	#define ACK1   0x02
	#define ACK0   0x01
SFR(DADI, 0xDA); // DADC Input Control Register
	#define ACON 0x80
	#define IREF 0x40
	#define TRG1 0x20
	#define TRG0 0x10
	#define DIFF 0x08
	#define ACS2 0x04
	#define ACS1 0x02
	#define ACS0 0x01
SFR(DADL, 0xDC);
SFR(DADH, 0xDD);

#endif /* REG_AT89LP6440_H */
