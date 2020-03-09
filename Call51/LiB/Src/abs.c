/*-------------------------------------------------------------------------
   abs.c: computes absolute value of an integer.

   Copyright (C) 2009-2011 - Jesus Calvino-Fraga jesusc [at] ece.ubc.ca

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

#include <stdlib.h>

static void dummy(void) __naked
{
    __asm
    public	_abs
_abs:
    mov	a, dph
    jnb	acc.7, ?Done
    cpl a
    mov dph, a
    mov	a,dpl
    cpl a
    mov	dpl,a
    inc dptr
?Done:
    ret
    __endasm;
}

