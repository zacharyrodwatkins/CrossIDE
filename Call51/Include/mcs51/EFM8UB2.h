// -----------------------------------------------------------------------------
// EFM8UB2.h: Register definitions for Silabs EFM8UB2 devices.
// Taken from "Table 3.1. Special Function Registers by Address" and
// "Table 3.2. Special Function Registers by Name" 
// of the EFM8UB2 datasheet
// Rev. 0.2.
//
// Copyright (C) 2015 - Jesus Calvino-Fraga jesuscf@gmail.com
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
//
// -----------------------------------------------------------------------------

#ifndef EFM8UB2_H
#define EFM8UB2_H

// Interrupt Vector Numbers

#define INTERRUPT_INT0        0  // External Interrupt 0
#define INTERRUPT_TIMER0      1  // Timer 0 Overflow
#define INTERRUPT_INT1        2  // External Interrupt 1
#define INTERRUPT_TIMER1      3  // Timer 1 Overflow
#define INTERRUPT_UART0       4  // UART0
#define INTERRUPT_TIMER2      5  // Timer 2 Overflow
#define INTERRUPT_SPI0        6  // SPI0
#define INTERRUPT_SMBUS0      7  // SMBus0 Interface
#define INTERRUPT_USB0        8  // SMBus0 Interface
#define INTERRUPT_ADC0_WINDOW 9  // ADC0 Window Comparison
#define INTERRUPT_ADC0_EOC    10 // ADC0 End Of Conversion
#define INTERRUPT_PCA0        11 // PCA0 Peripheral
#define INTERRUPT_COMPARATOR0 12 // Comparator 0 Comparison
#define INTERRUPT_COMPARATOR1 13 // Comparator 1 Comparison
#define INTERRUPT_TIMER3      14 // Timer 3 Overflow
#define INTERRUPT_VBUS        15 // VBus Interrupt
#define INTERRUPT_UART1       16 // UART1
#define INTERRUPT_SMBUS1      18 // SMBus1 Interface
#define INTERRUPT_TIMER4      19 // Timer 4 Overflow
#define INTERRUPT_TIMER5      20 // Timer 5 Overflow

// Special Function Registers and bits

__sfr __at (0x80) P0;      // Port 0 Latch 
	__sbit __at (0x80) P0_0;
	__sbit __at (0x81) P0_1;
	__sbit __at (0x82) P0_2;
	__sbit __at (0x83) P0_3;
	__sbit __at (0x84) P0_4;
	__sbit __at (0x85) P0_5;
	__sbit __at (0x86) P0_6;
	__sbit __at (0x87) P0_7;
__sfr __at (0x81) SP;      // Stack Pointer 
__sfr __at (0x82) DPL;     // Data Pointer Low 
__sfr __at (0x83) DPH;     // Data Pointer High 
__sfr __at (0x84) EMI0TC;  // External Memory Interface Timing 
__sfr __at (0x85) EMI0CF;  // External Memory Interface Configuration 
__sfr __at (0x86) OSCLCN;  // Internal Low-Frequency Oscillator Control 
__sfr __at (0x87) PCON;    // Power Control (alternate name)
__sfr __at (0x87) PCON0;   // Power Control 
__sfr __at (0x88) TCON;    // Timer/Counter Control 
	__sbit __at (0x8F) TF1; // Timer 1 Overflow Flag
	__sbit __at (0x8E) TR1; // Timer 1 On/Off Control
	__sbit __at (0x8D) TF0; // Timer 0 Overflow Flag
	__sbit __at (0x8C) TR0; // Timer 0 On/Off Control
	__sbit __at (0x8B) IE1; // Ext. Interrupt 1 Edge Flag
	__sbit __at (0x8A) IT1; // Ext. Interrupt 1 Type
	__sbit __at (0x89) IE0; // Ext. Interrupt 0 Edge Flag
	__sbit __at (0x88) IT0; // Ext. Interrupt 0 Type
__sfr __at (0x89) TMOD;    // Timer/Counter Mode 
__sfr __at (0x8A) TL0;     // Timer/Counter 0 Low 
__sfr __at (0x8B) TL1;     // Timer/Counter 1 Low 
__sfr __at (0x8C) TH0;     // Timer/Counter 0 High 
__sfr __at (0x8D) TH1;     // Timer/Counter 1 High 
__sfr __at (0x8E) CKCON0;  // Clock Control 
__sfr __at (0x8E) CKCON;   // Clock Control (alternate name)
__sfr __at (0x8F) PSCTL;   // Program Store R/W Control 
__sfr __at (0x90) P1;      // Port 1 Latch 
	__sbit __at (0x90) P1_0;
	__sbit __at (0x91) P1_1;
	__sbit __at (0x92) P1_2;
	__sbit __at (0x93) P1_3;
	__sbit __at (0x94) P1_4;
	__sbit __at (0x95) P1_5;
	__sbit __at (0x96) P1_6;
	__sbit __at (0x97) P1_7;
