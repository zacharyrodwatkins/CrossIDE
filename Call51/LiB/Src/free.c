/*-------------------------------------------------------------------------
   free.c - release allocated memory.

   Copyright (C) 2004 - Maarten Brock, sourceforge.brock@dse.nl

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

#include <c51-lib.h>
#include <malloc.h>

#if defined(C51_STACK_AUTO) || defined(C51_z80) || defined(C51_gbz80)
#define CRITICAL __critical
#else
#define CRITICAL
#endif

#if _C51_MALLOC_TYPE_MLH

typedef struct _MEMHEADER MEMHEADER;

struct _MEMHEADER
{
    MEMHEADER *    next;
    MEMHEADER *    prev;
    unsigned int   len;
    unsigned char  mem;
};

#define HEADER_SIZE (sizeof(MEMHEADER)-sizeof(char))

/* These variables are defined through the crt0 functions. */
/* Base of this variable is the first byte of the heap. */
extern MEMHEADER _c51_heap_start;
/* Address of this variable is the last byte of the heap. */
extern char _c51_heap_end;

MEMHEADER * _c51_prev_memheader;
// apart from finding the header
// this function also finds it's predecessor
MEMHEADER *
_c51_find_memheader(void * p)
{
    register MEMHEADER * pthis;
    if (!p)
        return NULL;
    pthis = (MEMHEADER * )((char *)  p - HEADER_SIZE); //to start of header
    _c51_prev_memheader = pthis->prev;

    return (pthis);
}

void
free (void *p)
{
    MEMHEADER *prev_header, *pthis;

    if ( p ) //For allocated pointers only!
        CRITICAL
    {
        pthis = (MEMHEADER * )((char *)  p - HEADER_SIZE); //to start of header
        if ( pthis->prev ) // For the regular header
        {
            prev_header = pthis->prev;
            prev_header->next = pthis->next;
            if (pthis->next)
            {
                pthis->next->prev = prev_header;
            }
        }
        else
        {
            pthis->len = 0; //For the first header
        }
    }
}

#else

//--------------------------------------------------------------------
//Written by Dmitry S. Obukhov, 1997
//dso@usa.net
//--------------------------------------------------------------------
//Modified for C51 by Sandeep Dutta, 1999
//sandeep.dutta@usa.net
//--------------------------------------------------------------------
//malloc and free functions implementation for embedded system
//Non-ANSI keywords are C51 specific.
// __xdata - variable in external memory (just RAM)
//--------------------------------------------------------------------

#define MEMHEADER   struct MAH// Memory Allocation Header

MEMHEADER
{
    MEMHEADER __xdata *  next;
    unsigned int         len;
    unsigned char        mem[];
};

#define HEADER_SIZE sizeof(MEMHEADER)

//Static here means: can be accessed from this module only
extern MEMHEADER __xdata * _c51_first_memheader;

MEMHEADER __xdata * _c51_prev_memheader;
// apart from finding the header
// this function also finds it's predecessor
MEMHEADER __xdata * _c51_find_memheader(void __xdata * p)
{
    register MEMHEADER __xdata * pthis;
    register MEMHEADER __xdata * cur_header;

    if (!p)
        return NULL;
    pthis = (MEMHEADER __xdata *) p;
    pthis -= 1; //to start of header
    cur_header = _c51_first_memheader;
    _c51_prev_memheader = NULL;
    while (cur_header && pthis != cur_header)
    {
        _c51_prev_memheader = cur_header;
        cur_header = cur_header->next;
    }
    return (cur_header);
}

void free (void * p)
{
    register MEMHEADER __xdata * pthis;

    CRITICAL
    {
        pthis = _c51_find_memheader(p);
        if (pthis) //For allocated pointers only!
        {
            if (!_c51_prev_memheader)
            {
                pthis->len = 0;
            }
            else
            {
                _c51_prev_memheader->next = pthis->next;
            }
        }
    }
}
//END OF MODULE
#endif
