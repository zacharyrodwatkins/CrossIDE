/*-------------------------------------------------------------------------
   Register Declarations for Chipcon CC1010

   Written By -  Jesus Calvino-Fraga / jesusc at ece.ubc.ca (July 2007)
   (Based on Chipcom CC1010 Data Sheet SWRS047)

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

   In other words, you are welcome to use, share and improve this program.
   You are forbidden to forbid anyone else to use, share and improve
   what you give them.   Help stamp out software-hoarding!
-------------------------------------------------------------------------*/

#ifndef REG_CC1010_H
#define REG_CC1010_H

#include <compiler.h>

// Interrupt Vectors
#define DEBUG_VECTOR  ((0x33-3)/8) // Flash / Debug interrupt
#define EXT0_VECTOR   ((0x03-3)/8) // External Interrupt 0
#define T0_VECTOR     ((0x0B-3)/8) // Timer 0 Interrupt
#define EXT1_VECTOR   ((0x13-3)/8) // External Interrupt 1
#define T1_VECTOR     ((0x1B-3)/8) // Timer 1 Interrupt
#define SCON0_VECTOR  ((0x23-3)/8) // Serial Port 0 Transmit/Receive Interrupt
#define SCON1_VECTOR  ((0x3B-3)/8) // Serial Port 1 Transmit/Receive Interrupt
#define RF_VECTOR     ((0x43-3)/8) // RF Transmit / Receive Interrupt
#define T2_VECTOR     ((0x4B-3)/8) // Timer 2 Interrupt
#define ADC_VECTOR    ((0x53-3)/8) // ADC Interrupt & DES Encryption/Decryption Interrupt
#define T3_VECTOR     ((0x5B-3)/8) // Timer 3 Interrupt
#define RTC_VECTOR    ((0x63-3)/8) // Realtime Clock Interrupt

// SFR Registers and BITs

SFR(DPL0,   0x82); // Data Pointer 0 Low Byte
SFR(DPH0,   0x83); // Data Pointer 0 High Byte
SFR(DPL1,   0x84); // Data Pointer 1 Low Byte
SFR(DPH1,   0x85); // Data Pointer 1 High Byte
SFR(DPS,    0x92); // Data Pointer Select
SFR(MPAGE,  0x93); // Memory Page Select
SFR(_XPAGE, 0x93); // Memory Page Select under the name SDCC needs it
SFR(PSW,    0xD0); // Program Status Word
   SBIT(P,   0xD0, 0); // Parity Flag
   SBIT(F1,  0xD0, 1); // User-Defined Flag
   SBIT(OV,  0xD0, 2); // Overflow Flag
   SBIT(RS0, 0xD0, 3); // Register Bank Select 0
   SBIT(RS1, 0xD0, 4); // Register Bank Select 1
   SBIT(F0,  0xD0, 5); // User-Defined Flag
   SBIT(AC,  0xD0, 6); // Auxiliary Carry Flag
   SBIT(CY,  0xD0, 7); // Carry Flag
SFR(ACC, 0xE0); // Accumulator
   SBIT(ACC_0, 0xE0, 0); // Accumulator bit 0
   SBIT(ACC_1, 0xE0, 1); // Accumulator bit 1
   SBIT(ACC_2, 0xE0, 2); // Accumulator bit 2
   SBIT(ACC_3, 0xE0, 3); // Accumulator bit 3
   SBIT(ACC_4, 0xE0, 4); // Accumulator bit 4
   SBIT(ACC_5, 0xE0, 5); // Accumulator bit 5
   SBIT(ACC_6, 0xE0, 6); // Accumulator bit 6
   SBIT(ACC_7, 0xE0, 7); // Accumulator bit 7
SFR(B, 0xF0); // B Register
   SBIT(B_0,      0xF0, 0); // Register B bit 0
   SBIT(B_1,      0xF0, 1); // Register B bit 1
   SBIT(B_2,      0xF0, 2); // Register B bit 2
   SBIT(B_3,      0xF0, 3); // Register B bit 3
   SBIT(B_4,      0xF0, 4); // Register B bit 4
   SBIT(B_5,      0xF0, 5); // Register B bit 5
   SBIT(B_6,      0xF0, 6); // Register B bit 6
   SBIT(B_7,      0xF0, 7); // Register B bit 7