__sfr __at (0x91) TMR3CN;  // Page: 0 Desc: Timer/Counter 3 Control
__sfr __at (0x91) TMR3CN0; // Page: 0 Desc: Timer/Counter 3 Control
	#define TF3H     0x80  // Timer 3 High Byte Overflow Flag.
	#define TF3L     0x40  // Timer 3 Low Byte Overflow Flag.
	#define TF3LEN   0x20  // Timer 3 Low Byte Interrupt Enable.
	#define TF3CEN   0x10  // Timer 3 Low-Frequency Oscillator Capture Enable.
	#define T3SPLIT  0x08  // Timer 3 Split Mode Enable.
	#define TR3      0x04  // Timer 3 Run Control.
	#define T3CSS    0x02  // Timer 3 Capture Source Select.
	#define T3XCLK   0x01  // Timer 3 External Clock Select.
__sfr __at (0x91) TMR4CN;  // Page: F Desc: Timer/Counter 4 Control
__sfr __at (0x91) TMR4CN0; // Page: F Desc: Timer/Counter 4 Control
	#define TF4H     0x80  // Timer 4 High Byte Overflow Flag.
	#define TF4L     0x40  // Timer 4 Low Byte Overflow Flag.
	#define TF4LEN   0x20  // Timer 4 Low Byte Interrupt Enable.
	#define TMR4CN_4 0x10  // Unused Read = 0b; Write = don’t care.
	#define T4SPLIT  0x08  // Timer 4 Split Mode Enable.
	#define TR4      0x04  // Timer 4 Run Control.
	#define TMR4CN_1 0x02  // Unused Read = 0b; Write = don’t care.
	#define T4XCLK   0x01  // Timer 4 External Clock Select.
__sfr __at (0x92) TMR3RLL; // Page: 0 Desc: Timer/Counter 3 Reload Low 
__sfr __at (0x92) TMR4RLL; // Page: F Desc: Timer/Counter 4 Reload Low 
__sfr __at (0x93) TMR3RLH; // Page: 0 Desc: Timer/Counter 3 Reload High 
__sfr __at (0x93) TMR4RLH; // Page: F Desc: Timer/Counter 4 Reload High 
__sfr __at (0x94) TMR3L;   // Page: 0 Desc: Timer/Counter 3 Low 
__sfr __at (0x94) TMR4L;   // Page: F Desc: Timer/Counter 4 Low 
__sfr __at (0x95) TMR3H;   // Page: 0 Desc: Timer/Counter 3 High 
__sfr __at (0x95) TMR4H;   // Page: F Desc: Timer/Counter 4 High 
__sfr __at (0x96) USB0ADR; // USB0 Indirect Address Register 
__sfr __at (0x97) USB0DAT; // USB0 Data Register 
__sfr __at (0x98) SCON;    // UART0 Control 
__sfr __at (0x98) SCON0;   // UART0 Control 
	__sbit __at (0x9F) S0MODE; // Serial Port 0 Operation Mode
	__sbit __at (0x9E) SCON0_6;
	__sbit __at (0x9D) MCE0; // Multiprocessor Communication Enable
	__sbit __at (0x9C) REN0; // UART0 RX Enable
	__sbit __at (0x9B) TB80; // Ninth Transmission Bit
	__sbit __at (0x9A) RB80; // Ninth Receive Bit
	__sbit __at (0x99) TI0; // UART0 TX Interrupt Flag
	__sbit __at (0x98) RI0; // UART0 RX Interrupt Flag
	// For compatibility purposes
	__sbit __at (0x9E) SCON_6;
	__sbit __at (0x9D) MCE; // Multiprocessor Communication Enable
	__sbit __at (0x9C) REN; // UART0 RX Enable
	__sbit __at (0x9B) TB8; // Ninth Transmission Bit
	__sbit __at (0x9A) RB8; // Ninth Receive Bit
	__sbit __at (0x99) TI; // UART0 TX Interrupt Flag
	__sbit __at (0x98) RI; // UART0 RX Interrupt Flag
