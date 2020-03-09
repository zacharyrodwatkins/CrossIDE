/*  atof.c: converts an ASCII string to float

    Copyright (C) 2003-2011  Jesus Calvino-Fraga, jesusc (at) ece.ubc.ca

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

#include <ctype.h>
#include <stdlib.h>

// Since this function is called from scanf_format which uses ?lib?dseg?1, we
// need to use a different overlay data segment:

#pragma overlayto ?lib?dseg?2

#ifdef toupper
#undef toupper
#endif
#ifdef tolower
#undef tolower
#endif
#ifdef islower
#undef islower
#endif
#ifdef isdigit
#undef isdigit
#endif
#ifdef isspace
#undef isspace
#endif

#define toupper(c) ((c)&=0xDF)
#define tolower(c) ((c)|=0x20)
#define islower(c) ((unsigned char)c >= (unsigned char)'a' && (unsigned char)c <= (unsigned char)'z')
#define isdigit(c) ((unsigned char)c >= (unsigned char)'0' && (unsigned char)c <= (unsigned char)'9')
#define isspace(c) (((unsigned char)c == (unsigned char)' ') || ((unsigned char)c == (unsigned char)'\t'))

float atof(char * s)
{
	// Making this variables volatile results in significant data space saving in the small
	// compile mode.
    volatile float value;
    volatile char iexp_off=0;
    volatile char iexp=0;
    bit sign, esign, dot_flag=0;

    //Skip leading blanks
    while (isspace(*s)) s++;

    //Get the sign
    if (*s == '-')
    {
        sign=1;
        s++;
    }
    else
    {
        sign=0;
        if (*s == '+') s++;
    }

    //Get the number
    for (value=0.0; isdigit(*s) || (*s == '.'); s++)
    {
    	if(*s == '.') 
    	{
    		dot_flag=1;
    	}
    	else
    	{
	        value=10.0*value;
	        value+=(*s-'0');
	        if(dot_flag) iexp_off--;
	    }
    }

    //Finally, the exponent
    if (toupper(*s)=='E')
    {
        s++;
	    //Get the exponent sign
	    if (*s == '-')
	    {
	        esign=1;
	        s++;
	    }
	    else
	    {
	        esign=0;
	        if (*s == '+') s++;
	    }

	    for (iexp=0; isdigit(*s); s++)
	    {
	        iexp=10*iexp;
	        iexp+=(*s-'0');
	    }
        if(esign) iexp*=-1;
  	}
  	     
    iexp+=iexp_off;
    while(iexp!=0)
    {
        if(iexp<0)
        {
            value*=0.1;
            iexp++;
        }
        else
        {
            value*=10.0;
            iexp--;
        }
    }

    if(sign) value*=-1.0;
    return (value);
}
