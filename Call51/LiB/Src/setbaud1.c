/*  setbaud1.c: Sets the serial port baud rate using timer 1.

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

__sfr  __at (0x87) PCON;
__sfr  __at (0x89) TMOD;
__sfr  __at (0x8D) TH1;
__sfr  __at (0x8B) TL1;
__sfr  __at (0x98) SCON;
__sbit __at (0x8E) TR1;

void setbaud_timer1 (unsigned char reload)
{
	TR1=0;
	TMOD=(TMOD&0x0f)|0x20;
	PCON|=0x80;
	TH1=TL1=reload;
	TR1=1;
	SCON=0x52;
}
