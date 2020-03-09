/*  _ftoa.c: float to string conversion

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

char * _ftoa (float f)
{
    f; // Hush the compiler

    // Print the floating point using format +3.1415926E-05

    __asm
   		push acc ; Save the sign (bit 7) in the stack
   		; Check for floating point zero
     	mov r0, a ; The accumulator contains bits 24 to 31 of the floating point number: save it!
    	orl	a,dpl
    	orl	a,dph
    	orl	a,b
    	jnz	_Is_not_FP_zero
    	; Print "+0.0000000E+00"
    	mov b, a
    	mov r3, a
    	mov r4, a
    	mov r5, a
    	mov r6, a
    	ljmp BCD_to_ASCII

    _Is_not_FP_zero:
    	; Put the floating point (FP) in working registers
    	mov a, r0  ; Retrive original accumulator
 
     	; Extract the FP exponent
    	rl a
    	mov c, b.7
    	mov acc.0, c
    	mov r0, a ; Binary exponent saved in r0

    	; Save the FP mantissa to r4, r3, r2, r1
    	mov	r1,dpl
    	mov	r2,dph
    	setb b.7 ; Most significant bit in FP mantissa is implicit 1
    	mov	r3,b
    	mov r4, #0 ; Extend FP mantissa size by 8 bits.

    	; Initialize BCD exponent
    	mov r6, #7 ; We set it to seven because we are showing 7 decimal digits.

    	; In order to proceed, the FP exponent needs to be >(127+24).
    	; If not, we need to multiply the FP mantissa by decimal 10 until r0>(127+24)

    FP_Adjust:

    	clr c
    	mov a,#(127+24)
    	subb a, r0
    	jc Convert_FP_to_BCD ; r0>(127+24)?

		; Exponent not big enough.
		
    	; Decrement BCD exponent (using two`s complement for negative numbers)
    	mov a, #0xff
    	add a, r6
    	mov r6, a

    	;
    	; Multiply FP mantissa by decimal 10.  First get the partial products:
    	;
    	; r1*10 -> [dpl,r1]
    	mov a,#10
    	mov b, r1
    	mul ab
    	mov r1, a
    	mov dpl, b
    	; r2*10 -> [dph,r2]
    	mov a,#10
    	mov b, r2
    	mul ab
    	mov r2, a
    	mov dph, b
    	; r3*10 -> [b, r3]
    	mov a,#10
    	mov b, r3
    	mul ab
    	mov r3, a
    	;
    	; Second: add the partial products
    	;
    	; r1 <- r1+5 (r1 is already good, but we add 5 to round up the result)
    	mov a, #5
    	add a, r1
    	mov r1, a
    	; r2 <- r2+dpl+carry
    	mov a, r2
    	addc a, dpl
    	mov r2, a
    	; r3 <- r3+dph+carry
    	mov a, r3
    	addc a, dph
    	mov r3, a
    	; r4 <- b+carry
    	mov a, #0
    	addc a, b
    	mov r4, a
    	;
    	; Third: normalize the FP mantissa by shifting the product right until r4 is zero.
    	; After every shift increment the FP exponent.
    	;
    Shift_Product_Right:
    	clr c
    	mov a, r4
    	rrc a
    	mov r4, a
    	;
    	mov a, r3
    	rrc a
    	mov r3, a
    	;
    	mov a, r2
    	rrc a
    	mov r2, a
    	;
    	mov a, r1
    	rrc a
    	mov r1, a
    	;
    	inc r0 ; Increment FP exponent
    	mov a, r4
    	jnz Shift_Product_Right

    	sjmp FP_Adjust

    Convert_FP_to_BCD:
    	; Now we proceed to convert the floating point binary to floating point BCD
    	;
    	; Remove the +127 bias from the FP exponent
    	mov a, r0
    	clr c
    	subb a, #127
    	mov r0, a
    	
    	; The FP binary mantissa lives in dph, r2, r1.  r2 and r1 are good already.
    	mov dph, r3 ; It is more efficient to use r3 for BCD mantissa

    	; Put the BCD exponent in b
    	mov b, r6
    	; The BCD mantissa lives in r7,r6,r5,r4,r3. Initialize to zero.
    	clr a
    	mov r3, a
    	mov r4, a
    	mov r5, a
    	mov r6, a
    	mov r7, a

    	; Adjust the FP exponent to execute the correct number of loops.
    	inc r0
    	
    Conversion_Loop:
    	; Shift the FP mantissa in dph, r2, r1 left by one bit.
    	clr c

    	mov a, r1
    	rlc a
    	mov r1, a

    	mov a, r2
    	rlc a
    	mov r2, a

    	mov a, dph
    	rlc a
    	mov dph, a

    	; Multiply the BCD mantisa by two and add the carry from the shift above.
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

    	jz No_BCD_mantissa_overflow ; If BCD mantissa does not overflow, continue

    	; There is overflow in the BCD mantissa (r7 is not zero).  Adjust both the
    	; BCD mantisa and the BCD exponent.

    	inc b ; Increment the BCD exponent

    	; Before discarding the least significant BCD digit, round off
    	; by adding 5:
    	mov a, #5
    	add a, r3
    	da a
    	mov r3, a

    	clr a
    	addc a, r4
    	da a
    	mov r4, a

    	clr a
    	addc a, r5
    	da a
    	mov r5, a

    	clr a
    	addc a, r6
    	da a
    	mov r6, a

    	clr a
    	addc a, r7
    	da a
    	mov r7, a

    	; Divide by 10 by shifting the BCD mantisa right four bits (one BCD digit)
    	mov dpl, #4
    Divide_by_10_loop:
    	clr c
    	mov a, r7
    	rrc a
    	mov r7, a

    	mov a, r6
    	rrc a
    	mov r6, a

    	mov a, r5
    	rrc a
    	mov r5, a

    	mov a, r4
    	rrc a
    	mov r4, a

    	mov a, r3
    	rrc a
    	mov r3, a

    	djnz dpl, Divide_by_10_loop

    No_BCD_mantissa_overflow:
    	djnz r0, Conversion_Loop

	BCD_to_ASCII:
    	; The conversion to BCD is complete. Now convert BCD to ASCII and store in _taos[].
    	mov r0, #__taos
    	; Start with the sign, which was saved into the stack early on.
    	pop acc
    	jb acc.7, ASCII_minus
    	mov @r0, #'+'
    	sjmp ASCII_digits
    ASCII_minus:
    	mov @r0, #'-'
    ASCII_digits:
    	inc r0
    	mov r1, #ar6 ; Output the most significant digit first.  The bcd mantisa uses four bytes (r6, r5, r4, r3)
    ASCII_digits_loop:
    	mov a, @r1
    	swap a
    	anl a, #0x0F
    	orl a, #'0'
    	mov @r0, a
    	inc r0
    	; Check if we need to insert a decimal point
    	cjne r1, #ar6, No_Decimal_Point
    	mov @r0,#'.'
    	inc r0
    No_Decimal_Point:
    	mov a, @r1
    	anl a, #0x0F
    	orl a, #'0'
    	mov @r0, a
    	inc r0
    	dec r1
    	cjne r1, #ar2, ASCII_digits_loop

    	; Convert the exponent to ASCII
    	mov @r0,#'E'
    	inc r0
    	mov a, b
    	jb acc.7, ASCII_exp_minus
    	mov @r0,#'+'
    	sjmp ASCII_exp
    ASCII_exp_minus:
    	mov @r0,#'-' ; The exponent is negative so we need to get the two`s complement
    	cpl a
    	inc a
    ASCII_exp:
    	inc r0
    	mov b, #10
    	div ab
    	orl a, #'0'
    	mov @r0, a
    	inc r0
    	mov a, b
    	orl a, #'0'
    	mov @r0, a
    	inc r0
    	clr a ; Terminate the ASCII string with zero.  Done!
    	mov @r0, a
    __endasm;

    return _taos;
}
