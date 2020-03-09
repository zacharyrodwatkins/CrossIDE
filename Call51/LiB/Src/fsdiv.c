/*  fsdiv2.c: floating point division

    Copyright (C) 2011-2012  Jesus Calvino-Fraga, jesuscf@gmail.com

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

#define C51_FLOAT_LIB
#include <float.h>

// This asm version of the floating point division uses the recurrence formula
//
// P=(P*16)-(qn*D).
//
// with radix-16 instead of the most common radix-2.  This is possible because
// the 8051 has an 8-bit by 8-bit integer division instruction that allows for
// the easy and efficient estimation of the quotient digits.  The resulting
// function is about 37.5% faster than the radix-2 version but uses 50% more
// code space. 

// float __fsdiv (float a, float b) __reentrant
static void dummy(void) __naked
{
    __asm
    public	___fsdiv
    ___fsdiv:
    ; extract the two inputs, placing them into:
    ;      sign     exponent   mantissa
    ;      ----     --------   --------
    ;  a:  sign_a   exp_a      r4/r3/r2
    ;  b:  sign_b   exp_b      r7/r6/r5

    lcall	fsgetargs

    ; compute final sign bit
    jnb	sign_b, L00001?
    cpl	sign_a
L00001?:
    ; if divisor is zero, ...
    cjne r7, #0, L00003?
    ; if dividend is also zero, return NaN
    cjne r4, #0, L00002?
    ljmp fs_return_nan
L00002?:
    ; but dividend is non-zero, return infinity
    ljmp fs_return_inf
L00003?:
    ; if dividend is zero, return zero
    cjne r4, #0, L00004?
    ljmp fs_return_zero
L00004?:
    ; if divisor is infinity, ...
    mov	a, exp_b
    cjne a, #0xFF, L00006?
    ; and dividend is also infinity, return NaN
    mov	a, exp_a
    cjne a, #0xFF, L00005?
    ljmp fs_return_nan
L00005?:
    ; but dividend is not infinity, return zero
    ljmp fs_return_zero
    L00006?:
    ; if dividend is infinity, return infinity
    mov	a, exp_a
    cjne a, #0xFF, L00007?
    ljmp fs_return_inf
L00007?:

    ; subtract exponents
    clr	c
    subb a, exp_b
    ; if no carry then no underflow
    jnc	L00008?
    add	a, #127
    jc	L00009?
    ljmp fs_return_zero

L00008?:
    add	a, #128
    dec	a
    jnc L00009?
    ljmp fs_return_inf

L00009?:
    push acc ; Save the exponent of the result into the stack

    ; The partial remainder 'P' is in r4/r3/r2/r1
    clr	a
    xch	a, r4
    xch	a, r3
    xch	a, r2
    mov	r1, a

	; Use the overlay segment to store some frequently used variables.  This
	; is needed because there are not enough general purpose registers available.
	
    rseg R_OSEG
    
saved_r5:    ds    1
saved_r6:    ds    1
saved_r7:    ds    1
saved_b:     ds    1

    rseg R_CSEG
   
    ; The dividend 'D' is initially in r7/r6/r5 and saved in saved_r7/saved_6/saved_r5.
    mov saved_r5, r5 
    mov saved_r6, r6 
    mov saved_r7, r7
    
    ; The most significant digit of the denominator is used to estimate all the
    ; digits of the quotient.  For speed sake`s, store it into a variable.
	mov a, r7
	anl a, #0f0h
	swap a    
    mov saved_b, a
    
	mov dph, #6 ; Loop counter. 6 radix-16 digits are required for a float mantisa.
    
    ; -------------- Radix-16 recurrence loop starts here --------------
    
L00010?:   

    ; Get an estimate of 'qn' using the 'div ab' instruction.
    mov b, saved_b
	mov a, r3
	div ab
	mov dpl, a ; Save 'qn'    

    ; Compute (P*0x10) by shifting the 4-bit digit to the left.  For speed, use the
    ; 'swap' and exchange digit 'xchd' instructions.
    
    mov a, r1
    swap a
    mov r1, a
    
    mov a, r2
    swap a
    mov r2, a
    
    mov a, r3
    swap a
    mov r3, a
    
    mov a, r4
    anl a, #0fh ; The high part of r4 propagates to r1, so make it zero.
    swap a
    ; mov r4, a ; Redundant, see below

	mov r0, #ar3 ; The xchd instruction works only with indirect addressesing.
    ; mov a, r4 ; Redundant, see above
	xchd a, @r0
	mov r4, a
    
	dec r0
	mov a, r3
	xchd a, @r0
	mov r3, a
    
	dec r0
	mov a, r2
	xchd a, @r0
	mov r2, a

    ; Compute qn * D
        
	mov b, dpl ; qn = dpl
	mov a, r5
	mul ab
	mov r0, b
	mov r5, a
    
	mov b, dpl
	mov a, r6
	mul ab
	add a, r0
	mov r6, a
    
	clr a
	addc a, b
	mov r0, a

	mov b, dpl
	mov a, r7
	mul ab
	add a, r0
	mov r7, a
    
	clr a
	addc a, b
	mov r0, a ; r0 is used as a the temporary MSD.

    ; Compute the new remainder using the recurrence formula P=(P*0x10)-(qn*D). 
    
    ;clr c ; carry is already zero from above...
    mov	a, r1
    subb a, r5
    mov r1, a
    mov	a, r2
    subb a, r6
    mov r2, a
    mov	a, r3
    subb a, r7
    mov r3, a
    mov	a, r4
    subb a, r0
    mov r4, a

    ; Restore the original denominator to fast regisers.
    
    mov r5, saved_r5 
    mov r6, saved_r6 
    mov r7, saved_r7
   
   	; /*
    ; Having a negative partial remainder means that the value for 'qn' was too big.
    ; Sometimes the estimated value is off by +1, rarelly by +2. This is mentioned
    ; in  the "The Art of Computer Programming", Volume 2, "Seminumerical Algorithms"
    ; by Knuth.  In the 1971 version, the theorem is in page 237 (Theorem B): "The
    ; most important part of this theorem is that the conclusion is independent
    ; of b (the radix); the trial quotient q will never be more than 2 in error!".
    ; The error is always positive, as shown in step 3 of Algorithm D in the same
    ; page. This, of course, is only valid when using twice the number of digits
    ; in the numerator related to the denominator when estimating q.
    ;
    ; This loop fixes the estimated value and the partial remainder.
 	; */

