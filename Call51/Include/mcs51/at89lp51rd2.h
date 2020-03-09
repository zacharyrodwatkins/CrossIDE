/*-------------------------------------------------------------------------
   Register Declarations for the Atmel AT89LP51RD2/ED2/ID2 Processor

   Written By -  Jesus Calvino-Fraga / jesusc at ece.ubc.ca (February 2012)
   (Based on AT89LP51RD2/AT89LP51ED2/AT89LP51ID2 Preliminary Datasheet
   from July 2011 by Atmel: http://www.atmel.com/Images/doc3573.pdf)

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

#ifndef __AT89LP51RD2_H__
#define __AT89LP51RD2_H__

// C51 Core SFRs
sfr at (0xE0) ACC;  // Accumulator
	sbit at (0xE0) ACC_0;
	sbit at (0xE1) ACC_1;
	sbit at (0xE2) ACC_2;
	sbit at (0xE3) ACC_3;
	sbit at (0xE4) ACC_4;
	sbit at (0xE5) ACC_5;
	sbit at (0xE6) ACC_6;
	sbit at (0xE7) ACC_7;
sfr at (0xF0) B;    // B Register
	sbit at (0xF0) B_0;
	sbit at (0xF1) B_1;
	sbit at (0xF2) B_2;
	sbit at (0xF3) B_3;
	sbit at (0xF4) B_4;
	sbit at (0xF5) B_5;
	sbit at (0xF6) B_6;
	sbit at (0xF7) B_7;
sfr at (0xD0) PSW;  // Program Status Word CY AC F0 RS1 RS0 OV F1 P
	sbit at (0xD0) P    ;
	sbit at (0xD1) F1   ;
	sbit at (0xD2) OV   ;
	sbit at (0xD3) RS0  ;
	sbit at (0xD4) RS1  ;
	sbit at (0xD5) F0   ;
	sbit at (0xD6) AC   ;
	sbit at (0xD7) CY   ;
sfr at (0x81) SP;   // Stack Pointer
sfr at (0xEF) SPX;  // Extended Stack Pointer
sfr at (0x82) DPL;  // Data Pointer Low Byte
sfr at (0x83) DPH;  // Data Pointer High Byte
sfr at (0xD4) DPLB; // Alternate Data Pointer Low Byte
sfr at (0xD5) DPHB; // Alternate Data Pointer High Byte
sfr at (0xF6) PAGE; // ERAM Page Register

// Digital Signal Processing SFRs
sfr at (0xE1) AX;   // Extended Accumulator
sfr at (0xF7) BX;   // Extended B Register
sfr at (0xE2) DSPR; // DSP Control Register MRW1 MRW0 SMLB SMLA CBE1 CBE0 MVCD DPRB
    #define MRW1   0x80
    #define MRW0   0x40
    #define SMLB   0x20
    #define SMLA   0x10
    #define CBE1   0x08
    #define CBE0   0x04
    #define MVCD   0x02
    #define DPRB   0x01
sfr at (0xE3) FIRD; // FIFO Depth
sfr at (0xE4) MACL; // MAC Low Byte
sfr at (0xE5) MACH; // MAC High Byte

// System Management SFRs
sfr at (0x87) PCON;    // Power Control SMOD1 SMOD0 PWDEX POF GF1 GF0 PD IDL
    #define SMOD1  0x80
    #define SMOD0  0x40
    #define PWDE   0x20
    #define POF    0x10
    #define GF1    0x08
    #define GF0    0x04
    #define PD     0x02
    #define IDL    0x01
sfr at (0x8E) AUXR;    // Auxiliary Register 0: DPU WS1 WS0/M0 XRS2 XRS1 XRS0 EXTRAM AO
    #define DPU    0x80
    #define WS1    0x40
    #define WS0    0x20
    #define M0     0x20
    #define XRS2   0x10
    #define XRS1   0x08
    #define XRS0   0x04
    #define EXTRAM 0x02
    #define AO     0x01
sfr at (0xA2) AUXR1;   // Auxiliary Register 1: – – ENBOOT XSTK GF3 0 – DPS
    //#define -    0x80
    //#define -    0x40
    #define ENBOOT 0x20
    #define XSTK   0x10
    #define GF3    0x08
    //#define 0    0x04
    //#define -    0x02
    #define DPS    0x01
sfr at (0xA1) DPCF;    // Datapointer Config Register DPU1 DPU0 DPD1 DPD0 – – – –
    #define DPU1   0x80
    #define DPU0   0x40
    #define DPD1   0x20
    #define DPD0   0x10
    //#define -    0x08
    //#define -    0x04
    //#define -    0x02
    //#define -    0x01
sfr at (0x97) CKRL;    // Clock Reload Register
sfr at (0x8F) CKCKON0; // Clock Control Register 0: TWIX2 WDTX2 PCAX2 SIX2 T2X2 T1X2 T0X2 X2
    #define TWIX2  0x80
    #define WDTX2  0x40
    #define PCAX2  0x20
    #define SIX2   0x10
    #define T2X2   0x08
    #define T1X2   0x04
    #define T0X2   0x02
    #define X2     0x01
sfr at (0xAF) CKCKON1; // Clock Control Register 1: – – – – – – – SPIX2
    //#define -    0x80
    //#define -    0x40
    //#define -    0x20
    //#define -    0x10
    //#define -    0x08
    //#define -    0x04
    //#define -    0x02
    #define SPIX2  0x01
sfr at (0x85) CKSEL;   // Clock Selection Register – – – – – – – CKS
    //#define -    0x80
    //#define -    0x40
    //#define -    0x20
    //#define -    0x10
    //#define -    0x08
    //#define -    0x04
    //#define -    0x02
    #define CKS    0x01
sfr at (0xAE) CLKREG;  // Clock Register TPS3 TPS2 TPS1 TPS0 – – – –
    #define TPS3   0x80
    #define TPS2   0x40
    #define TPS1   0x20
    #define TPS0   0x10
    //#define -    0x08
    //#define -    0x04
    //#define -    0x02
    //#define -    0x01
sfr at (0x85) OSCCON;  // Oscillator Contro l Register – – – – – SCLKT0 OscBEn OscAEn
    //#define -   0x80
    //#define -   0x40
    //#define -   0x20
    //#define -   0x10
    //#define -   0x08
    #define SCLKT0    0x04
    #define OscBEn    0x02
    #define OscAEn    0x01

// Interrupt SFRs
sfr at (0xA8) IE;   // Interrupt Enable Control 0
sfr at (0xA8) IEN0; // Interrupt Enable Control 0
	sbit at (0xA8) EX0  ;
	sbit at (0xA9) ET0  ;
	sbit at (0xAA) EX1  ;
	sbit at (0xAB) ET1  ;
	sbit at (0xAC) ES   ;
	sbit at (0xAD) ET2  ;
	sbit at (0xAE) EC   ;
	sbit at (0xAF) EA   ;
sfr at (0xB1) IEN1; // Interrupt Enable Control 1 – – EADC ECMP – ESPI ETWI EKB
  //#define ----   0x80
  //#define ----   0x40
    #define EADC   0x20
    #define ECMP   0x10
  //#define ----   0x08
    #define ESPI   0x04
    #define ETWI   0x02
    #define EKB    0x01
sfr at (0xB7) IPH0; // Interrupt Priority Control High 0: IP1D PPCH PT2H PHS PT1H PX1H PT0H PX0H
    #define IP1D   0x80
    #define PPCH   0x40
    #define PT2H   0x20
    #define PHS    0x10
    #define PT1H   0x08
    #define PX1H   0x04
    #define PT0H   0x02
    #define PX0H   0x01
sfr at (0xB8) IP;   // Interrupt Priority Control Low 0: IP0D PPCL PT2L PLS PT1L PX1L PT0L PX0L
sfr at (0xB8) IPL0; // Interrupt Priority Control Low 0 IP0D PPCL PT2L PLS PT1L PX1L PT0L PX0L
	sbit at (0xB8) PX0  ;
	sbit at (0xB9) PT0  ;
	sbit at (0xBA) PX1  ;
	sbit at (0xBB) PT1  ;
	sbit at (0xBC) PS   ;
	sbit at (0xBD) PT2  ; /* T2 interrupt priority bit */

	sbit at (0xBF) IP0D;
	sbit at (0xBE) PPCL; //PCA Interrupt Priority low bit.
	sbit at (0xBD) PT2L; //Timer 2 Interrupt Priority Low Bit.
	sbit at (0xBC) PLS ; //Serial Port Interrupt Priority Low Bit.
	sbit at (0xBB) PT1L; //Timer 1 Interrupt Priority Low Bit.
	sbit at (0xBA) PX1L; //External Interrupt 1 Priority Low Bit.
	sbit at (0xB9) PT0L; //Timer 0 Interrupt Priority Low Bit.
	sbit at (0xB8) PX0L; //External Interrupt 0 Priority Low Bit.