SFR(SP, 0x81); // Stack Pointer
SFR(IE, 0xA8); //Interrupt Enable Register
   SBIT(EA,  0xA8, 7); // Global Interrupt enable / disable
   SBIT(ES1, 0xA8, 6); // Serial Port 1 interrupt enable / disable
   SBIT(ES0, 0xA8, 4); // Serial Port 0 interrupt enable / disable
   SBIT(ET1, 0xA8, 3); // Timer 1 interrupt enable / disable
   SBIT(EX1, 0xA8, 2); // External interrupt 1 (from P3.3) enable / disable
   SBIT(ET0, 0xA8, 1); // Timer 0 interrupt enable / disable
   SBIT(EX0, 0xA8, 0); // External interrupt 0 (from P3.2) enable / disable
SFR(EIE, 0xE8); // Extended Interrupt Enable Register
   SBIT(RTCIE, 0xE8, 4); // Realtime Clock interrupt enable / disable
   SBIT(ET3,   0xE8, 3); // Timer 3 interrupt enable / disable
   SBIT(ADIE,  0xE8, 2); // ADC / DES interrupt enable / disable
   SBIT(ET2,   0xE8, 1); // Timer 2 interrupt enable / disable
   SBIT(RFIE,  0xE8, 0); // RF Interrupt enable / disable
SFR(EICON, 0xD8); // Extended Interrupt Control
   SBIT(SMOD1, 0xD8, 7); // Serial Port 1 baud rate doubler
   SBIT(FDIE,  0xD8, 5); // Flash / Debug interrupt enable
   SBIT(FDIF,  0xD8, 4); // Flash / Debug interrupt flag
   SBIT(RTCIF, 0xD8, 3); // Real-time clock interrupt flag
SFR(EXIF, 0x91); // Extended Interrupt Flag
   #define TF3  0x80 // Timer 3 interrupt flag.
   #define ADIF 0x40 // ADC / DES Interrupt flag.
   #define TF2  0x20 // Timer 2 interrupt flag.
   #define RFIF 0x10 // RF Transmit / receive interrupt flag.
SFR(IP, 0xB8); // Interrupt Priority Register
   SBIT(PS1, 0xB8, 6); // Serial Port 1 interrupt priority control
   SBIT(PS0, 0xB8, 4); // erial Port 0 interrupt priority control
   SBIT(PT1, 0xB8, 3); // Timer 1 interrupt priority control
   SBIT(PX1, 0xB8, 2); // External Interrupt 1 (from P3.3) interrupt priority control
   SBIT(PT0, 0xB8, 1); // Timer 0 interrupt priority control
   SBIT(PX0, 0xB8, 0); // External Interrupt 0 (from P3.2) interrupt priority control
SFR(EIP, 0xF8); // Extended Interrupt Priority Register
   SBIT(PRTC, 0xF8, 4); // Realtime Clock interrupt priority control
   SBIT(PT3,  0xF8, 3); // Timer 3 interrupt priority control
   SBIT(PAD,  0xF8, 2); // ADC / DES interrupt priority control
   SBIT(PT2,  0xF8, 1); // Timer 2 interrupt priority control
   SBIT(PRF,  0xF8, 0); // Description??? 
SFR(PCON, 0x87); // Power Control Register
   #define SMOD0 0x80 // Serial Port 0 baud rate doubler enable.
   #define GF1   0x08 // General purpose flag 1. 
   #define GF0   0x04 // General purpose flag 0. 
   #define STOP  0x02 // Power Down (Stop) mode select. 
   #define IDLE  0x01 // Idle mode select. 
SFR(X32CON, 0xD1); // 32.768 kHz Crystal Oscillator Control Register
   #define X32_BYPASS 0x04 // 32.768 kHz oscillator bypass control signal
   #define X32_PD     0x02 // 32.768 kHz oscillator power down signal
   #define CMODE      0x01 // Select different Clock Modes for the 8051 and its peripherals.