__sfr __at (0x99) SBUF;    // UART0 Data Buffer 
__sfr __at (0x99) SBUF0;   // UART0 Data Buffer 
__sfr __at (0x9A) CMP1CN0;  // Comparator1 Control 
__sfr __at (0x9B) CMP0CN0;  // Comparator0 Control 
__sfr __at (0x9C) CMP1MD;  // Comparator1 Mode Selection 
__sfr __at (0x9D) CMP0MD;  // Comparator0 Mode Selection 
__sfr __at (0x9E) CMP1MX;  // Comparator1 MUX Selection 
__sfr __at (0x9F) CMP0MX;  // Comparator0 MUX Selection 
__sfr __at (0xA0) P2;      // Port 2 Latch 
	__sbit __at (0xA0) P2_0;
	__sbit __at (0xA1) P2_1;
	__sbit __at (0xA2) P2_2;
	__sbit __at (0xA3) P2_3;
	__sbit __at (0xA4) P2_4;
	__sbit __at (0xA5) P2_5;
	__sbit __at (0xA6) P2_6;
	__sbit __at (0xA7) P2_7;
__sfr __at (0xA1) SPI0CFG; // SPI Configuration 
__sfr __at (0xA2) SPI0CKR; // SPI Clock Rate Control 
__sfr __at (0xA3) SPI0DAT; // SPI Data 
__sfr __at (0xA4) P0MDOUT; // Port 0 Output Mode Configuration 
__sfr __at (0xA5) P1MDOUT; // Port 1 Output Mode Configuration 
__sfr __at (0xA6) P2MDOUT; // Port 2 Output Mode Configuration 
__sfr __at (0xA7) P3MDOUT; // Port 3 Output Mode Configuration 
__sfr __at (0xA8) IE;      // Interrupt Enable 
	__sbit __at (0xAF) EA; // Global Interrupt Enable
	__sbit __at (0xAE) ESPI0; // SPI0 Interrupt Enable
	__sbit __at (0xAD) ET2; // Timer 2 Interrupt Enable
	__sbit __at (0xAC) ES0; // UART0 Interrupt Enable
	__sbit __at (0xAB) ET1; // Timer 1 Interrupt Enable
	__sbit __at (0xAA) EX1; // External Interrupt 1 Enable
	__sbit __at (0xA9) ET0; // Timer 0 Interrupt Enable
	__sbit __at (0xA8) EX0; // External Interrupt 0 Enable
__sfr __at (0xA9) CLKSEL;  // Clock Select 
__sfr __at (0xAA) EMI0CN;  // External Memory Interface Control
__sfr __at (0xAA) _XPAGE;  // External Memory Interface Control
__sfr __at (0xAC) SBCON1;  // UART1 Baud Rate Generator Control 
__sfr __at (0xAE) P4MDOUT; // Port 4 Output Mode Configuration 
__sfr __at (0xAF) PFE0CN;  // Prefetch Engine Control 
__sfr __at (0xB0) P3;      // Port 3 Latch
	__sbit __at (0xB0) P3_0;
	__sbit __at (0xB1) P3_1;
	__sbit __at (0xB2) P3_2;
	__sbit __at (0xB3) P3_3;
	__sbit __at (0xB4) P3_4;
	__sbit __at (0xB5) P3_5;
	__sbit __at (0xB6) P3_6;
	__sbit __at (0xB7) P3_7;
__sfr __at (0xB1) OSCX0CN; // External Oscillator Control 
__sfr __at (0xB2) HFO0CN;  // Internal Oscillator Control 
__sfr __at (0xB3) HFO0CAL; // Internal Oscillator Calibration 
__sfr __at (0xB2) OSCICN;  // Internal Oscillator Control (for compatibility with older code) 
__sfr __at (0xB3) OSCICL;  // Internal Oscillator Calibration  (for compatibility with older code)
__sfr __at (0xB4) SBRLL1;  // UART1 Baud Rate Generator Low 
__sfr __at (0xB5) SBRLH1;  // UART1 Baud Rate Generator High 
__sfr __at (0xB6) FLSCL;   // Flash Scale 
__sfr __at (0xB7) FLKEY;   // Flash Lock and Key 
__sfr __at (0xB8) IP;      // Interrupt Priority 
	__sbit __at (0xBF) IP_7;  // Bit 7 unused
	__sbit __at (0xBE) PSPI0; // SPI0 Interrupt Priority
	__sbit __at (0xBD) PT2;   // Timer 2 Priority
	__sbit __at (0xBC) PS0;   // UART0 Priority
	__sbit __at (0xBB) PT1;   // Timer 1 Priority
	__sbit __at (0xBA) PX1;   // External Interrupt 1 Priority
	__sbit __at (0xB9) PT0;   // Timer 0 Priority
	__sbit __at (0xB8) PX0;   // External Interrupt 0 Priority
