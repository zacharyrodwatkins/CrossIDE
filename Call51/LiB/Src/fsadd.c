/* Floating point library in optimized assembly for 8051
 * Copyright (c) 2004, Paul Stoffregen, paul@pjrc.com
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#define C51_FLOAT_LIB
#include <float.h>
#include <stdbool.h>
#include <c51-lib.h>

// float __fsadd (float a, float b) __reentrant
static void dummy(void) __naked
{

    // extract the two inputs, placing them into:
    //      sign     exponent   mantiassa
    //      ----     --------   ---------
    //  a:  sign_a   exp_a      r4/r3/r2
    //  b:  sign_b   exp_b      r7/r6/r5
    //
    // r1: used to extend precision of a's mantissa
    // r0: general purpose loop counter

    __asm

    public	___fsadd
___fsadd:

    lcall	fsgetargs

    public	fsadd_direct_entry
    fsadd_direct_entry:

    mov	r1, #0 ; we are going to extend mantissa to 32 bits temporarily

    ; which exponent is greater?
    mov	a, exp_b
    cjne	a, exp_a, L00005?
    sjmp	L00011?

L00005?:
	jnc	L00010?

    ; a's exponent was greater, so shift b's mantissa
    lcall	fs_swap_a_b

L00010?:
    ; b's exponent was greater, so shift a's mantissa
    mov	a, exp_b
    clr	c
    subb	a, exp_a
    lcall	fs_rshift_a	; acc has # of shifts to do

L00011?:
    ; decide if we need to add or subtract
    ; sign_a and sign_b are stored in the flag bits of psw,
    ; so this little trick checks if the arguements have the
    ; same sign.
    mov	a, psw
    swap	a
    xrl	a, psw
    jb	acc.1, L00022?

L00020?:
    ; add the mantissas (both positive or both negative)
    mov	a, r2
    add	a, r5
    mov	r2, a
    mov	a, r3
    addc	a, r6
    mov	r3, a
    mov	a, r4
    addc	a, r7
    mov	r4, a
    ; check for overflow past 24 bits
    jnc	L00021?
    mov	a, #1
    lcall	fs_rshift_a
    mov	a, r4
    orl	a, #0x80
    mov	r4, a
    L00021?:
    ljmp	fs_round_and_return

L00022?:
    ; subtract the mantissas (one of them is negative)
    clr	c
    mov	a, r2
    subb	a, r5
    mov	r2, a
    mov	a, r3
    subb	a, r6
    mov	r3, a
    mov	a, r4
    subb	a, r7
    mov	r4, a
    jnc	L00025?
    ; if we get a negative result, turn it positive and
    ; flip the sign bit
    clr	c
    clr	a
    subb	a, r1
    mov	r1, a
    clr	a
    subb	a, r2
    mov	r2, a
    clr	a
    subb	a, r3
    mov	r3, a
    clr	a
    subb	a, r4
    mov	r4, a
    cpl	sign_a
L00025?:
    lcall	fs_normalize_a
    ljmp	fs_round_and_return

    __endasm;
}
