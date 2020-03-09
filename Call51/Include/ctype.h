/*-------------------------------------------------------------------------
   ctype.h - ANSI functions forward declarations

   Written By -  Sandeep Dutta . sandeep.dutta@usa.net (1998)

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

#ifndef __C51_CTYPE_H
#define __C51_CTYPE_H 1

#include <c51-lib.h>

extern char  iscntrl   (unsigned char )  ;
extern char  isdigit   (unsigned char )  ;
extern char  isgraph   (unsigned char )  ;
extern char  islower   (unsigned char )  ;
extern char  isupper   (unsigned char )  ;
extern char  isprint   (unsigned char )  ;
extern char  ispunct   (unsigned char )  ;
extern char  isspace   (unsigned char )  ;
extern char  isxdigit  (unsigned char )  ;

#define isalnum(c)   (isalpha(c) || isdigit(c))
#define isalpha(c)   (isupper(c) || islower(c))

/* ANSI versions of _tolower & _toupper
#define _tolower(c)  ((c) - ('a' - 'A'))
#define _toupper(c)  ((c) + ('a' - 'A'))
*/

/* The _tolower & _toupper functions below can applied to any
   alpha characters regardless of the case (upper or lower) */
#define _tolower(c)  (char)(((c) |  (char)('a' - 'A')))
#define _toupper(c)  (char)(((c) & ~(char)('a' - 'A')))

#define tolower(c)  ((isupper(c)) ? _tolower(c) : (c))
#define toupper(c)  ((islower(c)) ? _toupper(c) : (c))
#define toascii(c)  ((c) & 0x7F)

#endif