__sfr __at (0xB9) SMBTC;   // Page: F Desc: SMBus0/1 Timing Control 
__sfr __at (0xBA) AMX0N;   // AMUX0 Negative Channel Select 
__sfr __at (0xBB) AMX0P;   // AMUX0 Positive Channel Select 
__sfr __at (0xBC) ADC0CF;  // ADC0 Configuration 
__sfr __at (0xBD) ADC0L;   // ADC0 Low 
__sfr __at (0xBE) ADC0H;   // ADC0 High 
__sfr __at (0xBF) SFRPAGE; // SFR Page Select 
__sfr __at (0xC0) SMB0CN;  // Page: 0 Desc: SMBus0 Control 
	__sbit __at (0xC7) MASTER0; // SMBus0 Master/Slave Indicator
	__sbit __at (0xC6) TXMODE0; // SMBus0 Transmit Mode Indicator
	__sbit __at (0xC5) STA0;    // SMBus0 Start Flag
	__sbit __at (0xC4) STO0;    // SMBus0 Stop Flag
	__sbit __at (0xC3) ACKRQ0;  // SMBus0 Acknowledge Request
	__sbit __at (0xC2) ARBLOST0;// SMBus0 Arbitration Lost Indicator
	__sbit __at (0xC1) ACK0;    // SMBus0 Acknowledge
	__sbit __at (0xC0) SI0;     // SMBus0 Interrupt Flag
__sfr __at (0xC0) SMB1CN;  // Page: F Desc: SMBus1 Control 
	__sbit __at (0xC7) MASTER1; // SMBus1 Master/Slave Indicator
	__sbit __at (0xC6) TXMODE1; // SMBus1 Transmit Mode Indicator
	__sbit __at (0xC5) STA1;    // SMBus1 Start Flag
	__sbit __at (0xC4) STO1;    // SMBus1 Stop Flag
	__sbit __at (0xC3) ACKRQ1;  // SMBus1 Acknowledge Request
	__sbit __at (0xC2) ARBLOST1;// SMBus1 Arbitration Lost Indicator
	__sbit __at (0xC1) ACK1;    // SMBus1 Acknowledge
	__sbit __at (0xC0) SI1;     // SMBus1 Interrupt Flag
__sfr __at (0xC1) SMB0CF;  // Page: 0 Desc: SMBus0 Configuration 
__sfr __at (0xC1) SMB1CF;  // Page: F Desc: SMBus1 Configuration 
	#define ENSMB    0b10000000
	#define INH      0b01000000
	#define BUSY     0b00100000
	#define EXTHOLD  0b00010000
	#define SMBTOE   0b00001000
	#define SMBFTE   0b00000100
	#define SMBCS1   0b00000010
	#define SMBCS0   0b00000001
__sfr __at (0xC2) SMB0DAT; // Page: 0 Desc: SMBus0 Data 
__sfr __at (0xC2) SMB1DAT; // Page: F Desc: SMBus1 Data 
__sfr __at (0xC3) ADC0GTL; // ADC0 Greater-Than Compare Low 
__sfr __at (0xC4) ADC0GTH; // ADC0 Greater-Than Compare High 
__sfr __at (0xC5) ADC0LTL; // ADC0 Less-Than Compare Word Low 
__sfr __at (0xC6) ADC0LTH; // ADC0 Less-Than Compare Word High 
__sfr __at (0xC7) P4;      // Port 4 Latch 
__sfr __at (0xC8) TMR2CN;  // Page: 0 Desc: Timer/Counter 2 Control 
	__sbit __at (0xCF) TF2;     // Timer 2 Overflow Flag (same as TF2H)
	__sbit __at (0xCF) TF2H;    // Timer 2 High-Byte Overflow Flag
	__sbit __at (0xCE) TF2L;    // Timer 2 Low-Byte Overflow Flag
	__sbit __at (0xCD) TF2LEN;  // Timer 2 Low-Byte Flag Enable
	__sbit __at (0xCC) TF2CEN;  // Timer 2 Capture Enable
	__sbit __at (0xCB) T2SPLIT; // Timer 2 Split-Mode Enable
	__sbit __at (0xCA) TR2;     // Timer2 Run Enable
	__sbit __at (0xC9) T2CSS;   // Timer 2 Capture Source Select
	__sbit __at (0xC8) T2XCLK;  // Timer 2 External Clock Select
__sfr __at (0xC8) TMR5CN;  // Page: F Desc: Timer/Counter 5 Control 
	__sbit __at (0xCF) TF5H;    // Timer 5 High-Byte Overflow Flag
	__sbit __at (0xCE) TF5L;    // Timer 5 Low-Byte Overflow Flag
	__sbit __at (0xCD) TF5LEN;  // Timer 5 Low-Byte Flag Enable
	__sbit __at (0xCC) TMR5CN_4;// Bit 4 unused
	__sbit __at (0xCB) T5SPLIT; // Timer 5 Split-Mode Enable
	__sbit __at (0xCA) TR5;     // Timer 5 Run Enable
	__sbit __at (0xC9) TMR5CN_1;// Bit 1 unused
	__sbit __at (0xC8) T5XCLK;  // Timer 5 External Clock Select.