SFR(FLADR, 0xAE); // Flash Write Address Register
SFR(FLCON, 0xAF); // Flash Write Control Register (Please check datasheet for bit assigments)
SFR(FLTIM, 0xDD); // Flash Write Timing Register
SFR(RESERVED, 0xE7); // Reserved register, used by Chipcon debugger software
SFR(RDATA, 0xB9); // Replacement Data
SFR(RADRH, 0xBB); // Replacement address, high byte
SFR(RADRL, 0xBA); // Replacement address, low byte
SFR(CHVER, 0x9F); // Chip Version / Revision Register
SFR(P0, 0x80); // Port 0
   SBIT(P0_0, 0x80, 0); // Port 0 bit 0
   SBIT(P0_1, 0x80, 1); // Port 0 bit 1
   SBIT(P0_2, 0x80, 2); // Port 0 bit 2
   SBIT(P0_3, 0x80, 3); // Port 0 bit 3
SFR(P1, 0x90); // Port 1
   SBIT(P1_0, 0x90, 0); // Port 1 bit 0
   SBIT(P1_1, 0x90, 1); // Port 1 bit 1
   SBIT(P1_2, 0x90, 2); // Port 1 bit 2
   SBIT(P1_3, 0x90, 3); // Port 1 bit 3
   SBIT(P1_4, 0x90, 4); // Port 1 bit 4
   SBIT(P1_5, 0x90, 5); // Port 1 bit 5
   SBIT(P1_6, 0x90, 6); // Port 1 bit 6
   SBIT(P1_7, 0x90, 7); // Port 1 bit 7
SFR(P2, 0xA0); // Port 2
   SBIT(P2_0, 0xA0, 0); // Port 2 bit 0
   SBIT(P2_1, 0xA0, 1); // Port 2 bit 1
   SBIT(P2_2, 0xA0, 2); // Port 2 bit 2
   SBIT(P2_3, 0xA0, 3); // Port 2 bit 3
   SBIT(P2_4, 0xA0, 4); // Port 2 bit 4
   SBIT(P2_5, 0xA0, 5); // Port 2 bit 5
   SBIT(P2_6, 0xA0, 6); // Port 2 bit 6
   SBIT(P2_7, 0xA0, 7); // Port 2 bit 7
SFR(P3, 0xB0); // Port 3
   SBIT(P3_0, 0xB0, 0); // Port 3 bit 0
   SBIT(P3_1, 0xB0, 1); // Port 3 bit 1
   SBIT(P3_2, 0xB0, 2); // Port 3 bit 2
   SBIT(P3_3, 0xB0, 3); // Port 3 bit 3
   SBIT(P3_4, 0xB0, 4); // Port 3 bit 4
   SBIT(P3_5, 0xB0, 5); // Port 3 bit 5
SFR(P0DIR, 0xA4); // Port 0 Direction Register
   #define P0DIR_0 0x01 // Port 0 direction bit 0
   #define P0DIR_1 0x02 // Port 0 direction bit 1
   #define P0DIR_2 0x04 // Port 0 direction bit 2
   #define P0DIR_3 0x08 // Port 0 direction bit 3
SFR(P1DIR, 0xA5); // Port 1 Direction Register
   #define P1DIR_0 0x01 // Port 1 direction bit 0
   #define P1DIR_1 0x02 // Port 1 direction bit 1
   #define P1DIR_2 0x04 // Port 1 direction bit 2
   #define P1DIR_3 0x08 // Port 1 direction bit 3
   #define P1DIR_4 0x10 // Port 1 direction bit 4
   #define P1DIR_5 0x20 // Port 1 direction bit 5
   #define P1DIR_6 0x40 // Port 1 direction bit 6
   #define P1DIR_7 0x80 // Port 1 direction bit 7
SFR(P2DIR, 0xA6); // Port 2 Direction Register
   #define P2DIR_0 0x01 // Port 2 direction bit 0
   #define P2DIR_1 0x02 // Port 2 direction bit 1
   #define P2DIR_2 0x04 // Port 2 direction bit 2
   #define P2DIR_3 0x08 // Port 2 direction bit 3
   #define P2DIR_4 0x10 // Port 2 direction bit 4
   #define P2DIR_5 0x20 // Port 2 direction bit 5
   #define P2DIR_6 0x40 // Port 2 direction bit 6
   #define P2DIR_7 0x80 // Port 2 direction bit 7
