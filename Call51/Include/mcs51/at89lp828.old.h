/*-------------------------------------------------------------------------
   Register Declarations for the Atmel AT89LP428/828 Processor

   Written By -  Jesus Calvino-Fraga / jesusc at ece.ubc.ca (February 2012)
   (Based on AT89LP828 Datasheet from August 2009:
   http://www.atmel.com/Images/doc3654A.pdf)

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
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA

-------------------------------------------------------------------------*/

#ifndef __AT89LP828_H__
#define __AT89LP828_H__

sfr at (0x81) SP;   // Stack Pointer
sfr at (0x82) DPL;  // Data Pointer Low Byte
sfr at (0x83) DPH;  // Data Pointer High Byte
sfr at (0x82) DP0L; // Data Pointer Low Byte
sfr at (0x83) DP0H; // Data Pointer High Byte
sfr at (0x84) DP1L; // Alternate Data Pointer Low Byte
sfr at (0x85) DP1H; // Alternate Data Pointer High Byte
sfr at (0x86) PAGE; // EDATA Page Register . . . . . . . PAGE.0
sfr at (0x87) PCON; // Power Control Register SMOD1 SMOD0 PWDEX POF GF1 GF0 PD IDL
sfr at (0x88) TCON; // Timer/Counter Control Register TF1 TR1 TF0 TR0 IE1 IT1 IE0 IT0
	sbit at (0x88) IT0;
	sbit at (0x89) IE0;
	sbit at (0x8A) IT1;
	sbit at (0x8B) IE1;
	sbit at (0x8C) TR0;
	sbit at (0x8D) TF0;
	sbit at (0x8E) TR1;
	sbit at (0x8F) TF1;
sfr at (0x89) TMOD;   // Timer/Counter Mode Control Register GATE1 C/T1 T1M1 T1M0 GATE0 C/T0 T0M0 T0M1
sfr at (0x8A) TL0;    // Timer/Counter 0 Low Byte
sfr at (0x8B) TL1;    // Timer/Counter 1 Low Byte
sfr at (0x8C) TH0;    // Timer/Counter 0 High Byte
sfr at (0x8D) TH1;    // Timer/Counter 1 High Byte
sfr at (0x8F) CLKREG; // Clock Control Register TPS3 TPS2 TPS1 TPS0 CDV2 CDV1 CDV0 COE
sfr at (0x90) P1;     // 8-bit Port 1
	sbit at (0x90) P1_0;
	sbit at (0x91) P1_1;
	sbit at (0x92) P1_2;
	sbit at (0x93) P1_3;
	sbit at (0x94) P1_4;
	sbit at (0x95) P1_5;
	sbit at (0x96) P1_6;
	sbit at (0x97) P1_7;
sfr at (0x91) TCONB;   // Timer/Counter Control Register B PWM1EN PWM0EN PSC12 PSC11 PSC10 PSC02 PSC01 PSC00
sfr at (0x92) RL0;     // Timer/Counter 0 Reload Low
sfr at (0x93) RL1;     // Timer/Counter 1 Reload low
sfr at (0x94) RH0;     // Timer/Counter 0 Reload High
sfr at (0x95) RH1;     // Timer/Counter 1 Reload High
sfr at (0x96) MEMCON;  // Memory Control Register IAP AERS LDPG MWEN DMEN ABORT . WRTINH
sfr at (0x97) ACSRA;   // Analog Comparator a Control and Status Register CSA1 CSA0 CONA CFA CENA CMA2 CMA1 CMA0
sfr at (0x98) SCON;    // Serial Port Control Register SM0/FE SM1 SM2 REN TB8 RB8 T1 RI
	sbit at (0x98) RI;
	sbit at (0x99) TI;
	sbit at (0x9A) RB8;
	sbit at (0x9B) TB8;
	sbit at (0x9C) REN;
	sbit at (0x9D) SM2;
	sbit at (0x9E) SM1;
	sbit at (0x9F) SM0;