L00011?:
	jnb acc.7, L00012? ; bit 7 of r4 is used as 'sign' here.  
    dec dpl
    
	mov a, r1
	add a, r5
	mov r1, a
	mov a, r2
	addc a, r6
	mov r2, a
	mov a, r3
	addc a, r7
	mov r3, a
	clr a
	addc a, r4
	mov r4, a
	sjmp L00011?
    
L00012?:
	push dpl     ; save the computed digit into the stack.
    
	djnz dph, L00010? ; Repeat recurrence loop.

    ; ----------------- Recurrence loop ends here -----------------
    
    ; Compute an extra bit to round off properly by checking if (2P-D)>=0.
    ; If so, set the extra bit to one.  Otherwise set it to zero.  This is the
    ; same recurrence loop algorithm as above, but it uses radix-2 instead
    ; of radix-16.
    
	clr c
	mov a, r1
	rlc a
	mov r1, a
	mov a, r2
	rlc a
	mov r2, a
	mov a, r3
	rlc a
	mov r3, a
	mov a, r4
	rlc a
	mov r4, a
    
	clr c
	mov a, r1
	subb a, r5
	mov a, r2
	subb a, r6
	mov a, r3
	subb a, r7
	mov a, r4
	subb a, #0
    
	cpl c
	clr a
	rrc a
	mov r1, a ; Extra bit is now in bit 7 of r1

    ; The division result Q is in the stack, LSD at the top.  Extract it.
    pop ar2
    pop acc
    swap a
    orl a, r2
    mov r2, a

    pop ar3
    pop acc
    swap a
    orl a, r3
    mov r3, a

    pop ar4
    pop acc
    mov b, a ; Save he most significant digit as it can be larger than 0xf
    anl a, #0fh
    swap a
    orl a, r4
    mov r4, a
    
    pop exp_a
    dec exp_a

    ; if the numerator's mantisa is larger than the denominator's mantisa
    ; the first calculated digit > 0xf, so rotate right the quotient:
     
    jnb b.4, L00013? ; The most significant digit was saved above
    setb c
    mov a, r4
    rrc a
    mov r4, a
    mov a, r3
    rrc a
    mov r3, a
    mov a, r2
    rrc a
    mov r2, a
    mov a, r1
    rrc a
    mov r1, a
    inc exp_a

L00013?:
    ; Round the result (if needed!)
	mov a, r1
	jnb acc.7, L00014?
	mov a, #1
	add a, r2
	mov r2, a
	clr a
	addc a, r3
	mov r3, a
	clr a
	addc a, r4
	mov r4, a

L00014?:
    ; lcall fs_normalize_a ; already normalized!
    ljmp fs_zerocheck_return
    
    __endasm;
}