__sfr __at (0xC9) REG01CN; // Voltage Regulator 0 and 1 Control 
__sfr __at (0xCA) TMR2RLL; // Page: 0 Desc: Timer/Counter 2 Reload Low 
__sfr __at (0xCA) TMR5RLL; // Page: F Desc: Timer/Counter 5 Reload Low 
__sfr __at (0xCB) TMR2RLH; // Page: 0 Desc: Timer/Counter 2 Reload High 
__sfr __at (0xCB) TMR5RLH; // Page: F Desc: Timer/Counter 5 Reload High 
__sfr __at (0xCC) TMR2L;   // Page: 0 Desc: Timer/Counter 2 Low 
__sfr __at (0xCC) TMR5L;   // Page: F Desc: Timer/Counter 5 Low 
__sfr __at (0xCD) TMR2H;   // Page: 0 Desc: Timer/Counter 2 High 
__sfr __at (0xCD) TMR5H;   // Page: F Desc: Timer/Counter 5 High 
__sfr __at (0xCE) SMB0ADM; // Page: 0 Desc: SMBus0 Address Mask 
__sfr __at (0xCE) SMB1ADM; // Page: F Desc: SMBus1 Address Mask 
__sfr __at (0xCF) SMB0ADR; // Page: 0 Desc: SMBus0 Address 
__sfr __at (0xCF) SMB1ADR; // Page: F Desc: SMBus1 Address 
__sfr __at (0xD0) PSW;     // Program Status Word 
	__sbit __at (0xD7) CY;     // Carry Flag
	__sbit __at (0xD6) AC;     // Auxiliary Carry Flag
	__sbit __at (0xD5) F0;     // User Flag 0
	__sbit __at (0xD4) RS1;    // Register Bank Select 1
	__sbit __at (0xD3) RS0;    // Register Bank Select 0
	__sbit __at (0xD2) OV;     // Overflow Flag
	__sbit __at (0xD1) F1;     // User Flag 1
	__sbit __at (0xD0) PARITY; // Accumulator Parity Flag
__sfr __at (0xD1) REF0CN;  // Voltage Reference Control 
__sfr __at (0xD2) SCON1;   // UART1 Control 
__sfr __at (0xD3) SBUF1;   // UART1 Data Buffer 
__sfr __at (0xD4) P0SKIP;  // Port 0 Skip 
__sfr __at (0xD5) P1SKIP;  // Port 1 Skip 
__sfr __at (0xD6) P2SKIP;  // Port 2 Skip 
__sfr __at (0xD7) USB0XCN; // USB0 Transceiver Control 
__sfr __at (0xD8) PCA0CN0; // PCA Control 
__sfr __at (0xD8) PCA0CN;  // PCA Control 
	__sbit __at (0xDF) CF;      // PCA0 Counter Overflow Flag
	__sbit __at (0xDE) CR;      // PCA0 Counter Run Control Bit
	__sbit __at (0xDE) PCA0CN_5;// Bit 5 unused
	__sbit __at (0xDC) CCF4;    // PCA0 Module 4 Capture/Compare Flag
	__sbit __at (0xDB) CCF3;    // PCA0 Module 3 Capture/Compare Flag
	__sbit __at (0xDA) CCF2;    // PCA0 Module 2 Capture/Compare Flag
	__sbit __at (0xD9) CCF1;    // PCA0 Module 1 Capture/Compare Flag
	__sbit __at (0xD8) CCF0;    // PCA0 Module 0 Capture/Compare Flag
__sfr __at (0xD9) PCA0MD; // PCA Mode
	#define CIDL     0x80 // PCA Counter/Timer Idle Control.
	#define WDTE     0x40 // Watchdog Timer Enable.
	#define WDLCK    0x20 // Watchdog Timer Lock.
	#define PCA0MD_4 0x10 // Unused Read = 0b, Write = Don't care.
	#define CPS2     0x08 // PCA Counter/Timer Pulse Select bit 2.
	#define CPS1     0x04 // PCA Counter/Timer Pulse Select bit 1.
	#define CPS0     0x02 // PCA Counter/Timer Pulse Select bit 0.
	#define ECF      0x01 // PCA Counter/Timer Overflow Interrupt Enable.