sfr at (0xB3) IPH1; // Interrupt Priority Control High 1 IP3D – PADL PCMPL – SPIH PTWL PKBH
    #define IP3D   0x80
    //#define --   0x40
    #define PADL   0x20
    #define PCMPL  0x10
    //#define --   0x08
    #define SPIH   0x04
    #define PTWL   0x02
    #define PKBH   0x01
sfr at (0xB2) IPL1; // Interrupt Priority Control Low 1 IP2D – PADH PCMPH – SPIL PTWH PKBL
    #define IP2D   0x80
    //#define --   0x40
    #define PADH   0x20
    #define PCMPH  0x10
    //#define --   0x08
    #define SPIL   0x04
    #define PTWH   0x02
    #define PKBL   0x01

// Port SFRs
sfr at (0x80) P0;   // 8-bit Port 0
	sbit at (0x80) P0_0 ;
	sbit at (0x81) P0_1 ;
	sbit at (0x82) P0_2 ;
	sbit at (0x83) P0_3 ;
	sbit at (0x84) P0_4 ;
	sbit at (0x85) P0_5 ;
	sbit at (0x86) P0_6 ;
	sbit at (0x87) P0_7 ;
sfr at (0x90) P1;   // 8-bit Port 1
	sbit at (0x90) P1_0 ;
	sbit at (0x91) P1_1 ;
	sbit at (0x92) P1_2 ;
	sbit at (0x93) P1_3 ;
	sbit at (0x94) P1_4 ;
	sbit at (0x95) P1_5 ;
	sbit at (0x96) P1_6 ;
	sbit at (0x97) P1_7 ;
