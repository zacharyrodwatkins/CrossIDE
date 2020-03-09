/*  _ultoso.c: unsigned long to octal string conversion

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

char * _ultoso (long L)
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
     	
    	; The most significant digit is a 2-bit number
    	mov a, r7
    	swap a
    	rr a
    	rr a
    	anl a, #0x03
    	orl a, #'0'
    	mov @r0, a
    	inc r0
    	
    	lcall rra_r7_r6_r5_r4
    	lcall rra_r7_r6_r5_r4
   		
   		mov r1, #10 ; There are 10 3-bit numbers left to convert
   		
    ASCII_digits_loop:
		
    	mov a, r7
    	swap a
    	rr a
    	anl a, #0x07
    	orl a, #'0'
    	mov @r0, a
    	inc r0
    	
    	lcall rra_r7_r6_r5_r4
    	lcall rra_r7_r6_r5_r4
    	lcall rra_r7_r6_r5_r4

    	djnz r1, ASCII_digits_loop

    	clr a ; Terminate the ASCII string with zero.  Done!
    	mov @r0, a
    	sjmp done
    	
	rra_r7_r6_r5_r4:
		clr c
		
		mov a, r4
		rlc a
		mov r4, a
		
		mov a, r5
		rlc a
		mov r5, a
		
		mov a, r6
		rlc a
		mov r6, a
		
		mov a, r7
		rlc a
		mov r7, a
		
		ret

	done:
    __endasm;

    return _taos;
}
