/*  div16.c: divides a 16 bit integer by an 8 bit integer

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

// Divides a 16-bit normalized number by a 8-bit normalized number using
//
// P=(P*16)-(qn*D).
//

static void dummy(void) __naked
{
    __asm
    public	___div16by8
    ___div16by8:

	push ar6
	push ar5
	push ar1
	push ar0
	push b
	push dpl
	push dph
	
    ; The partial remainder 'P' is in r5/r4/r3
    mov r5, #0
    ; The dividend 'D' is initially in r2.

    rseg R_CSEG
   
    ; The most significant digit of the denominator is used to estimate all the
    ; digits of the quotient.  For speed store it into a register.
	mov a, r2
	anl a, #0f0h
	swap a    
    mov r6, a
    
	mov dph, #2 ; Loop counter. 2 radix-16 digits are required for the result
    
    ; -------------- Radix-16 recurrence loop starts here --------------
    
L00010?:   

    ; Get an estimate of 'qn' using the 'div ab' instruction.
    mov b, r6
	mov a, r4
	div ab
	mov dpl, a ; Save 'qn'    

    ; Compute (P*0x10) by shifting the 4-bit digit to the left.  For speed, use the
    ; 'swap' and exchange digit 'xchd' instructions.
    
    mov a, r3
    swap a
    mov r3, a
    
    mov a, r4
    swap a
    mov r4, a
    
    mov a, r5
    anl a, #0fh ; The high part of r5 propagates to r3, so make it zero.
    swap a
    ; mov r5, a ; Redundant, see below

	mov r0, #ar4 ; The xchd instruction works only with indirect addressesing.
    ; mov a, r5 ; Redundant, see above
	xchd a, @r0
	mov r5, a
    
	dec r0
	mov a, r4
	xchd a, @r0
	mov r4, a
    
	dec r0
	mov a, r3
	xchd a, @r0
	mov r3, a

    ; Compute qn * D
        
	mov b, dpl ; qn = dpl
	mov a, r2
	mul ab
	mov r0, a ; qn * D is in b,r0,0

    ; Compute the new remainder using the recurrence formula P=(P*0x10)-(qn*D). 
    
    ;clr c ; carry is already zero from the 'mul ab' above...
    mov	a, r3
    subb a, #0
    mov r3, a
    
    mov	a, r4
    subb a, r0
    mov r4, a
    
    mov	a, r5
    subb a, b
    mov r5, a

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
	jnb acc.7, L00012? ; bit 7 of r5 is used as 'sign' here.  
    dec dpl
    
	mov a, r3
	add a, #0
	mov r3, a
	
	mov a, r4
	addc a, r2
	mov r4, a
	
	clr a
	addc a, r5
	mov r5, a
	
	sjmp L00011?
    
L00012?:
	push dpl ; save the computed digit into the stack.
    
	djnz dph, L00010? ; Repeat recurrence loop.

	; Done, extract the result and return
	pop dpl
	pop acc
	mov c, acc.4
	anl a, #0fh
	swap a
	orl a, dpl ; The 9-bit result is in cy, Acc

	pop dph
	pop dpl
	pop b
	pop ar0
	pop ar1
	pop ar5
	pop ar6
    
    ret
    
    __endasm;
}
