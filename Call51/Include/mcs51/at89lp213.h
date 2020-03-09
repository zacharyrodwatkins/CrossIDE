/*-------------------------------------------------------------------------
Register Declarations for Atmel's AT89LP213

Written By - Jesus Calvino-Fraga / jesusc at ece.ubc.ca (April 2012)

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option); any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
-------------------------------------------------------------------------*/

#ifndef REG_AT89LP213_H
#define REG_AT89LP213_H

#include <compiler.h>

SFR(P1, 0x90); // Port 1 
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
SFR(P1M0, 0xC2); 
SFR(P1M1, 0xC3); 
SFR(P3, 0xB0); // Port 3 
	SBIT(P3_5, 0xB0, 5); 
	SBIT(P3_4, 0xB0, 4); 
	SBIT(P3_3, 0xB0, 3); 
	SBIT(P3_2, 0xB0, 2); 
	SBIT(T1,   0xB0, 5); 
	SBIT(T0,   0xB0, 4); 
	SBIT(INT1, 0xB0, 3); 
	SBIT(INT0, 0xB0, 2); 
SFR(P3M0, 0xC6); 
SFR(P3M1, 0xC7); 
SFR(PSW, 0xD0); // Program Status Word 
	SBIT(CY,  0xD0, 7); // Carry Flag 
	SBIT(AC,  0xD0, 6); // Auxiliary Carry Flag 
	SBIT(F0,  0xD0, 5); // User Flag 0 
	SBIT(RS1, 0xD0, 4); // Register Bank Select 1 
	SBIT(RS0, 0xD0, 3); // Register Bank Select 0 
	SBIT(OV,  0xD0, 2); // Overflow Flag 
	SBIT(UD,  0xD0, 1); 
	SBIT(P,   0xD0, 0); // Accumulator Parity Flag 
SFR(ACC, 0xE0); // Accumulator 
	SBIT(ACC_7, 0xE0, 7);
	SBIT(ACC_6, 0xE0, 6);
	SBIT(ACC_5, 0xE0, 5);
	SBIT(ACC_4, 0xE0, 4);
	SBIT(ACC_3, 0xE0, 3);
	SBIT(ACC_2, 0xE0, 2);
	SBIT(ACC_1, 0xE0, 1);
	SBIT(ACC_0, 0xE0, 0);
SFR(B, 0xF0); // B Register 
	SBIT(B_7, 0xF0, 7);
	SBIT(B_6, 0xF0, 6);
	SBIT(B_5, 0xF0, 5);
	SBIT(B_4, 0xF0, 4);
	SBIT(B_3, 0xF0, 3);
	SBIT(B_2, 0xF0, 2);
	SBIT(B_1, 0xF0, 1);
	SBIT(B_0, 0xF0, 0);
SFR(SP, 0x81); 
SFR(DPL, 0x82); // Data Pointer Low 
SFR(DPH, 0x83); // Data Pointer High 
SFR(AUXR1, 0xA2); 
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
SFR(TL0, 0x8A); 
SFR(TL1, 0x8B); 
SFR(TH0, 0x8C); 
SFR(TH1, 0x8D); 
SFR(TCONB, 0x91); 
SFR(RL0, 0x92); 
SFR(RL1, 0x93); 
SFR(RH0, 0x94); 
SFR(RH1, 0x95); 
SFR(WDTRST, 0xA6); 
SFR(WDTCON, 0xA7); 
SFR(IE, 0xA8); // Interrupt Enable 
	SBIT(EA,  0xA8, 7); // Global Interrupt Enable 
	SBIT(EC,  0xA8, 6); 
	SBIT(EGP, 0xA8, 5); 
	SBIT(ET1, 0xA8, 3); // Timer 1 Interrupt Enable 
	SBIT(EX1, 0xA8, 2); // External Interrupt 1 Enable 
	SBIT(ET0, 0xA8, 1); // Timer 0 Interrupt Enable 
	SBIT(EX0, 0xA8, 0); // External Interrupt 0 Enable 
SFR(IP, 0xB8); // Interrupt Priority 
	SBIT(PGP, 0xB8, 5); 
	SBIT(PT1, 0xB8, 3); // Timer 1 Priority 
	SBIT(PX1, 0xB8, 2); // External Interrupt 1 Priority 
	SBIT(PT0, 0xB8, 1); // Timer 0 Priority 
	SBIT(PX0, 0xB8, 0); // External Interrupt 0 Priority 
SFR(IPH, 0xB7); 
SFR(PCON, 0x87); 
SFR(CLKREG, 0x8F); 
SFR(GPMOD, 0x9A); 
SFR(GPLS, 0x9B); 
SFR(GPIEN, 0x9C); 
SFR(GPIF, 0x9D); 
SFR(SPSR, 0xE8); 
	SBIT(SPIF,  0xE8, 7); 
	SBIT(WCOL,  0xE8, 6); 
	SBIT(LDEN,  0xE8, 5); 
	SBIT(SSIG,  0xE8, 2); 
	SBIT(DISSO, 0xE8, 1); 
	SBIT(ENH,   0xE8, 0); 
SFR(SPCR, 0xE9); 
SFR(SPDR, 0xEA); 
SFR(ACSR, 0x97); 

#endif // REG_AT89LP213_H