SFR(P3DIR, 0xA7); // Port 3 Direction Register
   #define P3DIR_0 0x01 // Port 3 direction bit 0
   #define P3DIR_1 0x02 // Port 3 direction bit 1
   #define P3DIR_2 0x04 // Port 3 direction bit 2
   #define P3DIR_3 0x08 // Port 3 direction bit 3
   #define P3DIR_4 0x10 // Port 3 direction bit 4
   #define P3DIR_5 0x20 // Port 3 direction bit 5
SFR(TL0, 0x8A); // Timer / Counter 0 Low byte counter value
SFR(TL1, 0x8B); // Timer / Counter 1 Low byte counter value
SFR(TH0, 0x8C); // Timer / Counter 0 High byte counter value
SFR(TH1, 0x8D); // Timer / Counter 1 High byte counter value
SFR(TMOD, 0x89); // Timer / Counter 0 and 1 Mode register
   #define GATE1 0x80 // Timer / Counter 1 gate control
   #define CT_1  0x40 // Counter / Timer select for Counter / Timer 1
   #define M1_1  0x20 // 0 Timer / Counter 1 mode select bit 2
   #define M1_0  0x10 // 0 Timer / Counter 1 mode select bit 1
   #define GATE0 0x08 // Timer / Counter 0 gate control
   #define CT_0  0x04 // Counter / Timer select for Counter / Timer 0
   #define M0_1  0x20 // Timer / Counter 0 mode select bit 2
   #define M0_0  0x10 // Timer / Counter 0 mode select bit 1
SFR(TCON, 0x88); // Timer / Counter 0 and 1 control register
   SBIT(TF1, 0x88, 7); // Timer 1 overflow flag. 
   SBIT(TR1, 0x88, 6); // Timer 1 run control bit
   SBIT(TF0, 0x88, 5); // Timer 0 overflow flag. 
   SBIT(TR0, 0x88, 4); // Timer 0 run control bit
   SBIT(IE1, 0x88, 3); // External interrupt 1 edge detect (interrupt flag)
   SBIT(IT1, 0x88, 2); // External interrupt 1 type select.
   SBIT(IE0, 0x88, 1); // External interrupt 0 edge detect (interrupt flag)
   SBIT(IT0, 0x88, 0); // External interrupt 0 type select.
SFR(CKCON, 0x8E); // Timer Clock rate Control Register
   #define T1M  0x10 // Timer 1 clock select. 
   #define T0M  0x08 // Timer 0 clock select. 
   #define MD_2 0x04 // Memory stretch cycles bit 3
   #define MD_1 0x02 // Memory stretch cycles bit 2
   #define MD_0 0x01 // Memory stretch cycles bit 1
SFR(TCON2, 0xA9); // Timer Control register 2
   #define TR3 0x08 // Timer 3 run control
   #define M3  0x04 // Timer 3 mode control.
   #define TR2 0x02 // Timer 2 run control
   #define M2  0x01 // Timer 2 mode control.
SFR(T2PRE, 0xAA); //  Timer 2 Prescaler Control
SFR(T3PRE, 0xAB); // Timer 3 Prescaler Control
SFR(T2, 0xAC); // Timer 2 Low byte counter value
SFR(T3, 0xAD); // Timer 3 Low byte counter value
SFR(WDT, 0xD2); // Watchdog Timer Control Register
   #define WDTSE    0x10 // Watchdog Timer Stop Enable
   #define WDTEN    0x08 // Watchdog Timer Enable / Disable
   #define WDTCLR   0x04 // Watchdog timer clear signal. 
   #define WDTPRE_1 0x02 // Watchdog timer prescaler control bit 2
   #define WDTPRE_0 0x01 // Watchdog timer prescaler control bit 1
SFR(RTCON, 0xED); // Real-time Clock Control Register
   #define RTEN 0x80 // Real-time Clock Enable / Disable
   #define RT   0x7F // Real-time Clock interrupt interval control mask
