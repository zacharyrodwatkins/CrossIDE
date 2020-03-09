/*  gets.c: Default gets() using getchar().

    Copyright (C) 2011  Jesus Calvino-Fraga, jesusc (at) ece.ubc.ca

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
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA */

//  ~C51~  -c --model-small

#include <stdio.h>

char * gets(char *s)
{
    char c;
    unsigned int count=0;

    while (1)
    {
        c=getchar(); // Assumes getchar echoes back
        switch(c)
        {
	        case '\b': // backspace
	            if (count)
	            {
	                putchar (' ');
	                putchar ('\b');
	                s--;
	                count--;
	            }
	            break;
	        case '\n':
	        case '\r': // CR or LF
	            *s=0;
	            return s;
	        default:
	            *s++=c;
	            count++;
	            break;
        }
    }
}
