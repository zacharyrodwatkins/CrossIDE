/** \file compiler.h
  * \author Maarten Brock
  *
  * This library is free software; you can redistribute it and/or
  * modify it under the terms of the GNU Lesser General Public
  * License as published by the Free Software Foundation; either
  * version 2.1 of the License, or (at your option) any later version.
  *
  * This library is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  * Lesser General Public License for more details.
  *
  * You should have received a copy of the GNU Lesser General Public
  * License along with this library; if not, write to the Free Software
  * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
  *
  * In other words, you are welcome to use, share and improve this program.
  * You are forbidden to forbid anyone else to use, share and improve
  * what you give them. Help stamp out software-hoarding!
  *
 */

#ifndef COMPILER_H
#define COMPILER_H

# define SBIT(name, addr, bit)  __sbit  __at(addr+bit)                    name
# define SFR(name, addr)        __sfr   __at(addr)                        name
# define SFRX(name, addr)       __xdata volatile unsigned char __at(addr) name
# define SFR16(name, addr)      __sfr16 __at(((addr+1U)<<8) | addr)       name
# define SFR16E(name, fulladdr) __sfr16 __at(fulladdr)                    name
# define SFR32(name, addr)      __sfr32 __at(((addr+3UL)<<24) | ((addr+2UL)<<16) | ((addr+1UL)<<8) | addr) name
# define SFR32E(name, fulladdr) __sfr32 __at(fulladdr)                    name


#endif //COMPILER_H