sfr at (0x99) SBUF;   // Serial Data Buffer
sfr at (0x9A) GPMOD;  // General-purpose Interrupt Mode Register GPMOD7 GPMOD6 GPMOD5 GPMOD4 GPMOD3 GPMOD2 GPMOD1 GPMOD0
sfr at (0x9B) GPLS;   // General-purpose Interrupt Level Select Register GPLS7 GPLS6 GPLS5 GPLS4 GPLS3 GPLS2 GPLS1 GPLS0
sfr at (0x9C) GPIEN;  // General-purpose Interrupt Enable Register GPIEN7 GPIEN6 GPIEN5 GPIEN4 GPIEN3 GPIEN2 GPIEN1 GPIEN0
sfr at (0x9D) GPIF;   // General-purpose Interrupt Flag Register GPIF7 GPIF6 GPIF5 GPIF4 GPIF3 GPIF2 GPIF1 GPIF0
sfr at (0x9F) ACSRB;  // Analog Comparator B Control and Status Register CSB1 CSB0 CONB CFB CENB CMB2 CMB1 CMB0
sfr at (0xA0) P2;     // 8-bit Port 2
	sbit at (0xA0) P2_0;
	sbit at (0xA1) P2_1;
	sbit at (0xA2) P2_2;
	sbit at (0xA3) P2_3;
	sbit at (0xA4) P2_4;
	sbit at (0xA5) P2_5;
	sbit at (0xA6) P2_6;
	sbit at (0xA7) P2_7;
sfr at (0xA2) DPCF;   // Data Pointer Configuration Register DPU1 DPU0 DPD1 DPD0 SIGEN 0 . DPS
sfr at (0xA6) WDTRST; // WatchDog Timer Reset
sfr at (0xA7) WDTCON; // Watchdog Control Register PS2 PS1 PS0 WDIDLE . SWRST WDTOVF WDTEN
sfr at (0xA8) IE;      // Interrupt Enable Register EA EC ET2 ES ET1 EX1 ET0 EX0
	sbit at (0xA8) EX0;
	sbit at (0xA9) ET0;
	sbit at (0xAA) EX1;
	sbit at (0xAB) ET1;
	sbit at (0xAC) ES;
	sbit at (0xAD) ET2;
	sbit at (0xAE) EC;
	sbit at (0xAF) EA;
sfr at (0xA9) SADDR;  // Slave Address
sfr at (0xAF) AREF;   // Analog Comparator Reference Control Register CBC1 CBC0 RFB1 RFB0 CAC1 CAC0 RFA1 RFA0
sfr at (0xB0) P3;     // 8-bit Port 3
	sbit at (0xB0) P3_0;
	sbit at (0xB1) P3_1;
	sbit at (0xB2) P3_2;
	sbit at (0xB3) P3_3;
	sbit at (0xB4) P3_4;
	sbit at (0xB5) P3_5;
	sbit at (0xB6) P3_6;
	sbit at (0xB7) P3_7;
sfr at (0xB4) IE2;    // Interrupt Enable 2 Register . . . . . ESP ECC EGP
sfr at (0xB5) IP2;    // Interrupt Priority 2 Register IP2D . . . . PSP PCC PGP
sfr at (0xB6) IP2H;   // Interrupt Priority 2 High Register IP3D . . . . PSPH PCCH PGPH
sfr at (0xB7) IPH;    // Interrupt Priority High Register IP1D PCH PT2H PSH PT1H PX1H PT0H PX0H
sfr at (0xB8) IP;     // Interrupt Priority Register IP0D PC PT2 PS PT1 PX1 PT0 PX0
sfr at (0xB9) SADEN;  // Slave Address Mask
sfr at (0xBE) P4M0;   // Port 4 Mode 0
sfr at (0xBF) P4M1;   // Port 4 Mode 1
sfr at (0xC0) P4;     // 8-bit Port 4
    sbit at (0xC0) P4_0;
    sbit at (0xC1) P4_1;
    sbit at (0xC2) P4_2;
    sbit at (0xC3) P4_3;
    sbit at (0xC4) P4_4;
    sbit at (0xC5) P4_5;
    sbit at (0xC6) P4_6;
    sbit at (0xC7) P4_7;
