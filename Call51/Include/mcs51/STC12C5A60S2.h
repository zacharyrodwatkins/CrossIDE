/*-------------------------------------------------------------------------
   Register Declarations for the STC STC12C5A60S2 Processor

   Written By -  Jesus Calvino-Fraga / jesusc at ece.ubc.ca (February 2012)
   (Based on STC MCU Limited STC12C5A60S2 series MCU Data Sheet from
   2010-10-23: http://www.stc-51.com/datasheet/STC12C5A-english.pdf)

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

#ifndef __STC12C5A60S2_H__
#define __STC12C5A60S2_H__

sfr at (0x80) P0; // Port 0  P0.7 P0.6 P0.5 P0.4 P0.3 P0.2 P0.1 P0.0
	sbit at (0x80) P0_0 ;
	sbit at (0x81) P0_1 ;
	sbit at (0x82) P0_2 ;
	sbit at (0x83) P0_3 ;
	sbit at (0x84) P0_4 ;
	sbit at (0x85) P0_5 ;
	sbit at (0x86) P0_6 ;
	sbit at (0x87) P0_7 ;
sfr at (0x81) SP; / / Stack Pointer 
sfr at (0x82) DPL;  // Data Pointer Low 
sfr at (0x83) DPH;  // Data Pointer High 
sfr at (0x87) PCON; // Power Control SMOD SMOD0 LVDF POF GF1 GF0 PD IDL
sfr at (0x88) TCON; // Timer Control TF1 TR1 TF0 TR0 IE1 IT1 IE0 IT0
	sbit at (0x88) IT0;
	sbit at (0x89) IE0;
	sbit at (0x8A) IT1;
	sbit at (0x8B) IE1;
	sbit at (0x8C) TR0;
	sbit at (0x8D) TF0;
	sbit at (0x8E) TR1;
	sbit at (0x8F) TF1;
sfr at (0x89) TMOD; // Timer Mode  GATE C/T M1 M0 GATE C/T M1 M0
sfr at (0x8A) TL0; // Timer Low 0 
sfr at (0x8B) TL1; // Timer Low 1 
sfr at (0x8C) TH0; // Timer High 0 
sfr at (0x8D) TH1; // Timer High 1 
sfr at (0x8E) AUXR; // Auxiliary register  T0x12 T1x12 UART_M0x6 BRTR S2SMOD BRTx12 EXTRAM S1BRS
sfr at (0x8F) WAKE_CLKO; // CLK_Output Power down Wake-up control register PCAWAKEUP RXD_PIN_IE T1_PIN_IE T0_PIN_IE LVD_WAKE BRTCLKO T1CLKO T0CLKO
sfr at (0x90) P1; // Port 1  P1.7 P1.6 P1.5 P1.4 P1.3 P1.2 P1.1 P1.0
	sbit at (0x90) P1_0 ;
	sbit at (0x91) P1_1 ;
	sbit at (0x92) P1_2 ;
	sbit at (0x93) P1_3 ;
	sbit at (0x94) P1_4 ;
	sbit at (0x95) P1_5 ;
	sbit at (0x96) P1_6 ;
	sbit at (0x97) P1_7 ;
sfr at (0x91) P1M1;    // P1 configuration 1 
sfr at (0x92) P1M0;    // P1 configuration 0 
sfr at (0x93) P0M1;    // P0 configuration 1 
sfr at (0x94) P0M0;    // P0 configuration 0 
sfr at (0x95) P2M1;    // P2 configuration 1 
sfr at (0x96) P2M0;    // P2 configuration 0 
sfr at (0x97) CLK_DIV; // Clock Divider  - - - - - CLKS2 CLKS1 CLKS0
sfr at (0x98) SCON;    // Serial Control  SM0/FE SM1 SM2 REN TB8 RB8 TI RI
	sbit at (0x98) RI   ;
	sbit at (0x99) TI   ;
	sbit at (0x9A) RB8  ;
	sbit at (0x9B) TB8  ;
	sbit at (0x9C) REN  ;
	sbit at (0x9D) SM2  ;
	sbit at (0x9E) SM1  ;
	sbit at (0x9F) SM0  ;
sfr at (0x99) SBUF;   // Serial Buffer 
sfr at (0x9A) S2CON;  // S2 Control  S2SM0 S2SM1 S2SM2 S2REN S2TB8 S2RB8 S2TI S2RI
sfr at (0x9B) S2SBUF; // S2 Serial Buffer 
sfr at (0x9C) BRT;    // Dedicated Baud-Rate Timer 
sfr at (0x9D) P1ASF;  // P1 Analog Special Function  P17ASF P16ASF P15ASF P14ASF P13ASF P12ASF P11ASF P10ASF
sfr at (0xA0) P2;     // Port 2  P2.7 P2.6 P2.5 P2.4 P2.3 P2.2 P2.1 P2.0
	sbit at (0xA0) P2_0 ;
	sbit at (0xA1) P2_1 ;
	sbit at (0xA2) P2_2 ;
	sbit at (0xA3) P2_3 ;
	sbit at (0xA4) P2_4 ;
	sbit at (0xA5) P2_5 ;
	sbit at (0xA6) P2_6 ;
	sbit at (0xA7) P2_7 ;
sfr at (0xA1) BUS_SPEED; // Bus-Speed Control  - - ALES1 ALES0 - RWS2 RWS1 RWS0
sfr at (0xA2) AUXR1;     // Auxiliary register 1  - PCA_P4 SPI_P4 S2_P4 GF2 ADRJ - DPS
sfr at (0xA8) IE;        // Interrupt Enable  EA ELVD EADC ES ET1 EX1 ET0 EX0
	sbit at (0xA8) EX0  ;
	sbit at (0xA9) ET0  ;
	sbit at (0xAA) EX1  ;
	sbit at (0xAB) ET1  ;
	sbit at (0xAC) ES   ;
	sbit at (0xAD) EADC ;
	sbit at (0xAE) ELVD ;
	sbit at (0xAF) EA   ;
sfr at (0xA9) SADDR; // Slave Address 
sfr at (0xAF) IE2;   // Interrupt Enable 2  - - - - - - ESPI ES2
sfr at (0xB0) P3;    // Port 3  P3.7 P3.6 P3.5 P3.4 P3.3 P3.2 P3.1 P3.0
	sbit at (0xB0) P3_0 ;
	sbit at (0xB1) P3_1 ;
	sbit at (0xB2) P3_2 ;
	sbit at (0xB3) P3_3 ;
	sbit at (0xB4) P3_4 ;
	sbit at (0xB5) P3_5 ;
	sbit at (0xB6) P3_6 ;
	sbit at (0xB7) P3_7 ;
	// Alternate bit names	
	sbit at (0xB0) RXD  ;
	sbit at (0xB1) TXD  ;
	sbit at (0xB2) INT0 ;
	sbit at (0xB3) INT1 ;
	sbit at (0xB4) T0   ;
	sbit at (0xB5) T1   ;
	sbit at (0xB6) WR   ;
	sbit at (0xB7) RD   ;
sfr at (0xB1) P3M1; // P2 configuration 1 
sfr at (0xB2) P3M0; // P3 configuration 0 
sfr at (0xB3) P4M1; // P4 configuration 1 
sfr at (0xB4) P4M0; // P4 configuration 0 
sfr at (0xB5) IP2;  // 2rd Interrupt Priority Low register  - - - - - - PSPI PS2
sfr at (0xB6) IP2H; // 2rd Interrupt Priority High register  - - - - - - PSPIH PS2H
sfr at (0xB7) IPH;  // Interrupt Priority High  PPCAH PLVDH PADCH PSH PT1H PX1H PT0H PX0H
sfr at (0xB8) IP;   // Interrupt Priority Low  PPCA PLVD PADC PS PT1 PX1 PT0 PX0
	sbit at (0xB8) PX0  ;
	sbit at (0xB9) PT0  ;
	sbit at (0xBA) PX1  ;
	sbit at (0xBB) PT1  ;
	sbit at (0xBC) PS  ;
	sbit at (0xBD) PADC  ;
	sbit at (0xBE) PLVD  ;
	sbit at (0xBF) PPCA  ;
sfr at (0xB9) SADEN;     // Slave Address Mask 
sfr at (0xBB) P4SW;      // Port 4 switch  - LVD_P4.6 ALE_P4.5 NA_P4.4 - - - -
sfr at (0xBC) ADC_CONTR; // ADC Control  ADC_POWER SPEED1 SPEED0 ADC_FLAG ADC_START CHS2 CHS1 CHIS0
sfr at (0xBD) ADC_RES;   // ADC Result 
sfr at (0xBE) ADC_RESL;  // ADC Result Low 
sfr at (0xC0) P4;        // Port 4  P4.7 P4.6 P4.5 P4.4 P4.3 P4.2 P4.1 P4.0
	sbit at (0xC0) P4_0 ;
	sbit at (0xC1) P4_1 ;
	sbit at (0xC2) P4_2 ;
	sbit at (0xC3) P4_3 ;
	sbit at (0xC4) P4_4 ;
	sbit at (0xC5) P4_5 ;
	sbit at (0xC6) P4_6 ;
	sbit at (0xC7) P4_7 ;
sfr at (0xC1) WDT_CONTR; // Watch-Dog-Timer Control Register  WDT_FLAG - EN_WDT CLR_WDT IDLE_WDT PS2 PS1 PS0
sfr at (0xC2) IAP_DATA;  // ISP/IAP Flash Data Register 
sfr at (0xC3) IAP_ADDRH; // ISP/IAP Flash Address High 
sfr at (0xC4) IAP_ADDRL; // ISP/IAP Flash Address Low 
sfr at (0xC5) IAP_CMD;   // ISP/IAP Flash Command Register  - - - - - - MS1 MS0
sfr at (0xC6) IAP_TRIG;  // ISP/IAP Flash Command Trigger 
sfr at (0xC7) IAP_CONTR; // ISP/IAP Control Register  IAPEN SWBS SWRST CMD_FAIL - WT2 WT1 WT0
sfr at (0xC8) P5;        // Port 5  - - - - P5.3 P5.2 P5.1 P5.0
	sbit at (0xC8) P5_0 ;
	sbit at (0xC9) P5_1 ;
	sbit at (0xCA) P5_2 ;
	sbit at (0xCB) P5_3 ;
sfr at (0xC9) P5M1;   // P5 Configuration 1 
sfr at (0xCA) P5M0;   // P5 Configuration 0 
sfr at (0xCD) SPSTAT; // SPI Status register  SPIF WCOL - - - - - -
sfr at (0xCE) SPCTL;  // SPI control register  SSIG SPEN DORD MSTR CPOL CPHA SPR1 SPR0
sfr at (0xCF) SPDAT;  // SPI Data register  - - - - - - - -
sfr at (0xD0) PSW;    // Program Status Word  CY AC F0 RS1 RS0 OV F1 P
	sbit at (0xD0) P    ;
	sbit at (0xD1) F1   ;
	sbit at (0xD2) OV   ;
	sbit at (0xD3) RS0  ;
	sbit at (0xD4) RS1  ;
	sbit at (0xD5) F0   ;
	sbit at (0xD6) AC   ;
	sbit at (0xD7) CY   ;
sfr at (0xD8) CCON; // PCA Control Register  CF CR - - - - CCF1 CCF0
	sbit at (0xD8) CCF0 ;
	sbit at (0xD9) CCF1 ;
	sbit at (0xDE) CR ;
	sbit at (0xDF) CF ;
sfr at (0xD9) CMOD;   // PCA Mode Register  CIDL - - - CPS2 CPS1 CPS0 ECF
sfr at (0xDA) CCAPM0; // PCA Module 0 Mode Register  - ECOM0 CAPP0 CAPN0 MAT0 TOG0 PWM0 ECCF0
sfr at (0xDB) CCAPM1; // PCA Module 1 Mode Register  - ECOM1 CAPP1 CAPN1 MAT1 TOG1 PWM1 ECCF1
sfr at (0xE0) ACC;    // Accumulator 
	sbit at (0xE0) ACC_0 ;
	sbit at (0xE1) ACC_1 ;
	sbit at (0xE2) ACC_2 ;
	sbit at (0xE3) ACC_3 ;
	sbit at (0xE4) ACC_4 ;
	sbit at (0xE5) ACC_5 ;
	sbit at (0xE6) ACC_6 ;
	sbit at (0xE7) ACC_7 ;
sfr at (0xE9) CL;     // PCA Base Timer Low 
sfr at (0xEA) CCAP0L; // PCA module 0 capture register low 
sfr at (0xEB) CCAP1L; // PCA module 1 capture register low 
sfr at (0xF0) B;      // B Register 
	sbit at (0xF0) B_0 ;
	sbit at (0xF1) B_1 ;
	sbit at (0xF2) B_2 ;
	sbit at (0xF3) B_3 ;
	sbit at (0xF4) B_4 ;
	sbit at (0xF5) B_5 ;
	sbit at (0xF6) B_6 ;
	sbit at (0xF7) B_7 ;
sfr at (0xF2) PCA_PWM0; // PCA PWM mode auxiliary register 1  - - - - - - EPC0H EPC0L
sfr at (0xF3) PCA_PWM1; // PCA PWM mode auxiliary register 1  - - - - - - EPC1H EPC1L
sfr at (0xF9) CH;       // PCA Base Timer High 
sfr at (0xFA) CCAP0H;   // PCA module 0 capture register high 
sfr at (0xFB) CCAP1H;   // PCA module 1 capture register high 

#endif  //__STC12C5A60S2_H__