sfr at (0xA0) P2;   // 8-bit Port 2
	sbit at (0xA0) P2_0 ;
	sbit at (0xA1) P2_1 ;
	sbit at (0xA2) P2_2 ;
	sbit at (0xA3) P2_3 ;
	sbit at (0xA4) P2_4 ;
	sbit at (0xA5) P2_5 ;
	sbit at (0xA6) P2_6 ;
	sbit at (0xA7) P2_7 ;
sfr at (0xB0) P3;   // 8-bit Port 3
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
sfr at (0xC0) P4;   // 8-bit Port 4
    sbit at (0xC0) P4_0 ;
    sbit at (0xC1) P4_1 ;
    sbit at (0xC2) P4_2 ;
    sbit at (0xC3) P4_3 ;
    sbit at (0xC4) P4_4 ;
    sbit at (0xC5) P4_5 ;
    sbit at (0xC6) P4_6 ;
    sbit at (0xC7) P4_7 ;
sfr at (0xE6) P0M0; // Port 0 Mode 0
sfr at (0xE7) P0M1; // Port 0 Mode 1
sfr at (0xD6) P1M0; // Port 1 Mode 0
sfr at (0xD7) P1M1; // Port 1 Mode 1
sfr at (0xCE) P2M0; // Port 2 Mode 0
sfr at (0xCF) P2M1; // Port 2 Mode 1
sfr at (0xC6) P3M0; // Port 3 Mode 0
sfr at (0xC7) P3M1; // Port 3 Mode 1
sfr at (0xBE) P4M0; // Port 4 Mode 0
sfr at (0xBF) P4M1; // Port 4 Mode 1

// Serial I/O Port SFRs
sfr at (0x98) SCON;   // Serial Control FE/SM0 SM1 SM2 REN TB8 RB8 TI RI
	sbit at (0x98) RI   ;
	sbit at (0x99) TI   ;
	sbit at (0x9A) RB8  ;
	sbit at (0x9B) TB8  ;
	sbit at (0x9C) REN  ;
	sbit at (0x9D) SM2  ;
	sbit at (0x9E) SM1  ;
	sbit at (0x9F) SM0  ;
sfr at (0x99) SBUF;   // Serial Data Buffer
sfr at (0xB9) SADEN;  // Slave Address Mask
sfr at (0xA9) SADDR;  // Slave Address
sfr at (0x9B) BDRCON; // Baud Rate Control – – – BRR TBCK RBCK SPD SRC
	#define BRR   (0x10)		//Baud Rate Run Control bit. '1'=enable
	#define TBCK  (0x08)		//Transmission Baud rate Generator Selection bit for UART
	#define RBCK  (0x04)		//Reception Baud Rate Generator Selection bit for UART
	#define SPD   (0x02)		//Baud Rate Speed Control bit for UART
	#define SRC   (0x01)		//Baud Rate Source select bit in Mode 0 for UART

