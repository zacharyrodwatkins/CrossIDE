/*-------------------------------------------------------------------------
   Register Declarations for the DE2-8052 soft-core processor

   Written By -  Jesus Calvino-Fraga / jesusc (at) ece.ubc.ca (July 2011)

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

#ifndef REG_DE2_8052_H
#define REG_DE2_8052_H

__sfr __at (0x80) P0;
__sfr __at (0x81) SP;
__sfr __at (0x82) DPL;
__sfr __at (0x83) DPH;
__sfr __at (0x87) PCON;
__sfr __at (0x88) TCON;
__sfr __at (0x89) TMOD;
__sfr __at (0x8A) TL0;
__sfr __at (0x8B) TL1;
__sfr __at (0x8C) TH0;
__sfr __at (0x8D) TH1;
__sfr __at (0x90) P1;
__sfr __at (0x98) SCON;
__sfr __at (0x99) SBUF;
__sfr __at (0xA0) P2;
__sfr __at (0xA8) IE;
__sfr __at (0xB0) P3;
__sfr __at (0xB8) IP;
__sfr __at (0xD0) PSW;
__sfr __at (0xE0) ACC;
__sfr __at (0xF0) B;

// P0 bits
__sbit __at (0x80) P0_0;
__sbit __at (0x81) P0_1;
__sbit __at (0x82) P0_2;
__sbit __at (0x83) P0_3;
__sbit __at (0x84) P0_4;
__sbit __at (0x85) P0_5;
__sbit __at (0x86) P0_6;
__sbit __at (0x87) P0_7;

// TCON bits
__sbit __at (0x88) IT0;
__sbit __at (0x89) IE0;
__sbit __at (0x8A) IT1;
__sbit __at (0x8B) IE1;
__sbit __at (0x8C) TR0;
__sbit __at (0x8D) TF0;
__sbit __at (0x8E) TR1;
__sbit __at (0x8F) TF1;

// P1 bits
__sbit __at (0x90) P1_0;
__sbit __at (0x91) P1_1;
__sbit __at (0x92) P1_2;
__sbit __at (0x93) P1_3;
__sbit __at (0x94) P1_4;
__sbit __at (0x95) P1_5;
__sbit __at (0x96) P1_6;
__sbit __at (0x97) P1_7;

// SCON
__sbit __at (0x98) RI;
__sbit __at (0x99) TI;
__sbit __at (0x9A) RB8;
__sbit __at (0x9B) TB8;
__sbit __at (0x9C) REN;
__sbit __at (0x9D) SM2;
__sbit __at (0x9E) SM1;
__sbit __at (0x9F) SM0;

// P2
__sbit __at (0xA0) P2_0;
__sbit __at (0xA1) P2_1;
__sbit __at (0xA2) P2_2;
__sbit __at (0xA3) P2_3;
__sbit __at (0xA4) P2_4;
__sbit __at (0xA5) P2_5;
__sbit __at (0xA6) P2_6;
__sbit __at (0xA7) P2_7;

// IE
__sbit __at (0xA8) EX0;
__sbit __at (0xA9) ET0;
__sbit __at (0xAA) EX1;
__sbit __at (0xAB) ET1;
__sbit __at (0xAC) ES;
__sbit __at (0xAD) ET2; /* Enable timer2 interrupt */
__sbit __at (0xAF) EA;

// P3 bits
__sbit __at (0xB0) P3_0;
__sbit __at (0xB1) P3_1;
__sbit __at (0xB2) P3_2;
__sbit __at (0xB3) P3_3;
__sbit __at (0xB4) P3_4;
__sbit __at (0xB5) P3_5;
__sbit __at (0xB6) P3_6;
__sbit __at (0xB7) P3_7;

__sbit __at (0xB0) RXD;
__sbit __at (0xB1) TXD;
__sbit __at (0xB2) INT0;
__sbit __at (0xB3) INT1;
__sbit __at (0xB4) T0;
__sbit __at (0xB5) T1;
__sbit __at (0xB6) WR;
__sbit __at (0xB7) RD;

// IP BITS
__sbit __at (0xB8) PX0;
__sbit __at (0xB9) PT0;
__sbit __at (0xBA) PX1;
__sbit __at (0xBB) PT1;
__sbit __at (0xBC) PS;
__sbit __at (0xBD) PT2; // T2 interrupt priority bit

// PSW  BITS
__sbit __at (0xD0) P;
__sbit __at (0xD1) F1;
__sbit __at (0xD2) OV;
__sbit __at (0xD3) RS0;
__sbit __at (0xD4) RS1;
__sbit __at (0xD5) F0;
__sbit __at (0xD6) AC;
__sbit __at (0xD7) CY;

