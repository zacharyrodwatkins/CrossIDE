/*-------------------------------------------------------------------------
   stdio.h - ANSI functions forward declarations

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

#ifndef __C51_STDIO_H
#define __C51_STDIO_H 1

#include <stdarg.h>

#include <c51-lib.h>

#ifndef NULL
  #define NULL (void *)0
#endif

#ifndef _SIZE_T_DEFINED
#define _SIZE_T_DEFINED
  typedef unsigned int size_t;
#endif

typedef void (*pfn_outputchar)(char c);

extern int _print_format (pfn_outputchar pfn, const char *format, va_list ap);

typedef char (*pfn_inputchar)(void);

extern int _scan_format (pfn_inputchar pfn, const char *format, va_list ap);

/*-----------------------------------------------------------------------*/

extern void printf_small (char *,...) _REENTRANT;
extern int printf (const char *,...);
extern int vprintf (const char *, va_list);
extern int sprintf (char *, const char *, ...);
extern int vsprintf (char *, const char *, va_list);
extern int scanf (const char *,...);
extern int vscanf (const char *, va_list);
extern int sscanf (char *, const char *, ...);
extern int vsscanf (char *, const char *, va_list);

extern int puts(const char *);
extern char *gets(char *);
extern char getchar(void);
extern void putchar(char);
extern void setbaud_timer1 (unsigned char reload);
extern void setbaud_timer2 (unsigned int reload);

#if !defined(C51_USE_XSTACK)
extern void printf_fast(__code const char *fmt, ...) _REENTRANT;
extern void printf_fast_f(__code const char *fmt, ...) _REENTRANT;
extern void printf_tiny(__code const char *fmt, ...) _REENTRANT; 
#endif

#endif /* __SDC51_STDIO_H */
