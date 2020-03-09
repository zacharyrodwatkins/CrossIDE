/*-------------------------------------------------------------------------
   string.h - ISO header for string library functions

   Written By -  Philipp Klaus Krause . pkk@spth.de (2009)

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
   
-------------------------------------------------------------------------*/


#ifndef __C51_STRING_H
#define __C51_STRING_H 1

#ifndef NULL
# define NULL (void *)0
#endif

#ifndef _SIZE_T_DEFINED
# define _SIZE_T_DEFINED
  typedef unsigned int size_t;
#endif

/* Copying functions: */
extern void *memcpy (void * dest, const void * src, size_t n);
extern void *memmove (void *dest, const void *src, size_t n);
extern char *strcpy (char * dest, const char * src);
extern char *strncpy(char * dest, const char * src, size_t n);

/* Concatenation functions: */
extern char *strcat (char * dest, const char * src);
extern char *strncat(char *  dest, const char * src, size_t n);

/* Comparison functions: */
extern int memcmp (const void *s1, const void *s2, size_t n);
extern int strcmp (const char *s1, const char *s2);
/*inline int strcoll(const char *s1, const char *s2) {return strcmp(s1, s2);}*/
extern int strncmp(const char *s1, const char *s2, size_t n);
/*inline size_t strxfrm(char *dest, const char *src, size_t n) {strncpy(dest, src, n); return strlen(src);}*/

/* Search functions: */
extern void *memchr (const void *s, int c, size_t n);
extern char *strchr (const char *s, char c);
extern size_t strcspn(const char *s, const char *reject);
extern char *strpbrk(const char *s, const char *accept);
extern char *strrchr(const char *s, char c);
extern size_t strspn (const char *s, const char *accept);
extern char *strstr (const char *haystack, const char *needle);
extern char *strtok (char *  str, const char *  delim);

/* Miscanelleous functions: */
extern void *memset (void *s, unsigned char c, size_t n); 
/* extern char *strerror(int errnum); */
extern size_t strlen (const char *s);

#endif

