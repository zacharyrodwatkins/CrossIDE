/*  setbaud2.c: Sets the serial port baud rate using timer 2.

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

#define LOW(X)  (X%0x100)
#define HIGH(X) (X/0x100)

__sfr __at (0x98) SCON;
__sfr __at (0xCA) RCAP2L;
__sfr __at (0xCB) RCAP2H;
__sfr __at (0xC8) T2CON;

void setbaud_timer2 (unsigned int reload)
{
	RCAP2H=HIGH(reload);
	RCAP2L=LOW(reload);
	T2CON=0x34; // #00110100B
	SCON=0x52; // Serial port in mode 1, ren, txrdy, rxempty
}
