; Add32.asm: shows how to add two 32-bit numbers at RAM
; addresses 30H and 34H and place result at XRAM address
; 100H

$MOD52

org 0000H
	ljmp myprogram

DSEG at 30H

Num1:	DS	4
Num2:	DS	4

XSEG at 100H
Result:	DS	4

CSEG
myprogram:
	mov SP, #80H

; Make Num1=55555555H for testing
	mov R0, #Num1
L1:	mov @R0, #55H
	inc R0
	cjne R0, #Num1+4, L1

; Make Num1=66666666H for testing
	mov R1, #Num2
L2:	mov @R1, #66H
	inc R1
	cjne R1, #Num2+4, L2	

; Initialize pointers
	mov R0, #Num1
	mov R1, #Num2
	mov DPTR, #Result

	clr c
	mov R2, #4
; Add the bytes, one by one
L3:	mov A, @R0
	addc A, @R1
	movx @dptr, A
	inc R0
	inc R1
	inc dptr
	djnz R2, L3
	
; Done!  Loop forever	
forever:
	sjmp forever
END
