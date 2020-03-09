/*-------------------------------------------------------------------------
   malloc.h - malloc header file

   Written By - Written by Dmitry S. Obukhov, 1997  dso@usa.net

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
/* malloc.h */
#ifndef __C51_MALLOC_H
#define __C51_MALLOC_H
#include <c51-lib.h>
#include <stddef.h>

#if _C51_MALLOC_TYPE_MLH

void * calloc (size_t nmemb, size_t size);
void * malloc (size_t size);
void * realloc (void * ptr, size_t size);
void free (void * ptr);

#else

extern void __xdata * calloc (size_t nmemb, size_t size);
extern void __xdata * malloc (size_t size);
extern void __xdata * realloc (void * ptr, size_t size);
extern void free (void * ptr);

#endif

#endif