__sfr __at (0xDA) PCA0CPM0; // PCA Module 0 Mode Register 
__sfr __at (0xDB) PCA0CPM1; // PCA Module 1 Mode Register 
__sfr __at (0xDC) PCA0CPM2; // PCA Module 2 Mode Register 
__sfr __at (0xDD) PCA0CPM3; // PCA Module 3 Mode Register 
__sfr __at (0xDE) PCA0CPM4; // PCA Module 4 Mode Register
	#define PWM16 0x80 // 16-bit Pulse Width Modulation Enable.
	#define ECOM  0x40 // Comparator Function Enable.
	#define CAPP  0x20 // CAPP Capture Positive Function Enable.
	#define CAPN  0x10 // CAPN Capture Negative Function Enable.
	#define MAT   0x08 // MAT Match Function Enable.
	#define TOG   0x04 // TOG Toggle Function Enable.
	#define PWM   0x02 // PWM Pulse Width Modulation Mode Enable.
	#define ECCF  0x01 // ECCF Capture/Compare Flag Interrupt Enable.
__sfr __at (0xDF) P3SKIP;  // Port 3Skip 
__sfr __at (0xE0) ACC;     // Accumulator 
	__sbit __at (0xE7) ACC_7;
	__sbit __at (0xE6) ACC_6;
	__sbit __at (0xE5) ACC_5;
	__sbit __at (0xE4) ACC_4;
	__sbit __at (0xE3) ACC_3;
	__sbit __at (0xE2) ACC_2;
	__sbit __at (0xE1) ACC_1;
	__sbit __at (0xE0) ACC_0;
__sfr __at (0xE1) XBR0;  // Port I/O Crossbar Control 0 
	#define CP1AE  0x80  // Comparator1 Asynchronous Output Enable.
	#define CP1E   0x40  // Comparator1 Output Enable.
	#define CP0AE  0x20  // Comparator0 Asynchronous Output Enable.
	#define CP0E   0x10  // Comparator0 Output Enable.
	#define SYSCKE 0x08  // SYSCLK Output Enable.
	#define SMB0E  0x04  // SMBus I/O Enable.
	#define SPI0E  0x02  // SPI I/O Enable.
	#define URT0E  0x01  // UART0 I/O Output Enable.
__sfr __at (0xE2) XBR1;  // Port I/O Crossbar Control 1
	#define WEAKPUD 0x80 // Port I/O Weak Pullup Disable.
	#define XBARE   0x40 // Crossbar Enable.
	#define T1E     0x20 // T1 Enable.
	#define T0E     0x10 // T0 Enable.
	#define ECIE    0x08 // PCA0 External Counter Input Enable.
	#define PCA0ME2 0x04 // PCA Module I/O Enable Bits.
	#define PCA0ME1 0x02 // PCA Module I/O Enable Bits.
	#define PCA0ME0 0x01 // PCA Module I/O Enable Bits.
__sfr __at (0xE3) XBR2;  // Port I/O Crossbar Control 2.
	#define SMB1E   0x02 // SMBus1 I/O Enable.
	#define URT1E   0x01 // UART1 I/OEnable.
__sfr __at (0xE4) IT01CF;  // Page: 0 Desc: INT0/INT1 Configuration 
__sfr __at (0xE4) CKCON1;  // Page: F Desc: Clock Control 1 
__sfr __at (0xE5) SMOD1;   // UART1 Mode 
__sfr __at (0xE6) EIE1;    // Extended Interrupt Enable 1
	#define ET3    0x80 // Enable Timer 3 Interrupt.
	#define ECP1   0x40 // Enable Comparator1 (CP1) Interrupt.
	#define ECP0   0x20 // Enable Comparator0 (CP0) Interrupt.
	#define EPCA0  0x10 // Enable Programmable Counter Array (PCA0) Interrupt.
	#define EADC0  0x08 // Enable ADC0 Conversion Complete Interrupt.
	#define EWADC0 0x04 // Enable Window Comparison ADC0 Interrupt.
	#define EUSB0  0x02 // Enable USB (USB0) Interrupt.
	#define ESMB0  0x01 // Enable SMBus0 Interrupt.
__sfr __at (0xE7) EIE2;    // Extended Interrupt Enable 2
	#define EIE2_7 0x80 // Not used
	#define EIE2_6 0x40 // Not used
	#define ET5    0x20 // Enable Timer 5 Interrupt.
	#define ET4    0x10 // Enable Timer 4 Interrupt.
	#define ESMB1  0x08 // Enable SMBus1 Interrupt.
	#define EIE2_2 0x04 // Reserved.  Write 0.
	#define ES1    0x20 // Enable UART1 Interrupt.
	#define EVBUS  0x01 // Enable VBUS Level Interrupt.