// PCON bits
#define IDL  0x01
#define PD   0x02
#define GF0  0x04
#define GF1  0x08
#define SMOD 0x80

// TMOD bits
#define T0_M0   0x01
#define T0_M1   0x02
#define T0_CT   0x04
#define T0_GATE 0x08
#define T1_M0   0x10
#define T1_M1   0x20
#define T1_CT   0x40
#define T1_GATE 0x80

#define T0_MASK 0x0F
#define T1_MASK 0xF0

#define EXTERNAL_0_ISR  0   // 0x0003 external interrupt 0
#define TIMER_0_ISR     1   // 0x000b timer/counter 0
#define EXTERNAL_1_ISR  2   // 0x0013 external interrupt 1
#define TIMER_1_ISR     3   // 0x001b timer/counter 1
#define UART_ISR        4   // 0x0023 serial port 0
#define TIMER_2_ISR     5   // 0x002B timer/counter 2

// Standard 8052 specific registers

__sfr __at (0xC8) T2CON;
__sfr __at (0xCA) RCAP2L;
__sfr __at (0xCB) RCAP2H;
__sfr __at (0xCC) TL2;
__sfr __at (0xCD) TH2;

__sbit __at (0xC8) T2CON_0;
__sbit __at (0xC9) T2CON_1;
__sbit __at (0xCA) T2CON_2;
__sbit __at (0xCB) T2CON_3;
__sbit __at (0xCC) T2CON_4;
__sbit __at (0xCD) T2CON_5;
__sbit __at (0xCE) T2CON_6;
__sbit __at (0xCF) T2CON_7;

__sbit __at (0xC8) CP_RL2;
__sbit __at (0xC9) C_T2;
__sbit __at (0xCA) TR2;
__sbit __at (0xCB) EXEN2;
__sbit __at (0xCC) TCLK;
__sbit __at (0xCD) RCLK;
__sbit __at (0xCE) EXF2;
__sbit __at (0xCF) TF2;

// DE2-8052 specific registers

// Second data pointer
__sfr __at (0x86) DPS; // DPH1, DPL1 active when DPS.0=1
__sfr __at (0x85) DPH1;
__sfr __at (0x84) DPL1;

// All the switches, LEDs, etc. in the DE2 board
__sfr __at (0x91) HEX0; // Right display.  Zero turns the segment on
__sfr __at (0x92) HEX1;
__sfr __at (0x93) HEX2;
__sfr __at (0x94) HEX3;
__sfr __at (0x8E) HEX4;
__sfr __at (0x8F) HEX5;
__sfr __at (0xE8) LEDRA; // LEDs LEDR0 to LEDR7
__sfr __at (0x95) LEDRB; // LEDs LEDR8 and LEDR9
__sfr __at (0xE8) SWA; // Switches SW0 to SW7
__sfr __at (0x95) SWB; // Switches SW8 and SW9
__sfr __at (0xF8) KEY; // KEY0=KEY.0, KEY1=KEY.1, KEY2=KEY.2, KEY3=KEY.3.
__sfr __at (0x9A) P0MOD; // Input/output mode bits for port 0
__sfr __at (0x9B) P1MOD; // Input/output mode bits for port 1
__sfr __at (0x9C) P2MOD; // Input/output mode bits for port 2
__sfr __at (0x9D) P3MOD; // Input/output mode bits for port 3

// The bits of LEDRA
__sbit __at (0xE8) LEDRA_0;
__sbit __at (0xE9) LEDRA_1;
__sbit __at (0xEA) LEDRA_2;
__sbit __at (0xEB) LEDRA_3;
__sbit __at (0xEC) LEDRA_4;
__sbit __at (0xED) LEDRA_5;
__sbit __at (0xEE) LEDRA_6;
__sbit __at (0xEF) LEDRA_7;

// The bits of SWA
__sbit __at (0xE8) SWA_0;
__sbit __at (0xE9) SWA_1;
__sbit __at (0xEA) SWA_2;
__sbit __at (0xEB) SWA_3;
__sbit __at (0xEC) SWA_4;
__sbit __at (0xED) SWA_5;
__sbit __at (0xEE) SWA_6;
__sbit __at (0xEF) SWA_7;

// The bits of KEY
__sbit __at (0xF8) KEY_0;
__sbit __at (0xF9) KEY_1;
__sbit __at (0xFA) KEY_2;
__sbit __at (0xFB) KEY_3;

// Access to the LCD display
__sfr __at (0xD8) LCD_CMD;
__sfr __at (0xD9) LCD_DATA;
__sfr __at (0xDA) LCD_MOD;   // Write 0xff to make LCD_DATA an output
__sbit __at (0xD8) LCD_RW;   // '0' write to LCD
__sbit __at (0xD9) LCD_EN;   // Toggle from '1' to '0'
__sbit __at (0xDA) LCD_RS;   // '0' for commands, '1' for data
__sbit __at (0xDB) LCD_ON;   // Write '1' to power the LCD
__sbit __at (0xDC) LCD_BLON; // Write '1' to turn on back light

