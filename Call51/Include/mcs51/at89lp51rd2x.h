/*  Register Declarations for Atmel's AT89LP51RD2 and similar

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
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA */

#ifndef REG_AT89LP51RD2_H
#define REG_AT89LP51RD2_H

#include <compiler.h>

SFR(P0, 0x80; // Port 0 Latch
	SBIT(P0_7, 0x80, 7); // Port 0 Bit 7
	SBIT(P0_6, 0x80, 6); // Port 0 Bit 6
	SBIT(P0_5, 0x80, 5); // Port 0 Bit 5
	SBIT(P0_4, 0x80, 4); // Port 0 Bit 4
	SBIT(P0_3, 0x80, 3); // Port 0 Bit 3
	SBIT(P0_2, 0x80, 2); // Port 0 Bit 2
	SBIT(P0_1, 0x80, 1); // Port 0 Bit 1
	SBIT(P0_0, 0x80, 0); // Port 0 Bit 0
SFR(SP, 0x81); // Stack Pointer
SFR(DPL, 0x82); // Data Pointer Low
SFR(DPH, 0x83); // Data Pointer High
SFR(CKSEL, 0x85); // Clock Selection Register
SFR(OSCCON, 0x86); // Oscillator Contro l Register
SFR(PCON, 0x87); // Power Control
SFR(TCON, 0x88); // Timer/Counter 0 and 1 Control
	SBIT(TF1, 0x88, 7); // Timer 1 Overflow Flag
	SBIT(TR1, 0x88, 6); // Timer 1 On/Off Control
	SBIT(TF0, 0x88, 5); // Timer 0 Overflow Flag
	SBIT(TR0, 0x88, 4); // Timer 0 On/Off Control
	SBIT(IE1, 0x88, 3); // Ext. Interrupt 1 Edge Flag
	SBIT(IT1, 0x88, 2); // Ext. Interrupt 1 Type
	SBIT(IE0, 0x88, 1); // Ext. Interrupt 0 Edge Flag
	SBIT(IT0, 0x88, 0); // Ext. Interrupt 0 Type
SFR(TMOD, 0x89); // Timer/Counter 0 and 1 Modes
SFR(TL0, 0x8A); // Timer/Counter 0 Low Byte
SFR(TL1, 0x8B); // Timer/Counter 1 Low Byte
SFR(TH0, 0x8C); // Timer/Counter 0 High Byte
SFR(TH1, 0x8D); // Timer/Counter 1 High Byte
SFR(AUXR, 0x8E); // Auxiliary Register 0
SFR(CKCON0, 0x8F); // Clock Control Register 0
SFR(P1, 0x90); // Port 1 Latch
	SBIT(P1_7, 0x90, 7); // Port 1 Bit 7
	SBIT(P1_6, 0x90, 6); // Port 1 Bit 6
	SBIT(P1_5, 0x90, 5); // Port 1 Bit 5
	SBIT(P1_4, 0x90, 4); // Port 1 Bit 4
	SBIT(P1_3, 0x90, 3); // Port 1 Bit 3
	SBIT(P1_2, 0x90, 2); // Port 1 Bit 2
	SBIT(P1_1, 0x90, 1); // Port 1 Bit 1
	SBIT(P1_0, 0x90, 0); // Port 1 Bit 0
SFR(TCONB, 0x91); // Timer/Counter 0 and 1 Mode B
SFR(BMSEL, 0x92); // Bank memory selection
SFR(SSCON, 0x93); // Synchronous Serial Control
SFR(SSCS, 0x94); // Synchronous Serial Status
SFR(SSDAT, 0x95); // Synchronous Serial Data
SFR(SSADR, 0x96); // Synchronous Serial Address
SFR(CKRL, 0x97); // Clock Reload Register
SFR(SCON, 0x98); // Serial Control
	SBIT(SM0, 0x98, 7); // Serial Port Mode Bit 0
	SBIT(SM1, 0x98, 6); // Serial Port Mode Bit 1
	SBIT(SM2, 0x98, 5); // Multiprocessor Communication Enable
	SBIT(REN, 0x98, 4); // Serial Reception Enable
	SBIT(TB8, 0x98, 3); // Transmitter Bit 8
	SBIT(RB8, 0x98, 2); // Receiver Bit 8
	SBIT(TI,  0x98, 1); // Transmit Interrupt Flag
	SBIT(RI,  0x98, 0); // Receive Interrupt Flag
SFR(SBUF, 0x99); // Serial Data Buffer
SFR(BRL, 0x9A); // Baud Rate Reload
SFR(BDRCON, 0x9B); // Baud Rate Control
SFR(KBLS, 0x9C); // Keyboard Level Selector
SFR(KBE, 0x9D); // Keyboard Input Enable
SFR(KBF, 0x9E); // Keyboard Flag Register
SFR(KBMOD, 0x9F); // Keyboard Mode Register
SFR(P2, 0xA0); // Port 2 Latch
	SBIT(P2_7, 0xA0, 7); // Port 2 Bit 7
	SBIT(P2_6, 0xA0, 6); // Port 2 Bit 6
	SBIT(P2_5, 0xA0, 5); // Port 2 Bit 5
	SBIT(P2_4, 0xA0, 4); // Port 2 Bit 4
	SBIT(P2_3, 0xA0, 3); // Port 2 Bit 3
	SBIT(P2_2, 0xA0, 2); // Port 2 Bit 2
	SBIT(P2_1, 0xA0, 1); // Port 2 Bit 1
	SBIT(P2_0, 0xA0, 0); // Port 2 Bit 0
SFR(DPCF, 0xA1); // Datapointer Config Register
SFR(AUXR1, 0xA2); // Auxiliary Register 1
SFR(ACSRA, 0xA3); // Comparator A Control Register
SFR(DADC, 0xA4); // DAC/ADC Control Register
SFR(DADI, 0xA5); // DAC/ADC Input Register
SFR(WDTRST, 0xA6); // WatchDog Timer Reset
SFR(WDTPRG, 0xA7); // WatchDog Timer Program
SFR(IEN0, 0xA8); // Interrupt Enable Control 0
	SBIT(EA,  0xA8, 7); // Global Interrupt Enable
	SBIT(EC,  0xA8, 6); // PCA Interrpt Enable
	SBIT(ET2, 0xA8, 5); // Timer 2 Interrupt Enable
	SBIT(ES,  0xA8, 4); // Serial Port Interrupt Enable
	SBIT(ET1, 0xA8, 3); // Timer 1 Interrupt Enable
	SBIT(EX1, 0xA8, 2); // External Interrupt 1 Enable
	SBIT(ET0, 0xA8, 1); // Timer 0 Interrupt Enable
	SBIT(EX0, 0xA8, 0); // External Interrupt 0 Enable
SFR(SADDR, 0xA9); // Slave Address
SFR(ACSRB, 0xAB); // Comparator B Control Register
SFR(DADL, 0xAC); // DAC/ADC Data Low Register
SFR(DADH, 0xAD); // DAC/ADC Data High Register
SFR(CLKREG, 0xAE); // Clock Register
SFR(CKCON1, 0xAF); // Clock Control Register 1
SFR(P3, 0xB0); // Port 3 Latch
	SBIT(P3_7, 0xB0, 7); // Port 3 Bit 7
	SBIT(P3_6, 0xB0, 6); // Port 3 Bit 6
	SBIT(P3_5, 0xB0, 5); // Port 3 Bit 5
	SBIT(P3_4, 0xB0, 4); // Port 3 Bit 4
	SBIT(P3_3, 0xB0, 3); // Port 3 Bit 3
	SBIT(P3_2, 0xB0, 2); // Port 3 Bit 2
	SBIT(P3_1, 0xB0, 1); // Port 3 Bit 1
	SBIT(P3_0, 0xB0, 0); // Port 3 Bit 0
SFR(IEN1, 0xB1); // Interrupt Enable Control 1
SFR(IPL1, 0xB2); // Interrupt Priority Control Low 1
SFR(IPH1, 0xB3); // Interrupt Priority Control High 1
SFR(IPH0, 0xB7); // Interrupt Priority Control High 0
SFR(IPL0, 0xB8); // Interrupt Priority Control Low 0
	SBIT(IP0DIS, 0xB8, 7); // Interrupt Level 0 Disable
	SBIT(PPCL,   0xB8, 6); // PCA Interrupt Priority Low
	SBIT(PT2L,   0xB8, 5); // Timer 2 Interrupt Priority Low
	SBIT(PSL,    0xB8, 4); // Serial Port Interrupt Priority Low
	SBIT(PT1L,   0xB8, 3); // Timer 1 Interrupt Priority Low
	SBIT(PX1L,   0xB8, 2); // External Interrupt 1 Priority Low
	SBIT(PT0L,   0xB8, 1); // Timer 0 Interrupt Priority Low
	SBIT(PX0L,   0xB8, 0); // External Interrupt 0 Priority Low
SFR(SADEN, 0xB9); // Slave Address Mask
SFR(AREF, 0xBD); // Comparator Reference Register
SFR(P4M0, 0xBE); // Port 4 Mode 0
SFR(P4M1, 0xBF); // Port 4 Mode 1
SFR(P4, 0xC0); // Port 4 Latch
	SBIT(P4_7, 0xC0, 7); // Port 4 Bit 7
	SBIT(P4_6, 0xC0, 6); // Port 4 Bit 6
	SBIT(P4_5, 0xC0, 5); // Port 4 Bit 5
	SBIT(P4_4, 0xC0, 4); // Port 4 Bit 4
	SBIT(P4_3, 0xC0, 3); // Port 4 Bit 3
	SBIT(P4_2, 0xC0, 2); // Port 4 Bit 2
	SBIT(P4_1, 0xC0, 1); // Port 4 Bit 1
	SBIT(P4_0, 0xC0, 0); // Port 4 Bit 0
SFR(SPCON, 0xC3); // SPI Control
SFR(SPSTA, 0xC4); // SPI Status
SFR(SPDAT, 0xC5); // SPI Data
SFR(P3M0, 0xC6); // Port 3 Mode 0
SFR(P3M1, 0xC7); // Port 3 Mode 1
SFR(T2CON, 0xC8); // Timer/Counter 2 control
	SBIT(TF2,   0xC8, 7); // Timer 2 Overflow Flag
	SBIT(EXF2,  0xC8, 6); // Timer 2 External Flag
	SBIT(RCLK,  0xC8, 5); // Receive Clock Enable
	SBIT(TCLK,  0xC8, 4); // Transmit Clock Enable
	SBIT(EXEN2, 0xC8, 3); // Timer 2 Split Mode Enable
	SBIT(TR2,   0xC8, 2); // Timer 2 Run Control
	SBIT(C,     0xC8, 1); // Timer/Counter select 2
	SBIT(CP,    0xC8, 0); // Capture/Reload Select
SFR(T2MOD, 0xC9); // Timer/C ounter 2 Mode
SFR(RCAP2L, 0xCA); // Timer/Counter 2 Reload/Capture Low B.
SFR(RCAP2H, 0xCB); // Timer/Counter 2 Reload/Capture High B.
SFR(TL2, 0xCC); // Timer/Counter 2 Low Byte
SFR(TH2, 0xCD); // Timer/Counter 2 High Byte
SFR(P2M0, 0xCE); // Port 2 Mode 0
SFR(P2M1, 0xCF); // Port 2 Mode 1
SFR(PSW, 0xD0); // Program Status Word
	SBIT(CY,  0xD0, 7); // Carry Flag
	SBIT(AC,  0xD0, 6); // Auxiliary Carry Flag
	SBIT(F0,  0xD0, 5); // User Flag 0
	SBIT(RS1, 0xD0, 4); // Register Bank Select 1
	SBIT(RS0, 0xD0, 3); // Register Bank Select 0
	SBIT(OV,  0xD0, 2); // Overflow Flag
	SBIT(F1,  0xD0, 1); // User Flag 1
	SBIT(P,   0xD0, 0); // Accumulator Parity Flag
SFR(FCON, 0xD1); // Flash Control Register
SFR(EECON, 0xD2); // EEPROM Control Register
SFR(DPLB, 0xD4); // Alternate Data Pointer Low Byte
SFR(DPHB, 0xD5); // Alternate Data Pointer High Byte
SFR(P1M0, 0xD6); // Port 1 Mode 0
SFR(P1M1, 0xD7); // Port 1 Mode 1
SFR(CCON, 0xD8); // PCA Timer/Counter Control
	SBIT(CF,   0xD8, 7); // PCA Counter Overflow Flag
	SBIT(CR,   0xD8, 6); // PCA Counter Run Control Bit
	SBIT(CCF4, 0xD8, 4); // PCA Module 4 Interrupt Flag
	SBIT(CCF3, 0xD8, 3); // PCA Module 3 Interrupt Flag
	SBIT(CCF2, 0xD8, 2); // PCA Module 2 Interrupt Flag
	SBIT(CCF1, 0xD8, 1); // PCA Module 1 Interrupt Flag
	SBIT(CCF0, 0xD8, 0); // PCA Module 0 Interrupt Flag
SFR(CMOD, 0xD9); // PCA Timer/Counter Mode
SFR(CCAPM0, 0xDA); // PCA Timer/Counter Mode 0
SFR(CCAPM1, 0xDB); // PCA Timer/Counter Mode 1
SFR(CCAPM2, 0xDC); // PCA Timer/Counter Mode 2
SFR(CCAPM3, 0xDD); // PCA Timer/Counter Mode 3
SFR(CCAPM4, 0xDE); // PCA Timer/Counter Mode 4
SFR(ACC, 0xE0); // Accumulator
SFR(AX, 0xE1); // Extended Accumulator
SFR(DSPR, 0xE2); // DSP Control Register
SFR(FIRD, 0xE3); // FIFO Depth
SFR(MACL, 0xE4); // MAC Low Byte
SFR(MACH, 0xE5); // MAC High Byte
SFR(P0M0, 0xE6); // Port 0 Mode 0
SFR(P0M1, 0xE7); // Port 0 Mode 1
SFR(CL, 0xE9); // PCA Timer/Counter Low Byte
SFR(CCAP0L, 0xEA); // PCA Compare Capture Module 0 L
SFR(CCAP1L, 0xEB); // PCA Compare Capture Module 1 L
SFR(CCAP2L, 0xEC); // PCA Compare Capture Module 2 L
SFR(CCAP3L, 0xED); // PCA Compare Capture Module 3 L
SFR(CCAP4L, 0xEE); // PCA Compare Capture Module 4 L
SFR(SPX, 0xEF); // Extended Stack Pointer
SFR(B, 0xF0); // B Register
SFR(RL0, 0xF2); // Timer/Counter 0 Reload Low
SFR(RL1, 0xF3); // Timer/Counter 1 Reload Low
SFR(RH0, 0xF4); // Timer/Counter 0 Reload High
SFR(RH1, 0xF5); // Timer/Counter 1 Reload High
SFR(PAGE, 0xF6); // ERAM Page Register
SFR(BX, 0xF7); // Extended B Register
SFR(CH, 0xF9); // PCA Timer/Counter High Byte
SFR(CCAP0H, 0xFA); // PCA Compare Capture Module 0 H
SFR(CCAP1H, 0xFB); // PCA Compare Capture Module 1 H
SFR(CCAP2H, 0xFC); // PCA Compare Capture Module 2 H
SFR(CCAP3H, 0xFD); // PCA Compare Capture Module 3 H
SFR(CCAP4H, 0xFE); // PCA Compare Capture Module 4 H

#endif // REG_AT89LP51RD2_H