__sfr __at (0xE8) ADC0CN0;  // ADC0 Control 
__sfr __at (0xE8) ADC0CN;   // ADC0 Control 
	__sbit __at (0xEF) AD0EN;   // ADC0 Enable
	__sbit __at (0xEE) AD0TM;   // ADC0 Track Mode Bit
	__sbit __at (0xED) AD0INT;  // ADC0 Conversion Complete Interrupt Flag
	__sbit __at (0xEC) AD0BUSY; // ADC0 Busy Flag
	__sbit __at (0xEB) AD0WINT; // ADC0 Window Compare Interrupt Flag
	__sbit __at (0xEA) AD0CM2;  // ADC0 Start Of Conversion Mode Bit 2
	__sbit __at (0xE9) AD0CM1;  // ADC0 Start Of Conversion Mode Bit 1
	__sbit __at (0xE8) AD0CM0;  // ADC0 Start Of Conversion Mode Bit 0
__sfr __at (0xE9) PCA0CPL1;// PCA Capture 1 Low 
__sfr __at (0xEA) PCA0CPH1;// PCA Capture 1 High 
__sfr __at (0xEB) PCA0CPL2;// PCA Capture 2 Low 
__sfr __at (0xEC) PCA0CPH2;// PCA Capture 2 High 
__sfr __at (0xED) PCA0CPL3;// PCA Capture 3 Low 
__sfr __at (0xEE) PCA0CPH3;// PCA Capture 3High 
__sfr __at (0xEF) RSTSRC;  // Reset Source Configuration/Status 
__sfr __at (0xF0) B;       // B Register 
	__sbit __at (0xF7) B_7;
	__sbit __at (0xF6) B_6;
	__sbit __at (0xF5) B_5;
	__sbit __at (0xF4) B_4;
	__sbit __at (0xF3) B_3;
	__sbit __at (0xF2) B_2;
	__sbit __at (0xF1) B_1;
	__sbit __at (0xF0) B_0;
__sfr __at (0xF1) P0MDIN;  // Port 0 Input Mode Configuration 
__sfr __at (0xF2) P1MDIN;  // Port 1 Input Mode Configuration 
__sfr __at (0xF3) P2MDIN;  // Port 2 Input Mode Configuration 
__sfr __at (0xF4) P3MDIN;  // Port 3 Input Mode Configuration 
__sfr __at (0xF5) P4MDIN;  // Port 4 Input Mode Configuration 
__sfr __at (0xF6) EIP1;    // Extended Interrupt Priority 1 
__sfr __at (0xF7) EIP2;    // Extended Interrupt Priority 2 
__sfr __at (0xF8) SPI0CN0; // SPI Control
__sfr __at (0xF8) SPI0CN;  // SPI Control
	__sbit __at (0xFF) SPIF;   // SPI0 Interrupt Flag
	__sbit __at (0xFE) WCOL;   // SPI0 Write Collision Flag
	__sbit __at (0xFD) MODF;   // SPI0 Mode Fault Flag
	__sbit __at (0xFC) RXOVRN; // SPI0 RX Overrun Flag
	__sbit __at (0xFB) NSSMD1; // SPI0 Slave Select Mode 1
	__sbit __at (0xFA) NSSMD0; // SPI0 Slave Select Mode 0
	__sbit __at (0xF9) TXBMT;  // SPI0 TX Buffer Empty Flag
	__sbit __at (0xF8) SPIEN;  // SPI0 Enable
__sfr __at (0xF9) PCA0L;   // PCA Counter Low 
__sfr __at (0xFA) PCA0H;   // PCA Counter High 
__sfr __at (0xFB) PCA0CPL0;// PCA Capture 0 Low 
__sfr __at (0xFC) PCA0CPH0;// PCA Capture 0 High 
__sfr __at (0xFD) PCA0CPL4;// PCA Capture 4 Low 
__sfr __at (0xFE) PCA0CPH4;// PCA Capture 4 High 
__sfr __at (0xFF) VDM0CN;  // VDD Monitor Control 

