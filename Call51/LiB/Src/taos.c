/*  _taos.c: common output used used by several conversion programs

    Copyright (C) 2011  Jesus Calvino-Fraga, jesuscf@gmail.com

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

// ~C51~  -c

// These 16 bytes of idata memory are used to return the result.  It is used
// by _ftoa.c, printf_large.c, _ultoa.c, scanf_large.c, etc.
idata char _taos[16]; // To ASCII output string