sfr at (0x9A) BRL;    // Baud Rate Reload

// Timer SFRs
sfr at (0x88) TCON;   // Timer/Counter 0 and 1 Control
	sbit at (0x88) IT0  ;
	sbit at (0x89) IE0  ;
	sbit at (0x8A) IT1  ;
	sbit at (0x8B) IE1  ;
	sbit at (0x8C) TR0  ;
	sbit at (0x8D) TF0  ;
	sbit at (0x8E) TR1  ;
	sbit at (0x8F) TF1  ;
sfr at (0x89) TMOD;   // Timer/Counter 0 and 1 Modes GATE1 C/T1 M11 M01 GATE0 C/T0 M10 M00
sfr at (0x91) TCONB;  // Timer/Counter 0 and 1 Mode B
sfr at (0x8A) TL0;    // Timer/Counter 0 Low Byte
sfr at (0x8C) TH0;    // Timer/Counter 0 High Byte
sfr at (0x8B) TL1;    // Timer/Counter 1 Low Byte
sfr at (0x8D) TH1;    // Timer/Counter 1 High Byte
sfr at (0xF2) RL0;    // Timer/Counter 0 Reload Low
sfr at (0xF4) RH0;    // Timer/Counter 0 Reload High
sfr at (0xF3) RL1;    // Timer/Counter 1 Reload Low
sfr at (0xF5) RH1;    // Timer/Counter 1 Reload High
sfr at (0xA6) WDTRST; // WatchDog Timer Reset
sfr at (0xA7) WDTPRG; // WatchDog Timer Program WDTOVF SWRST WDTEN WDIDLE DISRTO WTO2 WTO1 WTO0
	#define WDTOVF 0x80
	#define SWRST  0x40
	#define WDTEN  0x20
	#define WDIDLE 0x10
	#define DISRTO 0x08
	#define WTO2   0x04
	#define WTO1   0x02
	#define WTO0   0x01
sfr at (0xC8) T2CON;  // Timer/Counter 2 control
	sbit at (0xC8) CP_RL2  ;
	sbit at (0xC9) C_T2    ;
	sbit at (0xCA) TR2     ;
	sbit at (0xCB) EXEN2   ;
	sbit at (0xCC) TCLK    ;
	sbit at (0xCD) RCLK    ;
	sbit at (0xCE) EXF2    ;
	sbit at (0xCF) TF2     ;
sfr at (0xC9) T2MOD;  // Timer/C ounter 2 Mode – – – – – – T2OE DCEN
	#define T2OE   0x02
	#define DCEN   0x01
sfr at (0xCB) RCAP2H; // Timer/Counter 2 Reload/Capture High Byte
sfr at (0xCA) RCAP2L; // Timer/Counter 2 Reload/Capture Low Byte
sfr at (0xCD) TH2;    // Timer/Counter 2 High Byte
sfr at (0xCC) TL2;    // Timer/Counter 2 Low Byte

// SPI Controller SFRs
sfr at (0xC3) SPCON; // SPI Control SPR2 SPEN SSDIS MSTR CPOL CPHA SPR1 SPR0
	#define SPR2   0x80
	#define SPEN   0x40
	#define SSDIS  0x20
	#define MSTR   0x10
	#define CPOL   0x08
	#define CPHA   0x04
	#define SPR1   0x02
	#define SPR0   0x01
sfr at (0xC4) SPSTA; // SPI Status SPIF WCOL SSERR MODF TXE DORD REMAP TBIE
	#define SPIF   0x80
	#define WCOL   0x40
	#define SSERR  0x20
	#define MODF   0x10
	#define TXE    0x08
	#define DORD   0x04
	#define REMAP  0x02
	#define TBIE   0x01
sfr at (0xC5) SPDAT; // SPI Data SPD7 SPD6 SPD5 SPD4 SPD3 SPD2 SPD1 SPD0


// TWI Controller SFRs
sfr at (0x93) SSCON; // TWI Synchronous Serial Control SSCR2 SSPE SSSTA SSSTO SSI SSAA SSCR1 SSCR0
	#define SSCR2  0x80
	#define SSPE   0x40
	#define SSSTA  0x20
	#define SSSTO  0x10
	#define SSI    0x08
	#define SSAA   0x04
	#define SSCR1  0x02
	#define SSCR0  0x01