// 16-Bit Register definitions
__sfr16 __at (0x8382) DPTR;      // Data pointer
__sfr16 __at (0xCBCA) TMR2RL;  // Timer\Counter 2 reload data
__sfr16 __at (0x9392) TMR3RL;  // Timer 3 reload register
__sfr16 __at (0x9392) TMR4RL;  // Timer 4 reload register (page F)
__sfr16 __at (0xCBCA) TMR5RL;  // Timer\Counter 5 reload data (page F)
__sfr16 __at (0xCDCC) TMR2;    // Timer\Counter 2 data
__sfr16 __at (0x9594) TMR3;    // Timer 3 register
__sfr16 __at (0x9594) TMR4;    // Timer 4 register (page F)
__sfr16 __at (0xCDCC) TMR5;    // Timer\Counter 5 data
__sfr16 __at (0xB5B4) SBRL1;   // UART1 Baud Rate Generator
__sfr16 __at (0xBEBD) ADC0;    // ADC 0 data
__sfr16 __at (0xC4C3) ADC0GT;  // ADC 0 greater than compare
__sfr16 __at (0xC6C5) ADC0LT;  // ADC 0 less than compare
__sfr16 __at (0xFAF9) PCA0;    // PCA 0 counter data
__sfr16 __at (0xEAE9) PCA0CP1; // PCA module 1 capture/compare data
__sfr16 __at (0xECEB) PCA0CP2; // PCA module 2 capture/compare data
__sfr16 __at (0xEEED) PCA0CP3; // PCA module 3 capture/compare data
__sfr16 __at (0xFCFB) PCA0CP0; // PCA 0 capture data
__sfr16 __at (0xFEFD) PCA0CP4; // PCA 4 capture data

// ADC multiplexer selection values for 32-pin packages (both QFN and QFP)
#define LQFP32_MUX_P1_0   0b_000000  
#define LQFP32_MUX_P1_1   0b_000001 
#define LQFP32_MUX_P1_2   0b_000010
#define LQFP32_MUX_P1_3   0b_000011
#define LQFP32_MUX_P1_4   0b_000100
#define LQFP32_MUX_P1_5   0b_000101
#define LQFP32_MUX_P1_6   0b_000110
#define LQFP32_MUX_P1_7   0b_000111
#define LQFP32_MUX_P2_0   0b_001000
#define LQFP32_MUX_P2_1   0b_001001
#define LQFP32_MUX_P2_2   0b_001010
#define LQFP32_MUX_P2_3   0b_001011
#define LQFP32_MUX_P2_4   0b_001100
#define LQFP32_MUX_P2_5   0b_001101
#define LQFP32_MUX_P2_6   0b_001110
#define LQFP32_MUX_P2_7   0b_001111
#define LQFP32_MUX_P3_0   0b_010000
#define LQFP32_MUX_P0_0   0b_010001
#define LQFP32_MUX_P0_1   0b_010010
#define LQFP32_MUX_P0_4   0b_010011
#define LQFP32_MUX_P0_5   0b_010100
#define LQFP32_MUX_TEMP   0b_011110
#define LQFP32_MUX_VREF   0b_011110 
#define LQFP32_MUX_VDD    0b_011111
#define LQFP32_MUX_GND    0b_011111

// ADC multiplexer selection values for 48-pin packages
#define TQFP48_MUX_P2_0   0b_000000  
#define TQFP48_MUX_P2_1   0b_000001  
#define TQFP48_MUX_P2_2   0b_000010  
#define TQFP48_MUX_P2_3   0b_000011  
#define TQFP48_MUX_P2_5   0b_000100  
#define TQFP48_MUX_P2_6   0b_000101  
#define TQFP48_MUX_P3_0   0b_000110  
#define TQFP48_MUX_P3_1   0b_000111  
#define TQFP48_MUX_P3_4   0b_001000  
#define TQFP48_MUX_P3_5   0b_001001  
#define TQFP48_MUX_P3_7   0b_001010  
#define TQFP48_MUX_P4_0   0b_001011  
#define TQFP48_MUX_P4_3   0b_001100  
#define TQFP48_MUX_P4_4   0b_001101  
#define TQFP48_MUX_P4_5   0b_001110  
#define TQFP48_MUX_P4_6   0b_001111  
#define TQFP48_MUX_P0_3   0b_010001  
#define TQFP48_MUX_P0_4   0b_010010  
#define TQFP48_MUX_P1_1   0b_010011  
#define TQFP48_MUX_P1_2   0b_010100  
#define TQFP48_MUX_P1_0   0b_010101  
#define TQFP48_MUX_P1_3   0b_010110  
#define TQFP48_MUX_P1_6   0b_010111  
#define TQFP48_MUX_P1_7   0b_011000  
#define TQFP48_MUX_P2_4   0b_011001  
#define TQFP48_MUX_P2_7   0b_011010  
#define TQFP48_MUX_P3_2   0b_011011  
#define TQFP48_MUX_P3_3   0b_011100  
#define TQFP48_MUX_P3_6   0b_011101  
#define TQFP48_MUX_TEMP   0b_011110  
#define TQFP48_MUX_VREF   0b_011110  
#define TQFP48_MUX_VDD    0b_011111  
#define TQFP48_MUX_GND    0b_011111  
#define TQFP48_MUX_P4_1   0b_100000  
#define TQFP48_MUX_P4_2   0b_100001  
#define TQFP48_MUX_P4_7   0b_100010  


#endif // #define EFM8UB2_H
