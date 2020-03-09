/*-------------------------------------------------------------------------
  _divuint.c :- routine for unsigned int (16 bit) division

             Ecrit par -  Jean-Louis Vern . jlvern@writeme.com (1999)

   This library is free software; you can redistribute it and/or modify it
   under the terms of the GNU Library General Public License as published by the
   Free Software Foundation; either version 2, or (at your option) any
   later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this program; if not, write to the Free Software
   Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

   In other words, you are welcome to use, share and improve this program.
   You are forbidden to forbid anyone else to use, share and improve
   what you give them.   Help stamp out software-hoarding!
-------------------------------------------------------------------------*/

/*   Assembler-functions are provided for:
     mcs51 small
     mcs51 small stack-auto
*/

#include <stdbool.h>

#if !defined(C51_USE_XSTACK) && !defined(_C51_NO_ASM_LIB_FUNCS)
#  if defined(C51_mcs51)
#    if defined(C51_MODEL_SMALL)
#      if defined(C51_STACK_AUTO)
#        define _DIVUINT_ASM_SMALL_AUTO
#      else
#        define _DIVUINT_ASM_SMALL
#      endif
#    endif
#  endif
#endif

#if defined _DIVUINT_ASM_SMALL || defined _DIVUINT_ASM_SMALL_AUTO

static void
_divuint_dummy (void) __naked
{
    __asm

    public __divuint

    __divuint:

    #define count   r2
    #define reste_l r3
    #define reste_h r4
    #define xl      dpl
    #define xh      dph

    #if defined(C51_PARMS_IN_BANK1)
    #define yl      (b1_0)
    #define yh      (b1_1)
    #else // C51_PARMS_IN_BANK1
    #if defined(C51_STACK_AUTO)

    public __divint

    mov	a,sp
    add	a,#-2		; 2 bytes return address
    mov	r0,a		; r0 points to yh
    mov	a,@r0		; load yh
    mov	r1,a
    dec	r0
    mov	a,@r0		; load yl
    mov	r0,a

    #define yl      r0
    #define yh      r1

    __divint:			; entry point for __divsint


    #else // C51_STACK_AUTO

    #if defined(C51_NOOVERLAY)
    rseg R_DSEG
    #else
    rseg R_OSEG
    #endif

    public __divuint_PARM_2
    public __divsint_PARM_2

    __divuint_PARM_2:
    __divsint_PARM_2:
    ds	2

    rseg R_CSEG

    #define yl      (__divuint_PARM_2)
    #define yh      (__divuint_PARM_2 + 1)

    #endif // C51_STACK_AUTO
    #endif // C51_PARMS_IN_BANK1

    mov	count,#16
    clr	a
    mov	reste_l,a
    mov	reste_h,a

    loop:
    mov	a,xl		; x <<= 1
    add	a,acc
    mov	xl,a
    mov	a,xh
    rlc	a
    mov	xh,a

    mov	a,reste_l	; reste <<= 1
    rlc	a		;   feed in carry
    mov	reste_l,a
    mov	a,reste_h
    rlc	a
    mov	reste_h,a

    mov	a,reste_l	; reste - y
    subb	a,yl		; here carry is always clear, because
    				; reste <<= 1 never overflows
    mov	b,a
    mov	a,reste_h
    subb	a,yh

    jc	smaller		; reste >= y?

    mov	reste_h,a	; -> yes;  reste = reste - y;
    mov	reste_l,b
    orl	xl,#1
    smaller:			; -> no
    djnz	count,loop
    ret

    __endasm;
}

#else  // defined _DIVUINT_ASM_SMALL || defined _DIVUINT_ASM_SMALL_AUTO

#define MSB_SET(x) ((x >> (8*sizeof(x)-1)) & 1)

unsigned int
_divuint (unsigned int x, unsigned int y)
{
    unsigned int reste = 0;
    unsigned char count = 16;
    BOOL c;

    do
    {
        // reste: x <- 0;
        c = MSB_SET(x);
        x <<= 1;
        reste <<= 1;
        if (c)
            reste |= 1;

        if (reste >= y)
        {
            reste -= y;
            // x <- (result = 1)
            x |= 1;
        }
    }
    while (--count);
    return x;
}

#endif  // defined _DIVUINT_ASM_SMALL || defined _DIVUINT_ASM_SMALL_AUTO
