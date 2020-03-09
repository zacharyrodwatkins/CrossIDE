/*-----------------------------------------------------------------------------------*/
/* stdarg.h - ANSI macros for variable parameter list                                */
/*-----------------------------------------------------------------------------------*/

#ifndef __C51_STDARG_H
#define __C51_STDARG_H 1


#if defined(C51_USE_XSTACK)

typedef unsigned char __pdata * va_list;
#define va_start(marker, first) { marker = (va_list)&first; }
#define va_arg(marker, type)    *((type __pdata *)(marker -= sizeof(type)))

#else

typedef unsigned char __data * va_list;
#define va_start(marker, first) { marker = (va_list)&first; }
#define va_arg(marker, type)    *((type __data * )(marker -= sizeof(type)))

#endif

#define va_end(marker) marker = (va_list) 0;

#endif