// Access to the JTAG interface
__sfr __at  (0xC0) JCMD; // Bit addressable.  See below.
__sbit __at (0xC0) JRXRDY;
__sbit __at (0xC1) JTXRDY;
__sbit __at (0xC2) JRXEN;
__sbit __at (0xC3) JTXEN;
__sbit __at (0xC4) JTXFULL;
__sbit __at (0xC5) JRXFULL;
__sbit __at (0xC6) JTXEMPTY;
__sbit __at (0xC7) JTDI;
__sfr  __at (0xC1) JBUF;
__sfr  __at (0xC2) JCNT;

// This three sfrs are used to indirectly access other sfrs.  Using these sfrs to access themselves 
// (especially for writing) may not work!
__sfr __at (0xF1) REP_ADD_L;
__sfr __at (0xF2) REP_ADD_H;
__sfr __at (0xF3) REP_VALUE;

__sfr __at (0xFA) DEBUG_CALL_L;
__sfr __at (0xFB) DEBUG_CALL_H;

// Break point and step by step control
__sfr __at (0xFC) BPC;
__sfr __at (0xFD) BPS;
__sfr __at (0xFE) BPAL;
__sfr __at (0xFF) BPAH;
__sfr __at (0xFA) LBPAL;
__sfr __at (0xFB) LBPAH;

// Parallel flash memory
__sfr __at (0xC3) XRAMUSEDAS;
__sfr __at (0xDB) FLASH_CMD; // The control bits of the flash memory:
//	bit 0: FL_RST_N  Set to 1 for normal operation
//	bit 1: FL_WE_N
//	bit 2: FL_OE_N
//	bit 3: FL_CE_N
__sfr __at (0xDC) FLASH_DATA; // 8-bit data bus of flash memory.
__sfr __at (0xDD) FLASH_MOD;  // 0xff makes FLASH_DATA output.  0x00 makes FLASH_DATA input.
__sfr __at (0xE1) FLASH_ADD0; // address bits 0 to 7.
__sfr __at (0xE2) FLASH_ADD1; // address bits 8 to 15.
__sfr __at (0xE3) FLASH_ADD2; // address bits 16 to 21.

#ifdef C51_HAS_MAIN_FUNCTION

// Since this processor has dual data pointers, use them for initialization.
// Compare to file lib\_crt0.c to see the advantages of dual data pointers.
void de2_8052_crt0 (void) _naked
{
	_asm
	
	rseg R_GSINIT
	public _crt0
_crt0:	
	mov	sp,#_stack_start-1
	lcall	__c51_external_startup
	mov	a,dpl
	jz	__c51_init_data
	ljmp	__c51_program_startup
__c51_init_data:

; Initialize xdata variables

	mov dpl,   #_R_XINIT_start
	mov dph,   #(_R_XINIT_start>>8)
	mov _DPL1, #_R_IXSEG_start
	mov _DPH1, #(_R_IXSEG_start>>8)
	mov r0,    #_R_IXSEG_size
	mov r1,    #(_R_IXSEG_size>>8)
	
XInitLoop?repeat?:
	mov a, r0
	orl a, r1
	jz XInitLoop?done?
	clr a
	mov _DPS, #0 ; Using dpl, dph
	movc a,@a+dptr
	inc dptr
	mov _DPS, #1 ; Using DPL1, DPH1
	movx @dptr, a
	inc dptr
	dec r0
	cjne r0, #0xff, XInitLoop?repeat?
	dec r1
	sjmp XInitLoop?repeat?
	
XInitLoop?done?:

; Clear xdata variables
	mov _DPS, #0 ; Make sure we are using dpl, dph
	mov dpl,  #_R_XSEG_start
	mov dph,  #(_R_XSEG_start>>8)
	mov r4,   #_R_XSEG_size
	mov r5,   #(_R_XSEG_size>>8)
	
XClearLoop?repeat?:
	mov a, r4
	orl a, r5
	jz XClearLoop?done?
	clr a
	movx @dptr, a
	inc dptr
	dec r4
	cjne r4, #0xff, XClearLoop?repeat?
	dec r5
	sjmp XClearLoop?repeat?
	
XClearLoop?done?:
	lcall _R_DINIT_start ; Initialize data/idata variables
	
__c51_program_startup:
	lcall	_main

forever?home?:
	sjmp forever?home?
		
	_endasm;
}

#endif //C51_HAS_MAIN_FUNCTION

#endif //REG_DE2_8052_H