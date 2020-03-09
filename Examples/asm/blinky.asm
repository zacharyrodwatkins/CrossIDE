; Blinky.asm: blinks LEDR0 of the DE2-8052 each second.
$MODDE2

org 0000H
	ljmp myprogram

;For a 33.33MHz one clock cycle  takes 30ns
WaitHalfSec:
	mov R2, #90
L3: mov R1, #250
L2: mov R0, #250
L1: djnz R0, L1 ; 3 machine cycles-> 3*30ns*250=22.5us
	djnz R1, L2 ; 22.5us*250=5.625ms
	djnz R2, L3 ; 5.625ms*90=0.5s (approximately)
	ret
	
myprogram:
	mov SP, #7FH
	mov LEDRA,#0
	mov LEDRB,#0
	mov LEDRC,#0
	mov LEDG,#0
M0:
	cpl LEDRA.0
	lcall WaitHalfSec
	sjmp M0
END