sfr at (0x94) SSCS;  // TWI Synchronous Serial Status SSC4 SSC3 SSC2 SSC1 SSC0 0 0 0
	#define SSC4   0x80
	#define SSC3   0x40
	#define SSC2   0x20
	#define SSC1   0x10
	#define SSC0   0x08
sfr at (0x95) SSDAT; // TWI Synchronous Serial Data
sfr at (0x96) SSADR; // TWI Synchronous Serial Address SSA7 SSA6 SSA5 SSA4 SSA3 SSA2 SSA1 SSGC

// Keyboard Interface SFRs
sfr at (0x9C) KBLS;  // Keyboard Level Selector KBLS7 KBLS6 KBLS5 KBLS4 KBLS3 KBLS2 KBLS1 KBLS0
	#define KBLS7  0x80
	#define KBLS6  0x40
	#define KBLS5  0x20
	#define KBLS4  0x10
	#define KBLS3  0x08
	#define KBLS2  0x04
	#define KBLS1  0x02
	#define KBLS0  0x01
sfr at (0x9D) KBE;   // Keyboard Input Enable KBE7 KBE6 KBE5 KBE4 KBE3 KBE2 KBE1 KBE0
	#define KBE7  0x80
	#define KBE6  0x40
	#define KBE5  0x20
	#define KBE4  0x10
	#define KBE3  0x08
	#define KBE2  0x04
	#define KBE1  0x02
	#define KBE0  0x01
sfr at (0x9E) KBF;   // Keyboard Flag Register KBF7 KBF6 KBF5 KBF4 KBF3 KBF2 KBF1 KBF0
	#define KBF7  0x80
	#define KBF6  0x40
	#define KBF5  0x20
	#define KBF4  0x10
	#define KBF3  0x08
	#define KBF2  0x04
	#define KBF1  0x02
	#define KBF0  0x01
sfr at (0x9F) KBMOD; // Keyboard Mode Register KBM7 KBM6 KBM5 KBM4 KBM3 KBM2 KBM1 KBM0
	#define KBM7  0x80
	#define KBM6  0x40
	#define KBM5  0x20
	#define KBM4  0x10
	#define KBM3  0x08
	#define KBM2  0x04
	#define KBM1  0x02
	#define KBM0  0x01

// Flash/EEPROM Memory SFR
sfr at (0x92) BMSEL; // Bank Mode Select Register – – – – – – – FBS
	//#define -  0x80
	//#define -  0x40
	//#define -  0x20
	//#define -  0x10
	//#define -  0x08
	//#define -  0x04
	//#define -  0x02
	#define FBS  0x01
sfr at (0xD2) FCON;  // Flash Control Register FPL3 FPL2 FPL1 FPL0 FPS FMOD1 FMOD0 FBUSY
	#define FPL3   0x80
	#define FPL2   0x40
	#define FPL1   0x20
	#define FPL0   0x10
	#define FPS    0x08
	#define FMOD1  0x04
	#define FMOD0  0x02
	#define FBUSY  0x01
sfr at (0xD2) EECON; // EEPROM Control Register FOUT AERS LDPG FLGE INHIBIT ERR EEE EEBUSY
	#define FOUT    0x80
	#define AERS    0x40
	#define LDPG    0x20
	#define FLGE    0x10
	#define INHIBIT 0x08
	#define ERR     0x04
	#define EEE     0x02
	#define EEBUSY  0x01

// Analog Comparator SFRs
sfr at (0xA3) ACSRA; // Comparator A Control Register CSA1 CSA0 CONA CFA CENA CMA2 CMA1 CMA0
	#define CSA1    0x80
	#define CSA0    0x40
	#define CONA    0x20
	#define CFA     0x10
	#define CENA    0x08
	#define CMA2    0x04
	#define CMA1    0x02
	#define CMA0    0x01
sfr at (0xAB) ACSRB; // Comparator B Control Register CSB1 CSB0 CONB CFB CENB CMB2 CMB1 CMB0
	#define CSB1    0x80
	#define CSB0    0x40
	#define CONB    0x20
	#define CFB     0x10
	#define CENB    0x08
	#define CMB2    0x04
	#define CMB1    0x02
	#define CMB0    0x01
sfr at (0xBD) AREF;  // Comparator Reference Register CMPB CMPA RFB1 RFB0 CCS1 CCS0 RFA1 RFA0
	#define CMPB    0x80
	#define CMPA    0x40
	#define RFB1    0x20
	#define RFB0    0x10
	#define CCS1    0x08
	#define CCS0    0x04
	#define RFA1    0x02
	#define RFA0    0x01

