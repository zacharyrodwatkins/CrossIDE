/*-------------------------------------------------------------------------

  _decdptr.c :-  decrement dptr by 1

             Ecrit par -  Jean-Louis Vern jlvern@writeme.com (1999)

   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the
   Free Software Foundation; either version 2, or (at your option) any
   later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

-------------------------------------------------------------------------*/

/* the return value is already in dph/dpl */
void _decdptr (char *gptr)
{
    gptr; /* hush the compiler */

    __asm
    xch	a,dpl
    jnz     L00001?
    dec	dph
    L00001?:
    dec	a
    xch	a,dpl
    __endasm;
}
