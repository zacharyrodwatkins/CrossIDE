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

#ifdef FLOAT_ASM_MCS51

static void dummy(void) __naked
{
	__asm
	
	public	fs_normalize_a

fs_normalize_a:

#ifdef FLOAT_SHIFT_SPEEDUP
	mov	r0, #4
	mov	a, r4
L00001?:
	jnz	L00003?
	mov	a, exp_a
	add	a, #248
	jnc	L00002?	;denormalized
	mov	exp_a, a
	clr	a
	xch	a, r1
	xch	a, r2
	xch	a, r3
	mov	r4, a
	djnz r0, L00001?
	ret
#endif

L00002?:
	mov	a, r4
L00003?:
	mov	r0, #32
	inc	exp_a
L00004?:
	jb acc.7, L00006?
	djnz exp_a, L00005?
	ret	 ;denormalized
L00005?:
	clr	c
	mov	a, r1
	rlc	a
	mov	r1, a
	mov	a, r2
	rlc	a
	mov	r2, a
	mov	a, r3
	rlc	a
	mov	r3, a
	mov	a, r4
	rlc	a
	mov	r4, a
	djnz r0, L00004?
L00006?:
	dec	exp_a
	ret
	__endasm;
}

#endif