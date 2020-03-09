/*  crt0.c: Initialization of stack and variables

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

void dummy_name_crt0 (void) _naked
{
    __asm
    rseg R_GSINIT
    public _crt0
    _crt0:
    mov	sp,#_stack_start-1
    lcall	__c51_external_startup
    mov	a,dpl
    jz	__c51_init_data
    ljmp	__c51_program_startup
    __c51_init_data:

    ; Initialize xdata variables

    mov r0, #(_R_XINIT_start % 0x100)
    mov r1, #(_R_XINIT_start / 0x100)
    mov r2, #(_R_IXSEG_start % 0x100)
    mov r3, #(_R_IXSEG_start / 0x100)
    mov r4, #(_R_IXSEG_size % 0x100)
    mov r5, #(_R_IXSEG_size / 0x100)

    XInitLoop?repeat?:

    mov a, r4
    orl a, r5
    jz XInitLoop?done?
    mov dpl, r0
    mov dph, r1
    clr a
    movc a,@a+dptr
    inc dptr
    mov r0, dpl
    mov r1, dph
    mov dpl, r2
    mov dph, r3
    movx @dptr, a
    inc dptr
    mov r2, dpl
    mov r3, dph
    dec r4
    cjne r4, #0xff, XInitLoop?repeat?
    dec r5
    sjmp XInitLoop?repeat?

    XInitLoop?done?:

    ; Clear xdata variables

    mov dpl, #(_R_XSEG_start % 0x100)
    mov dph, #(_R_XSEG_start / 0x100)
    mov r4, #(_R_XSEG_size % 0x100)
    mov r5, #(_R_XSEG_size / 0x100)

    XClearLoop?repeat?:

    mov a, r4
    orl a, r5
    jz XClearLoop?done?
    clr a
    movx @dptr, a
    inc dptr
    dec r4
    cjne r4, #0xff, XClearLoop?repeat?
    dec r5
    sjmp XClearLoop?repeat?

    XClearLoop?done?:

    ; Clear pdata variables

    mov dpl, #(_R_PSEG_start % 0x100)
    mov dph, #(_R_PSEG_start / 0x100)
    mov r4, #(_R_PSEG_size % 0x100)
    mov r5, #(_R_PSEG_size / 0x100)

    PClearLoop?repeat?:

    mov a, r4
    orl a, r5
    jz PClearLoop?done?
    clr a
    movx @dptr, a
    inc dptr
    dec r4
    cjne r4, #0xff, PClearLoop?repeat?
    dec r5
    sjmp PClearLoop?repeat?

    PClearLoop?done?:

    lcall _R_DINIT_start ; Initialize data variables

    ; Initialize idata variables

    __c51_program_startup:
    lcall	_main
    ;	return from main will lock up
    forever?home?:
    sjmp forever?home?

    __endasm;
}