sfr at (0xC2) P1M0;   // Port 1 Mode 0
sfr at (0xC3) P1M1;   // Port 1 Mode 1
sfr at (0xC4) P2M0;   // Port 2 Mode 0
sfr at (0xC5) P2M1;   // Port 2 Mode 1
sfr at (0xC6) P3M0;   // Port 3 Mode 0
sfr at (0xC7) P3M1;   // Port 3 Mode 1
sfr at (0xC8) T2CON;  // Timer/Counter 2 Control Register TF2 EXF2 RCLK TCLK EXEN2 TR2 C/T2 CP/RL2
	sbit at (0xC8) CP_RL2;
	sbit at (0xC9) C_T2;
	sbit at (0xCA) TR2;
	sbit at (0xCB) EXEN2;
	sbit at (0xCC) TCLK;
	sbit at (0xCD) RCLK;
	sbit at (0xCE) EXF2;
	sbit at (0xCF) TF2;
sfr at (0xC9) T2MOD;  // Timer 2 Mode Control Register PHSD PHS2 PHS1 PHS0 T2CM1 T2CM0 T2OE DCEN
sfr at (0xCA) RCAP2L; // Timer/Counter 2 Reload/Capture Low Byte
sfr at (0xCB) RCAP2H; // Timer/Counter 2 Reload/Capture High Byte
sfr at (0xCC) TL2;    // Timer/Counter 2 Low Byte
sfr at (0xCD) TH2;    // Timer/Counter 2 High Byte
sfr at (0xD0) PSW;    // Program Status Word CY AC F0 RS1 RS0 OV F1 P
	sbit at (0xD0) P;
	sbit at (0xD1) F1;
	sbit at (0xD2) OV;
	sbit at (0xD3) RS0;
	sbit at (0xD4) RS1;
	sbit at (0xD5) F0;
	sbit at (0xD6) AC;
	sbit at (0xD7) CY;
sfr at (0xD1) T2CCA;  // Timer/Counter 2 Compare/Capture Address . . . . . . T2CCA.1 T2CCA.0
sfr at (0xD2) T2CCL;  // Timer/Counter 2 Compare/Capture Data Low T2CCD.7 T2CCD.6 T2CCD.5 T2CCD.4 T2CCD.3 T2CCD.2 T2CCD.1 T2CCD.0
sfr at (0xD3) T2CCH;  // Timer/Counter 2 Compare/Capture Data High T2CCD.15 T2CCD.14 T2CCD.13 T2CCD.12 T2CCD.11 T2CCD.10 T2CCD.9 T2CCD.8
sfr at (0xD4) T2CCC;  // Timer/Counter 2 Compare/Capture Control CIENx CDIRx . CTCx CCMx CxM2 CxM1 CxM0
sfr at (0xD5) T2CCF;  // Timer/Counter 2 Compare/Capture Flags . . . . CCFD CCFC CCFB CCFA
sfr at (0xE0) ACC;    // Accumulator
	sbit at (0xE0) ACC_0;
	sbit at (0xE1) ACC_1;
	sbit at (0xE2) ACC_2;
	sbit at (0xE3) ACC_3;
	sbit at (0xE4) ACC_4;
	sbit at (0xE5) ACC_5;
	sbit at (0xE6) ACC_6;
	sbit at (0xE7) ACC_7;
sfr at (0xE8) SPSR;  // SPI Status Register SPIF WCOL MODF TXE . SSIG DISSO ENH
	sbit at (0xE8) ENH;
	sbit at (0xE9) DISSO;
	sbit at (0xEA) SSIG;
	sbit at (0xEC) TXE;
	sbit at (0xED) MODF;
	sbit at (0xEE) WCOL;
	sbit at (0xEF) SPIF;
sfr at (0xE9) SPCR; // SPI Control Register TSCK SPE DORD MSTR CPOL CPHA SPR1 SPR0
sfr at (0xEA) SPDR; // SPI Data Register
sfr at (0xF0) B;    // B Register
	sbit at (0xF0) B_0;
	sbit at (0xF1) B_1;
	sbit at (0xF2) B_2;
	sbit at (0xF3) B_3;
	sbit at (0xF4) B_4;
	sbit at (0xF5) B_5;
	sbit at (0xF6) B_6;
	sbit at (0xF7) B_7;
#endif