// ADC Controller SFRs
sfr at (0xA4) DADC; // DAC/ADC Control Register ADIF GO/BSY DAC ADCE LADJ ACK2 ACK1 ACK0
	#define ADIF   0x80
	#define GO_BSY 0x40
	#define DAC    0x20
	#define ADCE   0x10
	#define LADJ   0x08
	#define ACK2   0x04
	#define ACK1   0x02
	#define ACK0   0x01
sfr at (0xA5) DADI; // DAC/ADC Input Register ACON IREF TRG1 TRG0 DIFF ACS2 ACS1 ACS0
	#define ACON 0x80
	#define IREF 0x40
	#define TRG1 0x20
	#define TRG0 0x10
	#define DIFF 0x08
	#define ACS2 0x04
	#define ACS1 0x02
	#define ACS0 0x01
sfr at (0xAC) DADL; // DAC/ADC Data Low Register
sfr at (0xAD) DADH; // DAC/ADC Data High Register

// PCA SFRs
sfr at (0xD8) CCON;   // PCA Timer/Counter Control CF CR – CCF4 CCF3 CCF2 CCF1 CCF0
	sbit at (0xDF) CF;	 //PCA Counter overflow flag.
	sbit at (0xDE) CR ;  //PCA Counter Run Control Bit. 1=counter on.  0=counter off.
	sbit at (0xDC) CCF4; //PCA Module 4 Interrupt Flag.
	sbit at (0xDB) CCF3; //PCA Module 3 Interrupt Flag.
	sbit at (0xDA) CCF2; //PCA Module 2 Interrupt Flag.
	sbit at (0xD9) CCF1; //PCA Module 1 Interrupt Flag.
	sbit at (0xD8) CCF0; //PCA Module 0 Interrupt Flag.
sfr at (0xD9) CMOD;   // PCA Timer/Counter Mode CIDL WDTE – – – CPS1 CPS0 ECF
	#define CIDL 0x80
	#define WDTE 0x40
	//#define -  0x20
	//#define -  0x10
	//#define -  0x08
	#define CPS1 0x04
	#define CPS0 0x02
	#define ECF  0x01
sfr at (0xE9) CL;     // PCA Timer/Counter Low Byte
sfr at (0xF9) CH;     // PCA Timer/Counter High Byte
sfr at (0xDA) CCAPM0; // PCA Timer/Counter Mode 0 – ECOM0 CAPP0 CAPN0 MAT0 TOG0 PWM0 ECCF0
sfr at (0xDB) CCAPM1; // PCA Timer/Counter Mode 1 – ECOM1 CAPP1 CAPN1 MAT1 TOG1 PWM1 ECCF1
sfr at (0xDC) CCAPM2; // PCA Timer/Counter Mode 2 – ECOM2 CAPP2 CAPN2 MAT2 TOG2 PWM2 ECCF2
sfr at (0xDD) CCAPM3; // PCA Timer/Counter Mode 3 – ECOM3 CAPP3 CAPN3 MAT3 TOG3 PWM3 ECCF3
sfr at (0xDE) CCAPM4; // PCA Timer/Counter Mode 4 – ECOM4 CAPP4 CAPN4 MAT4 TOG4 PWM4 ECCF4
	#define ECOM 0x40
	#define CAPP 0x20
	#define CAPN 0x10
	#define MAT  0x08
	#define TOG  0x04
	#define PWM  0x02
	#define ECCF 0x01
sfr at (0xFA) CCAP0H; // PCA Compare Capture Module 0 High
sfr at (0xFB) CCAP1H; // PCA Compare Capture Module 1 High
sfr at (0xFC) CCAP2H; // PCA Compare Capture Module 2 High
sfr at (0xFD) CCAP3H; // PCA Compare Capture Module 3 High
sfr at (0xFE) CCAP4H; // PCA Compare Capture Module 4 High
sfr at (0xEA) CCAP0L; // PCA Compare Capture Module 0 Low
sfr at (0xEB) CCAP1L; // PCA Compare Capture Module 1 Low
sfr at (0xEC) CCAP2L; // PCA Compare Capture Module 2 Low
sfr at (0xED) CCAP3L; // PCA Compare Capture Module 3 Low
sfr at (0xEE) CCAP4L; // PCA Compare Capture Module 4 Low

#endif
