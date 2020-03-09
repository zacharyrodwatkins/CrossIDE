/*  _ultosd.c: unsigned long to decimal string conversion

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

char * _ultosd (long L)
{
    L; // Hush the compiler

    // long is passed in [acc, b, dph, dpl]

    __asm
    	
    	; The long lives in r2, r1, dph, dpl.  dph and dpl are good already
    	mov r2, a
    	mov r1, b

    	; The BCD result lives in r7,r6,r5,r4,r3. Initialize to zero.
    	clr a
    	mov r3, a
    	mov r4, a
    	mov r5, a
    	mov r6, a
    	mov r7, a

    	mov r0, #32 ; Loop counter
    	
    Conversion_Loop:
    	; Shift the FP mantissa in r2, r1, dph, dpl left by one bit.
    	clr c

    	mov a, dpl
    	rlc a
    	mov dpl, a

    	mov a, dph
    	rlc a
    	mov dph, a

    	mov a, r1
    	rlc a
    	mov r1, a

    	mov a, r2
    	rlc a
    	mov r2, a

    	; Multiply the BCD by two and add the carry from the shift above.
    	; Note: to multiply by two in BCD we add the number to itself with decimal adjust.

    	mov a, r3
    	addc a, r3
    	da a
    	mov r3, a
    	
    	mov a, r4
    	addc a, r4
    	da a
    	mov r4, a

    	mov a, r5
    	addc a, r5
    	da a
    	mov r5, a

    	mov a, r6
    	addc a, r6
    	da a
    	mov r6, a

    	mov a, r7
    	addc a, r7
    	da a
    	mov r7, a

    	djnz r0, Conversion_Loop

	BCD_to_ASCII:
    	; The conversion to BCD is complete. Now convert BCD to ASCII and store in _taos[].
    	mov r0, #__taos
    	mov r1, #ar7 ; Output the most significant digit first.  The BCD uses five bytes (r7, r6, r5, r4, r3)
    ASCII_digits_loop:
    	mov a, @r1
    	swap a
    	anl a, #0x0F
    	orl a, #'0'
    	mov @r0, a
    	inc r0
    	mov a, @r1
    	anl a, #0x0F
    	orl a, #'0'
    	mov @r0, a
    	inc r0
    	dec r1
    	cjne r1, #ar2, ASCII_digits_loop

    	clr a ; Terminate the ASCII string with zero.  Done!
    	mov @r0, a
    __endasm;

    return _taos;
}