SFR(SBUF0, 0x99); // Serial Port 0, data buffer
SFR(SBUF1, 0xC1); // Serial Port 1, data buffer
SFR(SCON0, 0x98); // Serial Port 0 Control Register
   SBIT(SM0_0, 0x98, 7); // Serial Port 0 mode bit 1
   SBIT(SM1_0, 0x98, 6); // Serial Port 0 mode bit 2
   SBIT(SM2_0, 0x98, 5); // Multiprocessor communication enable. 
   SBIT(REN_0, 0x98, 4); // Receive enable. 
   SBIT(TB8_0, 0x98, 3); // 9th data bit transmitted in modes 2 and 3.
   SBIT(RB8_0, 0x98, 2); // In modes 2 and 3 RB8_0 indicates the state of the 9th bit received.
   SBIT(TI_0,  0x98, 1); // Transmit interrupt flag. 
   SBIT(RI_0,  0x98, 2); // Receive interrupt flag.
SFR(SCON1, 0xC0); // Serial Port 1 Control Register.
   SBIT(SM0_1, 0xC0, 7); // Serial Port 1 mode bit 1.
   SBIT(SM1_1, 0xC0, 6); // Serial Port 1 mode bit 2.
   SBIT(SM2_1, 0xC0, 5); // Multiprocessor communication enable. 
   SBIT(REN_1, 0xC0, 4); // Receive enable. 
   SBIT(TB8_1, 0xC0, 3); // 9th data bit transmitted in modes 2 and 3.
   SBIT(RB8_1, 0xC0, 2); // In modes 2 and 3 RB8_0 indicates the state of the 9th bit received.
   SBIT(TI_1,  0xC0, 1); // Transmit interrupt flag. 
   SBIT(RI_1,  0xC0, 2); // Receive interrupt flag.
SFR(SPCR, 0xA1); // SPI Control Register
   #define SPE   0x20 // SPI Enable.
   #define DORD  0x10 // Data Order.
   #define CPOL  0x08 // Clock Polarity.
   #define CPHA  0x04 // Clock Phase.
   #define SPR_1 0x02 // SPI Data Rate bit 2.
   #define SPR_0 0x01 // SPI Data Rate bit 1.
SFR(SPDR, 0xA2); // SPI Data Register 
SFR(SPSR, 0xA3); // SPI Status Register
   #define SPA  0x02 // SPI Active status bit
   #define WCOL 0x01 // Write collision flag. 
SFR(CRPCON, 0xC3); // Encryption / Decryption Control Register
   #define CRPIE    0x40 // Encryption / Decryption interrupt enable flag. 
   #define CRPIF    0x20 // Encryption / Decryption interrupt flag.
   #define LOADKEYS 0x10 // Enable / disable loading of keys at start up.
   #define CRPMD    0x08 // OFB / CFB Mode
   #define ENCDEC   0x04 // Encryption / Decryption select
   #define CRPEN    0x01 // Encryption / Decryption start and status bit.
SFR(CRPKEY,  0xC4); // Encryption / Decryption Key Location Register
SFR(CRPDAT,  0xC5); // Encryption / Decryption Data Location Register
SFR(CRPCNT,  0xC6); // Encryption / Decryption Counter
SFR(CRPINI0, 0xB4); // DES Initialisation Vector 0
SFR(CRPINI1, 0xB5); // DES Initialisation Vector 1
SFR(CRPINI2, 0xB6); // DES Initialisation Vector 2
SFR(CRPINI3, 0xB7); // DES Initialisation Vector 3
SFR(CRPINI4, 0xBC); // DES Initialisation Vector 4
SFR(CRPINI5, 0xBD); // DES Initialisation Vector 5
SFR(CRPINI6, 0xBE); // DES Initialisation Vector 6
SFR(CRPINI7, 0xBF); // DES Initialisation Vector 7
SFR(RANCON,  0xC7); // Random Bit Generator Control Register
   #define RANEN 0x02  // Random Bit Generator Enable
   #define RANBIT 0x01 // RANBIT returns one random bit, generated from the RF receiver path.
SFR(ADCON, 0x93); // ADC Control Register
   #define AD_PD   0x80 // ADC Power down bit.
   #define ADCM_1  0x20 // ADC Mode bit 2
   #define ADCM_0  0x10 // ADC Mode bit 1
   #define ADCREF  0x08 // Select the internal ADC Voltage Reference
   #define ADCRUN  0x04 // ADC run control. 
   #define ADADR_1 0x02 // Input to select to the ADC bit 2
   #define ADADR_0 0x01 // Input to select to the ADC bit 1
