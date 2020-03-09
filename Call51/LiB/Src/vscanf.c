/*-------------------------------------------------------------------------
  vscanf.c - formatted input conversion

   CopyRight (c) Jesus Calvino-Fraga (2011)

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

#include <stdarg.h>
#include <stdio.h>

static char get_char_from_stdin( void ) _REENTRANT
{
	char c;
    c=getchar();
    if(c== '\b') // backspace?
    {
        putchar (' ');
        putchar ('\b');
    }
    return(c);
}

int vscanf (const char *format, va_list ap)
{
    return _scan_format( get_char_from_stdin, format, ap );
}

int scanf (const char *format, ...)
{
    va_list arg;
    int i;

    va_start (arg, format);
    i = _scan_format( get_char_from_stdin, format, arg );
    va_end (arg);

    return i;
}
