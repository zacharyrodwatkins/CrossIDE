/*-------------------------------------------------------------------------
  print_format.c - formatted output conversion

		 Written By - Martijn van Balen aed@iae.nl (1999)
		 Floating point support by - Jesus Calvino-Fraga (2011)

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
// ~C51~  -c -DUSE_FLOATS --model-medium

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <c51-lib.h>

#pragma overlayto ?lib?dseg?1

#define PTR value.ptr

#define ptr_t const char *

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

#define toupper(c) ((c)&=0xDF)
#define tolower(c) ((c)|=0x20)
#define islower(c) ((unsigned char)c >= (unsigned char)'a' && (unsigned char)c <= (unsigned char)'z')
#define isdigit(c) ((unsigned char)c >= (unsigned char)'0' && (unsigned char)c <= (unsigned char)'9')

#define DEFAULT_FLOAT_PRECISION 6


#ifdef C51_STACK_AUTO
#define data
#define idata
#endif

typedef union
{
    unsigned char  byte[5];
    long           l;
    unsigned long  ul;
    float          f;
    const char     *ptr;
    int *iptr;
} value_t;

static pfn_outputchar output_char;
static value_t value;
static int charsOutputted;
static unsigned char radix;
static unsigned char  width;
static signed char decimals;
static unsigned char  length;
static unsigned char i;

static BOOL   lower_case;
static BOOL   f_argument;
static BOOL   e_argument;
static BOOL   g_argument;
static BOOL   left_justify;
static BOOL   zero_padding;
static BOOL   prefix_sign;
static BOOL   prefix_space;
static BOOL   signed_argument;
static BOOL   char_argument;
static BOOL   long_argument;
static BOOL   pound_argument;
static BOOL   lsd;
static BOOL   fflag;

#define OUTPUT_CHAR(c) _output_char (c)
static void _output_char( unsigned char c )
{
    output_char( c);
    charsOutputted++;
}

static void output_digit( unsigned char n )
{
    register unsigned char c = n + (unsigned char)'0';

    if (c > (unsigned char)'9')
    {
        c += (unsigned char)('A' - '0' - 10);
        if (lower_case)
            c = tolower(c);
    }
    _output_char( c );
}

#define OUTPUT_2DIGITS( B )   output_2digits( B )
static void output_2digits( unsigned char b )
{
    output_digit( b>>4   );
    output_digit( b&0x0F );
}


static void calculate_digit( void )
{
    register unsigned long ul = value.ul;
    register unsigned char b4 = value.byte[4];
    
    i = 32;

    do
    {
        b4 = (b4 << 1);
        b4 |= (ul >> 31) & 0x01;
        ul <<= 1;

        if (radix <= b4 )
        {
            b4 -= radix;
            ul |= 1;
        }
    }
    while (--i);
    value.ul = ul;
    value.byte[4] = b4;
}

#if USE_FLOATS

#define DEFAULT_FLOAT_PRECISION 6
#define reqWidth width
#define reqDecimals decimals
#define left left_justify
#define zero zero_padding
#define sign prefix_sign
#define space prefix_space

extern idata char _taos[16]; // To ASCII output string used by _ftoa()

static void output_f (void)
{
	#define minWidth radix
    signed char exp;

    exp=(_taos[12]-'0')*10+(_taos[13]-'0');
    if(_taos[11]=='-') exp*=-1;
    minWidth=1;

    if(exp>0)
    {
        for(i=3; i<10; i++)
        {
            minWidth++;
            _taos[i-1]=_taos[i];
            _taos[i]='.';
            exp--;
            if(exp==0) break;
        }
    }

    if(exp<0)
    {
        _taos[2]=_taos[1];
        _taos[1]='.';
        exp++;
    }

    if(reqDecimals)
    {
    	minWidth+=reqDecimals+1;
    }
    else
    {
    	if(pound_argument) minWidth++;
    }
    
    if ((_taos[0]=='-') || sign || space) minWidth++;

    if (!left)
    {
        if (zero)
        {
            if (_taos[0]=='-')  OUTPUT_CHAR('-');
            else if (sign)  OUTPUT_CHAR('+');
            else if (space) OUTPUT_CHAR(' ');

            if (_taos[1]=='.')
            {
                OUTPUT_CHAR('0');
                reqWidth--;
            }

            while (reqWidth-->minWidth) OUTPUT_CHAR('0');
        }
        else
        {
            while (reqWidth-->minWidth) OUTPUT_CHAR(' ');

            if (_taos[0]=='-')  OUTPUT_CHAR('-');
            else if (sign)  OUTPUT_CHAR('+');
            else if (space) OUTPUT_CHAR(' ');

            if (_taos[1]=='.')
            {
                OUTPUT_CHAR('0');
                reqWidth--;
            }
        }
    }
    else // Left aligment
    {
        if (_taos[0]=='-')
        {
            OUTPUT_CHAR('-');
            reqWidth--;
        }
        else if (sign)
        {
            OUTPUT_CHAR('+');
            reqWidth--;
        }
        else if (space)
        {
            OUTPUT_CHAR(' ');
            reqWidth--;
        }

        if (_taos[1]=='.')
        {
            OUTPUT_CHAR('0');
            reqWidth--;
        }
    }

    // output the number
    for(i=1, fflag=0; _taos[i]!='E'; i++)
    {
        if(_taos[i]=='.')
        {
        	while(exp>0)
        	{
        		OUTPUT_CHAR ('0');
        		exp--;
        	}
            fflag=1;
            if(reqDecimals==0) 
            {
            	if(pound_argument)
            		OUTPUT_CHAR ('.');
            	break;
            }
        }
        else if (fflag)
        {
         	while(exp<0)
        	{
        		if(reqDecimals>0)
        		{
	        		OUTPUT_CHAR ('0');
	            	reqDecimals--;
            	}
            	exp++;
            }
        }
        if((fflag==0) || (reqDecimals>0) )
        {
       		OUTPUT_CHAR (_taos[i]);
       		if((fflag)&&(_taos[i]!='.')) reqDecimals--;
       	}
        reqWidth--;
        if((reqDecimals<=0) && (fflag)) break;
    }

    while(reqDecimals>0)
    {
        OUTPUT_CHAR('0');
        reqDecimals--;
    }

    if (left)
    {
        while (reqWidth--)
        {
            OUTPUT_CHAR(' ');
        }
    }
}

static void output_e (void)
{
	if( (reqDecimals) || (pound_argument) )
	{
		reqWidth-=(7+reqDecimals);
	}
	else
	{
		reqWidth-=6; // No decimal point or decimals
	}
	
	i=0;
	if( (_taos[0]=='+') && (!sign) )
	{
		_taos[0]=' ';
		if (!space)
		{
			i++;
			reqWidth++;
		}
	}
		
	if(!left)
	{
		while( ((char)reqWidth)>0 ) // reqWidth is unsigned
		{
			OUTPUT_CHAR(' ');
			reqWidth--;
		}
	}
	
    for(fflag=0; _taos[i]!=0; i++)
    {
        if(_taos[i]=='E')
        {
        	if(lower_case) _taos[i]='e';
            while(reqDecimals>0)
		    {
		        OUTPUT_CHAR('0');
		        reqDecimals--;
		    }
            fflag=1;
        }
        if( (i<2) || ( (i>=2) && (reqDecimals>0) ) || (fflag) )
        {
       		OUTPUT_CHAR (_taos[i]);
       		if(i>2) reqDecimals--;
       	}
       	else
       	{
       		if((i==2) && (pound_argument))
      			OUTPUT_CHAR ('.');
       	}
    }
    
	if(left)
	{
		while( ((char)reqWidth)>0 ) // reqWidth is unsigned
		{
			OUTPUT_CHAR(' ');
			reqWidth--;
		}
	}
    
}
#endif //USE_FLOATS

int _print_format (pfn_outputchar pfn, const char *format, va_list ap)
{
    char c;
    output_char = pfn;

    // reset output chars
    charsOutputted = 0;

    while( c=*format++ )
    {
        if ( c=='%' )
        {
            left_justify    = 0;
            zero_padding    = 0;
            prefix_sign     = 0;
            prefix_space    = 0;
            signed_argument = 0;
            char_argument   = 0;
            long_argument   = 0;
            pound_argument  = 0;
            f_argument      = 0;
            e_argument      = 0;
            g_argument      = 0;
            radix           = 0;
            width           = 0;
            decimals        = -1;

get_conversion_spec:

            c = *format++;

            if (c=='%')
            {
                OUTPUT_CHAR(c);
                continue;
            }

            if (isdigit(c))
            {
                if (decimals==-1)
                {
                    width = 10*width + (c - '0');
                    if (width == 0)
                    {
                        /* first character of width is a zero */
                        zero_padding = 1;
                    }
                }
                else
                {
                    decimals = 10*decimals + (c-'0');
                }
                goto get_conversion_spec;
            }

            if (c=='.')
            {
                if (decimals==-1) decimals=0;
                else
                    ; // duplicate, ignore
                goto get_conversion_spec;
            }

            if (islower(c))
            {
                c = toupper(c);
                lower_case = 1;
            }
            else
                lower_case = 0;

            switch( c )
            {
            case '-':
                left_justify = 1;
                goto get_conversion_spec;
            case '+':
                prefix_sign = 1;
                goto get_conversion_spec;
            case ' ':
                prefix_space = 1;
                goto get_conversion_spec;
            case 'B':
                char_argument = 1;
                goto get_conversion_spec;
            case 'L':
                long_argument = 1;
                goto get_conversion_spec;
            case '#':
            	pound_argument = 1;
            	goto get_conversion_spec;
            case '*':
            	if(decimals==-1)
            	{
	                if( char_argument )
	                    width = va_arg(ap,char);
	                else
	                    width = va_arg(ap,int);
                }
                else
                {
	                if( char_argument )
	                    decimals = va_arg(ap,char);
	                else
	                    decimals = va_arg(ap,int);
                }
            	goto get_conversion_spec;

            case 'C':
                if( char_argument )
                    c = va_arg(ap,char);
                else
                    c = va_arg(ap,int);
                OUTPUT_CHAR( c );
                break;

            case 'S':
                PTR = va_arg(ap,ptr_t);

                length = strlen(PTR);
                if ( decimals == -1 )
                {
                    decimals = length;
                }
                if ( ( !left_justify ) && (length < width) )
                {
                    width -= length;
                    while( width-- != 0 )
                    {
                        OUTPUT_CHAR( ' ' );
                    }
                }

                while ( (c = *PTR)  && (decimals-- > 0))
                {
                    OUTPUT_CHAR( c );
                    PTR++;
                }

                if ( left_justify && (length < width))
                {
                    width -= length;
                    while( width-- != 0 )
                    {
                        OUTPUT_CHAR( ' ' );
                    }
                }
                break;

            case 'P':
                PTR = va_arg(ap,ptr_t);
                {
                    unsigned char memtype = value.byte[2];
                    if (memtype & 0x80)
                        c = 'C';
                    else if (memtype & 0x60)
                        c = 'P';
                    else if (memtype & 0x40)
                        c = 'I';
                    else
                        c = 'X';
                }
                OUTPUT_CHAR(c);
                OUTPUT_CHAR(':');
                OUTPUT_CHAR('0');
                OUTPUT_CHAR('x');
                if ((c != 'I' /* idata */) && (c != 'P' /* pdata */))
                {
                    OUTPUT_2DIGITS( value.byte[1] );
                }
                OUTPUT_2DIGITS( value.byte[0] );
                break;

            case 'D':
            case 'I':
                signed_argument = 1;
                radix = 10;
                break;

            case 'O':
                radix = 8;
                break;

            case 'U':
                radix = 10;
                break;

            case 'X':
                radix = 16;
                break;

            case 'F':
                f_argument=1;
                break;

            case 'E':
                e_argument=1;
                break;

            case 'G':
                g_argument=1;
                break;
                
            case 'N':
                value.iptr = va_arg(ap,int *);
            	*value.iptr= charsOutputted;
            	break;
                
            default:
                // nothing special, just output the character
                OUTPUT_CHAR( c );
                break;
            }

            if ( (f_argument) || (e_argument) || (g_argument))
            {
                value.f=va_arg(ap,float);
#if !USE_FLOATS
                PTR="<NO FLOAT>";
                while (c=*PTR++) OUTPUT_CHAR (c);
#else
				_ftoa(value.f);
    			// display some decimals as default
				if (reqDecimals==-1) reqDecimals=DEFAULT_FLOAT_PRECISION;

				if(g_argument)
				{
					#define fexp value.byte[4]
					fexp=value.byte[3]&0x7F; // Get the float exponent
					fexp<<=1;
					if(value.byte[2]&0x80) fexp|=0x01;
					
					if( (fexp>(127+24)) || (fexp<(127-24)) )
					{
						e_argument=1;
					}
				}
                if(e_argument)
                {
                    output_e();
                }
                else
                {
                    output_f();
                }
#endif //USE_FLOATS
            }
            else if (radix != 0)
            {
            	#ifdef USE_FLOATS
                #define store _taos
                #else
                unsigned char idata store[6];
                #endif
                unsigned char idata *pstore = &store[5];
                
                // store value in byte[0] (LSB) ... byte[3] (MSB)
                if (char_argument)
                {
                    value.l = va_arg(ap,char);
                    if (!signed_argument)
                    {
                        value.l &= 0xFF;
                    }
                }
                else if (long_argument)
                {
                    value.l = va_arg(ap,long);
                }
                else // must be int
                {
                    value.l = va_arg(ap,int);
                    if (!signed_argument)
                    {
                        value.l &= 0xFFFF;
                    }
                }
                
                if( (pound_argument) && (value.l!=0) )
                {
                	if(radix==8)
                	{
                		OUTPUT_CHAR( '0' );
                	}
                	else if (radix==16)
                	{
               			OUTPUT_CHAR( '0' );
                		if(lower_case)
                			OUTPUT_CHAR( 'x' );
                		else
                			OUTPUT_CHAR( 'X' );
                	}
                }

                if ( signed_argument )
                {
                    if (value.l < 0)
                        value.l = -value.l;
                    else
                        signed_argument = 0;
                }

                length=0;
                lsd = 1;

                do
                {
                    value.byte[4] = 0;
                    calculate_digit();
                    if (!lsd)
                    {
                        *pstore = (value.byte[4] << 4) | (value.byte[4] >> 4) | *pstore;
                        pstore--;
                    }
                    else
                    {
                        *pstore = value.byte[4];
                    }
                    length++;
                    lsd = !lsd;
                }
                while( value.ul );

                if (width == 0)
                {
                    // default width. We set it to 1 to output
                    // at least one character in case the value itself
                    // is zero (i.e. length==0)
                    width=1;
                }

                /* prepend spaces if needed */
                if (!zero_padding && !left_justify)
                {
                    while ( width > (unsigned char) (length+1) )
                    {
                        OUTPUT_CHAR( ' ' );
                        width--;
                    }
                }

                if (signed_argument) // this now means the original value was negative
                {
                    OUTPUT_CHAR( '-' );
                    // adjust width to compensate for this character
                    width--;
                }
                else if (length != 0)
                {
                    // value > 0
                    if (prefix_sign)
                    {
                        OUTPUT_CHAR( '+' );
                        // adjust width to compensate for this character
                        width--;
                    }
                    else if (prefix_space)
                    {
                        OUTPUT_CHAR( ' ' );
                        // adjust width to compensate for this character
                        width--;
                    }
                }

                /* prepend zeroes/spaces if needed */
                if (!left_justify)
                    while ( width-- > length )
                    {
                        OUTPUT_CHAR( zero_padding ? '0' : ' ' );
                    }
                else
                {
                    /* spaces are appended after the digits */
                    if (width > length)
                        width -= length;
                    else
                        width = 0;
                }

                /* output the digits */
                while( length-- )
                {
                    lsd = !lsd;
                    if (!lsd)
                    {
                        pstore++;
                        value.byte[4] = *pstore >> 4;
                    }
                    else
                    {
                        value.byte[4] = *pstore & 0x0F;
                    }
                    output_digit( value.byte[4] );
                }
                if (left_justify)
                {
                    while (width-- > 0)
                    {
                        OUTPUT_CHAR(' ' );
                    }
                }
            }
        }
        else
        {
            // nothing special, just output the character
            OUTPUT_CHAR( c );
        }
    }

    return charsOutputted;
}
