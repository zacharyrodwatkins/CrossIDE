;
; count.asm: Shows numbers in the seven segment displays of DE2 board
; by Jesus Calvino-Fraga, 2008-2013
;

$MODDE2

CSEG
org 0000H
   ljmp MyProgram

MyProgram:
    mov SP, #7FH ; Set the stack pointer to the begining of idata
    ; Initialize our BCD counter to zero
	MOV R3, #00H 
	MOV R4, #00H
	mov LEDRA, #0
	mov LEDRB, #0
	mov LEDRC, #0
	mov LEDG, #0

forever:
	; Display the 16-bit number stored in R3-R4
	mov a,R4
	anl a,#0FH
	mov dptr,#Disp7Seg
	movc a, @a+dptr
	mov HEX0, a
	
	mov a,R4
	swap a
	anl a,#0FH
	mov dptr,#Disp7Seg
	movc a, @a+dptr
	mov HEX1, a
	
	mov a,R3
	anl a,#0FH
	mov dptr,#Disp7Seg
	movc a, @a+dptr
	mov HEX2, a
	
	mov a,R3
	swap a
	anl a,#0FH
	mov dptr,#Disp7Seg
	movc a, @a+dptr
	mov HEX3, a

	lcall Wait1s
	
	;Increment R3-R4 in BCD!
	mov a, R4
	add a, #1
	da a
	mov R4, a
	mov a, R3
	addc a, #0
	da a
	mov R3, a

    sjmp forever

Wait1s:
	mov R2, #180
L3: mov R1, #250
L2: mov R0, #250
L1: djnz R0, L1 ; 3 machine cycles-> 3*30ns*250=22.5us
	djnz R1, L2 ; 22.5us*250=5.625ms
	djnz R2, L3 ; 5.625ms*180=1s (approximately)
	ret

Disp7Seg:	
	db 0C0H, 0F9H, 0A4H, 0B0H, 099H, 092H, 082H, 0F8H, 080H, 090H
	
END
