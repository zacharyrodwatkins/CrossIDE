/*-------------------------------------------------------------------------
   Register Declarations for the Cyrod CRD89C51AD1T Processor

   Written By -  Jesus Calvino-Fraga / jesusc at ece.ubc.ca (February 2012)
   (Based on Cyrod Technologies Inc. CRD89C51AD1T Data Sheet Rev 1.02
   http://www.cyrod.com/PDF/CRD89C51AD1T_V1.02.pdf)

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

#ifndef __CRD89C51AD1T_H__
#define __CRD89C51AD1T_H__

sfr at (0x80) P0 ;  // Port 0
	sbit at (0x80) P0_0 ;
	sbit at (0x81) P0_1 ;
	sbit at (0x82) P0_2 ;
	sbit at (0x83) P0_3 ;
	sbit at (0x84) P0_4 ;
	sbit at (0x85) P0_5 ;
	sbit at (0x86) P0_6 ;
	sbit at (0x87) P0_7 ;
sfr at (0x81) SP ;    // Stack Pointer
sfr at (0x82) DPL ;   // Data Pointer 0 low byte
sfr at (0x83) DPH ;   // Data Pointer 0 high byte
sfr at (0x84) DPL1 ;  // Data Pointer 1 low byte
sfr at (0x85) DPH1 ;  // Data Pointer 1 high byte
sfr at (0x86) RCON ;  // Internal RAM control register
sfr at (0x87) PCON ;  // Power Control
sfr at (0x88) TCON ;  // Timer/Counter Control
	sbit at (0x88) IT0  ;
	sbit at (0x89) IE0  ;
	sbit at (0x8A) IT1  ;
	sbit at (0x8B) IE1  ;
	sbit at (0x8C) TR0  ;
	sbit at (0x8D) TF0  ;
	sbit at (0x8E) TR1  ;
	sbit at (0x8F) TF1  ;
sfr at (0x89) TMOD ;  // Timer Mode Control
sfr at (0x8A) TL0 ;   // Timer 0, low byte
sfr at (0x8B) TL1 ;   // Timer 1, low byte
sfr at (0x8C) TH0 ;   // Timer 0, high byte
sfr at (0x8D) TH1 ;   // Timer 1, high byte
sfr at (0x8F) IFCON ; // Interface control register
sfr at (0x90) P1 ;    // Port 1
	sbit at (0x90) P1_0 ;
	sbit at (0x91) P1_1 ;
	sbit at (0x92) P1_2 ;
	sbit at (0x93) P1_3 ;
	sbit at (0x94) P1_4 ;
	sbit at (0x95) P1_5 ;
	sbit at (0x96) P1_6 ;
	sbit at (0x97) P1_7 ;
sfr at (0x91) AUX ;    // AUX
sfr at (0x92) AUX2 ;   // AUX2
sfr at (0x93) KBLS ;   // Keyboard level selector Register
sfr at (0x94) KBE ;    // Keyboard input enable Register
sfr at (0x95) KBF ;    // Keyboard interrupt flag Register
sfr at (0x96) KBD ;    // Keyboard interface De-bounce control register
sfr at (0x97) IRCON2 ; // Interrupt Request Control Register 2
sfr at (0x98) SCON ;   // Serial Port 0, Control Register (Alternate name)
sfr at (0x98) S0CON ;  // Serial Port 0, Control Register
	sbit at (0x98) RI   ;
	sbit at (0x99) TI   ;
	sbit at (0x9A) RB8  ;
	sbit at (0x9B) TB8  ;
	sbit at (0x9C) REN  ;
	sbit at (0x9D) SM2  ;
	sbit at (0x9E) SM1  ;
	sbit at (0x9F) SM0  ;
sfr at (0x99) SBUF ;    // Serial Port 0, Data Buffer (Alternate name)
sfr at (0x99) S0BUF ;   // Serial Port 0, Data Buffer
sfr at (0x9A) IEN2 ;    // Interrupt Enable Register 2
sfr at (0x9B) S1CON ;   // Serial Port 1, Control Register
sfr at (0x9C) S1BUF ;   // Serial Port 1, Data Buffer
sfr at (0x9D) S1RELL ;  // Serial Port 1, Reload Register, low byte
sfr at (0x9E) RTCADDR ; // RTC Addr Register
sfr at (0x9F) RTCDATA ; // RTC Data Register
sfr at (0xA0) P2 ;  // Port 2
	sbit at (0xA0) P2_0 ;
	sbit at (0xA1) P2_1 ;
	sbit at (0xA2) P2_2 ;
	sbit at (0xA3) P2_3 ;
	sbit at (0xA4) P2_4 ;
	sbit at (0xA5) P2_5 ;
	sbit at (0xA6) P2_6 ;
	sbit at (0xA7) P2_7 ;
sfr at (0xA8) IEN0 ;  // Interrupt Enable Register 0 EA – ET2 ES0 ET1 EX1 ET0 EX0 00h
	sbit at (0xA8) EX0  ;
	sbit at (0xA9) ET0  ;
	sbit at (0xAA) EX1  ;
	sbit at (0xAB) ET1  ;
	sbit at (0xAC) ES   ; // For backward compatibility
	sbit at (0xAC) ES0  ;
	sbit at (0xAD) ET2  ;
	sbit at (0xAF) EA   ;
sfr at (0xA9) IP0 ;    // Interrupt Priority Register 0
sfr at (0xAA) S0RELL ; // Serial Port 0, Reload Register, low byte
sfr at (0xAB) ADCC1 ;  // ADC Control 1 Register
sfr at (0xAC) ADCC2 ;  // ADC Control 2 Register
sfr at (0xAD) ADCDH ;  // ADC data high byte
sfr at (0xAE) ADCDL ;  // ADC data low byte
sfr at (0xAF) ADCCS ;  // ADC clock select
sfr at (0xB0) P3 ;     // Port 3
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
sfr at (0xB1) PWMD2H ;  // PWM channel 2 data high byte
sfr at (0xB2) PWMD2L ;  // PWM channel 2 data low byte
sfr at (0xB3) PWMD3H ;  // PWM channel 3 data high byte
sfr at (0xB4) PWMD3L ;  // PWM channel 3 data low byte
sfr at (0xB5) PWMC ;    // PWM control register
sfr at (0xB6) WDTC ;    // Watchdog timer control register
sfr at (0xB7) WDTK ;    // Watchdog timer refresh key.
sfr at (0xB8) IEN1 ;    // Interrupt Enable Register 1 EXEN2 - IEIIC IELVI IEKBI IEADC IESPI IEPWM
	sbit at (0xB8) IEPWM  ;
	sbit at (0xB9) IESPI  ;
	sbit at (0xBA) IEADC  ;
	sbit at (0xBB) IEKBI  ;
	sbit at (0xBC) IELVI  ;
	sbit at (0xBD) IEIIC  ;
	sbit at (0xBF) EXEN2  ;
sfr at (0xB9) IP1 ;     // Interrupt Priority Register 1
sfr at (0xBA) S0RELH ;  // Serial Port 0, Reload Register, high byte
sfr at (0xBB) S1RELH ;  // Serial Port 1, Reload Register, high byte
sfr at (0xBC) PWMD0H ;  // PWM channel 0 data high byte
sfr at (0xBD) PWMD0L ;  // PWM channel 0 data low byte
sfr at (0xBE) PWMD1H ;  // PWM channel 1 data high byte
sfr at (0xBF) PWMD1L ;  // PWM channel 1 data low byte
sfr at (0xC0) IRCON ;   // Interrupt Request Control Register
	sbit at (0xC7) EXF2;  // Timer 2 external reloads flag. Must be cleared by software.
	sbit at (0xC6) TF2;   // Timer 2 overflows flag. Must be cleared by software.
	sbit at (0xC5) IICIF; // IIC interrupt flag.
	sbit at (0xC4) LVIIF; // LVI interrupt flag.
	sbit at (0xC3) KBIIF; // KBI interrupt flag.
	sbit at (0xC2) ADCIF; // A/D converter end interrupt flag.
	sbit at (0xC1) SPIIF; // SPI interrupt flag.
	sbit at (0xC0) PWMIF; // PWM interrupt flag. Must be cleared by software
sfr at (0xC1) CCEN ;  // Compare/Capture Enable Register
sfr at (0xC2) CCL1 ;  // Compare/Capture Register 1, low byte
sfr at (0xC3) CCH1 ;  // Compare/Capture Register 1, high byte
sfr at (0xC4) CCL2 ;  // Compare/Capture Register 2, low byte
sfr at (0xC5) CCH2 ;  // Compare/Capture Register 2, high byte
sfr at (0xC6) CCL3 ;  // Compare/Capture Register 3, low byte
sfr at (0xC7) CCH3 ;  // Compare/Capture Register 3, high byte
sfr at (0xC8) T2CON ; // Timer 2 Control T2PS[2:0] T2R[1:0] T2CM T2I[1:0]
	sbit at (0xCF) T2PS2; // Prescaler select bit 2
	sbit at (0xCE) T2PS1; // Prescaler select bit 1
	sbit at (0xCD) T2PS0; // Prescaler select bit 0
	sbit at (0xCC) T2R1;  // Timer 2 reload mode selection bit 1
	sbit at (0xCB) T2R0;  // Timer 2 reload mode selection bit 0
	sbit at (0xCA) T2CM;  // Timer 2 Compare mode selection
	sbit at (0xC9) T2I1;  //  Timer 2 input selection bit 1
	sbit at (0xC8) T2I0;  //  Timer 2 input selection bit 1
sfr at (0xC9) CCCON ;   // Compare/Capture Control
sfr at (0xCA) CRCL ;    // Compare/Reload/Capture Register, low byte
sfr at (0xCB) CRCH ;    // Compare/Reload/Capture Register, high byte
sfr at (0xCC) TL2 ;     // Timer 2, low byte
sfr at (0xCD) TH2 ;     // Timer 2, high byte
sfr at (0xCE) PWMMDH ;  // PWM Max Data Register, high byte.
sfr at (0xCF) PWMMDL ;  // PWM Max Data Register, low byte.
sfr at (0xD0) PSW ;     // Program Status Word
	sbit at (0xD0) P    ;
	sbit at (0xD1) F1   ;
	sbit at (0xD2) OV   ;
	sbit at (0xD3) RS0  ;
	sbit at (0xD4) RS1  ;
	sbit at (0xD5) F0   ;
	sbit at (0xD6) AC   ;
	sbit at (0xD7) CY   ;
sfr at (0xD1) CCEN2 ; // Compare/Capture Enable 2 register
sfr at (0xD2) P0M0 ;  // Port 0 output mode 0
sfr at (0xD3) P0M1 ;  // Port 0 output mode 1
sfr at (0xD4) P1M0 ;  // Port 1 output mode 0
sfr at (0xD5) P1M1 ;  // Port 1 output mode 1
sfr at (0xD6) P2M0 ;  // Port 2 output mode 0
sfr at (0xD7) P2M1 ;  // Port 2 output mode 1
sfr at (0xD8) P5 ;    // Port 5
	sbit at (0xD8) P5_0 ;
	sbit at (0xD9) P5_1 ;
	sbit at (0xDA) P5_2 ;
	sbit at (0xDB) P5_3 ;
	sbit at (0xDC) P5_4 ;
	sbit at (0xDD) P5_5 ;
	sbit at (0xDE) P5_6 ;
	sbit at (0xDF) P5_7 ;
sfr at (0xDA) P3M0 ;  // Port 3 output mode 0
sfr at (0xDB) P3M1 ;  // Port 3 output mode 1
sfr at (0xDC) P4M0 ;  // Port 4 output mode 0
sfr at (0xDD) P4M1 ;  // Port 4 output mode 1
sfr at (0xDE) P5M0 ;  // Port 5 output mode 0
sfr at (0xDF) P5M1 ;  // Port 5 output mode 1
sfr at (0xE0) ACC ;   // Accumulator
	sbit at (0xE0) ACC_0 ;
	sbit at (0xE1) ACC_1 ;
	sbit at (0xE2) ACC_2 ;
	sbit at (0xE3) ACC_3 ;
	sbit at (0xE4) ACC_4 ;
	sbit at (0xE5) ACC_5 ;
	sbit at (0xE6) ACC_6 ;
	sbit at (0xE7) ACC_7 ;
sfr at (0xE1) ISPFAH ; // ISP Flash Address-High register
sfr at (0xE2) ISPFAL ; // ISP Flash Address-Low register
sfr at (0xE3) ISPFD ;  // ISP Flash Data register
sfr at (0xE4) ISPFC ;  // ISP Flash control register
sfr at (0xE6) LVC ;    // Low voltage control register
sfr at (0xE7) SWRES ;  // Software Reset register
sfr at (0xE8) P4 ;     // Port 4
    sbit at (0xE8) P4_0 ;
    sbit at (0xE9) P4_1 ;
    sbit at (0xEA) P4_2 ;
    sbit at (0xEB) P4_3 ;
    sbit at (0xEC) P4_4 ;
    sbit at (0xED) P4_5 ;
    sbit at (0xEE) P4_6 ;
    sbit at (0xEF) P4_7 ;
sfr at (0xE9) MD0 ;   // Multiplication/Division Register 0
sfr at (0xEA) MD1 ;   // Multiplication/Division Register 1
sfr at (0xEB) MD2 ;   // Multiplication/Division Register 2
sfr at (0xEC) MD3 ;   // Multiplication/Division Register 3
sfr at (0xED) MD4 ;   // Multiplication/Division Register 4
sfr at (0xEE) MD5 ;   // Multiplication/Division Register 5
sfr at (0xEF) ARCON ; // Arithmetic Control Register
sfr at (0xF0) B ;     // B Register
	sbit at (0xF0) B_0 ;
	sbit at (0xF1) B_1 ;
	sbit at (0xF2) B_2 ;
	sbit at (0xF3) B_3 ;
	sbit at (0xF4) B_4 ;
	sbit at (0xF5) B_5 ;
	sbit at (0xF6) B_6 ;
	sbit at (0xF7) B_7 ;
sfr at (0xF1) SPIC1 ;  // SPI control register 1
sfr at (0xF2) SPIC2 ;  // SPI control register 2
sfr at (0xF3) SPITXD ; // SPI transmit data buffer
sfr at (0xF4) SPIRXD ; // SPI receive data buffer
sfr at (0xF5) SPIS ;   // SPI status register
sfr at (0xF6) OpPin ;  // Op/Comparator Pin Select register
sfr at (0xF7) TAKEY ;  // Time Access Key register
sfr at (0xF8) IICS ;   // IIC status register MStart RxIF TxIF RDR TDR RxAK TxAK RW
	sbit at (0xF8) MStart;
	sbit at (0xF9) RxIF;
	sbit at (0xFA) TxIF;
	sbit at (0xFB) RDR;
	sbit at (0xFC) TDR;
	sbit at (0xFD) RxAK;
	sbit at (0xFE) TxAK;
	sbit at (0xFF) RW;
sfr at (0xF9) IICCTL ;  // IIC control register
sfr at (0xFA) IICA1 ;   // IIC channel 1 Address 1 register
sfr at (0xFB) IICA2 ;   // IIC channel 1 Address 2 register
sfr at (0xFC) IICRWD ;  // IIC channel 1 Read / Write Data buffer
sfr at (0xFD) IICS2 ;   // IIC status2 register
sfr at (0xFE) Cmp0CON ; // Comparator_0 Control register
sfr at (0xFF) Cmp1CON ; // Comparator_1 Control register

#endif  //_89C51AD1T_H__