SFR(ADDATL, 0x94); // ADC Data Register, Low Byte
SFR(ADDATH, 0x95); // ADC Data Register, High Bits
SFR(ADCON2, 0x96); // ADC Control Register 2
   #define ADCIE  0x80 // ADC interrupt enable flag.
   #define ADCIF  0x40 // ADC interrupt flag. 
   #define ADCDIV 0x3F // ADC clock divider. 
SFR(ADTRH, 0x97); // ADC Threshold Register.
SFR(RFMAIN, 0xC8); // RF Main Control Register
   SBIT(RXTX,    0xC8, 7); // RX/TX Switch.
   SBIT(F_REG,   0xC8, 6); // Select the frequency registers A or B
   SBIT(RX_PD,   0xC8, 5); // Select power down for the LNA, mixer, IF filter and digital demodulator.
   SBIT(TX_PD,   0xC8, 4); // Select power down of the digital modem and PA.
   SBIT(FS_PD,   0xC8, 3); // Select power down of the frequency synthesizer
   SBIT(CORE_PD, 0xC8, 2); // Power down of main crystal oscillator core.
   SBIT(BIAS_PD, 0xC8, 1); // Power down of bias current generator and crystal oscillator buffer.
SFR(MODEM0, 0xDB); // Modem Control Register 0
SFR(RFBUF, 0xC9); // RF Data Buffer
SFR(MODEM1, 0xDA); // Modem Control Register 1
SFR(MODEM2, 0xD9); // Modem Control Register 2
SFR(RFCON, 0xC2); // RF Control Register
SFR(PDET, 0xD3); // Preamble Detection Control Register
SFR(BSYNC, 0xD4); // Byte Synchronisation Register
SFR(FREQ_2A, 0xCC); // Frequency A, Control Register 2
SFR(FREQ_1A, 0xCB); // Frequency A, Control Register 1
SFR(FREQ_0A, 0xCA); // Frequency A, Control Register 0
SFR(FREQ_2B, 0xCF); // Frequency B, Control Register 2
SFR(FREQ_1B, 0xCE); // Frequency B, Control Register 1
SFR(FREQ_0B, 0xCD); // Frequency B, Control Register 0
SFR(FSEP1, 0xEB); // Frequency Separation Control Register 1
SFR(FSEP0, 0xEA); // Frequency Separation Control Register 0
SFR(PLL, 0xE3); // PLL Control Register
SFR(LOCK, 0xE4); // PLL Lock Register
SFR(CAL, 0xE5); // PLL Calibration Control Register
SFR(TEST6, 0xFF); // PLL Test Register 6
SFR(TEST5, 0xFE); // PLL Test Register 5
SFR(TEST4, 0xFD); // PLL Test Register 4
SFR(TEST3, 0xFC); // PLL Test Register 3
SFR(TEST2, 0xFB); // PLL Test Register 2
SFR(TEST1, 0xFA); // PLL Test Register 1
SFR(TEST0, 0xF9); // PLL Test Register 0
SFR(CURRENT, 0xE1); // RF Current Control Register
SFR(FREND, 0xEE); // Front End Control Register
SFR(MATCH, 0xDC); // Match Capacitor Array Control Register
SFR(PA_POW, 0xE2); // PA Output Power Control Register
SFR(FSHAPE1, 0xF1); // Frequency Shaping Register 1
SFR(FSHAPE2, 0xF2); // Frequency Shaping Register 2
SFR(FSHAPE3, 0xF3); // Frequency Shaping Register 3
SFR(FSHAPE4, 0xF4); // Frequency Shaping Register 4
SFR(FSHAPE5, 0xF5); // Frequency Shaping Register 5
SFR(FSHAPE6, 0xF6); // Frequency Shaping Register 6
SFR(FSHAPE7, 0xF7); // Frequency Shaping Register 7
SFR(FSDELAY, 0xE9); // Frequency Shaping Delay Control Register
SFR(FSCTRL, 0xEC); // Frequency Synthesiser Control Register
SFR(PRESCALER, 0xE6); // Prescaler Control Register
SFR(TESTMUX, 0xEF); // Test Multiplexer Control Register (for prototype testing)

#endif //REG_CC1010_H
