/*  _ultosh.c: unsigned long to hex string conversion

    Copyright (C) 2011  Jesus Calvino-Fraga, jesuscf@gmail.com

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
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA */

// ~C51~  -c

// These 16 bytes of idata memory are used to return the result.
extern idata char _taos[16]; // To ASCII output string
volatile static const char hex[]="0123456789ABCDEF";

char * _ultosh (long L)
{
    L; // Hush the compiler

    // long is passed in [acc, b, dph, dpl]

    __asm
    	; The long lives in r7, r6, r5, r4.
    	mov r7, a
    	mov r6, b
	   	mov r5, dph
	   	mov r4, dpl

	BCD_to_ASCII:
    	mov r0, #__taos
    	mov dptr, #_hex
    	mov r1, #ar7 ; Output the most significant digit first.
    ASCII_digits_loop:
    	mov a, @r1
    	swap a
    	anl a, #0x0F
    	movc a,@dptr+a
    	mov @r0, a
    	inc r0
    	mov a, @r1
    	anl a, #0x0F
    	movc a,@dptr+a
    	mov @r0, a
    	inc r0
    	dec r1
    	cjne r1, #ar3, ASCII_digits_loop

    	clr a ; Terminate the ASCII string with zero.  Done!
    	mov @r0, a
    __endasm;

    return _taos;
}
