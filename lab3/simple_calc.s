; Vishwanath EE10B035 Shamath EE10B035
; Program to evaluate (291*x + 5)/16 and 595*x + 19

	AREA Program, Code, READONLY
	LDR		R0, Num1		; Load the numbers
	LDR		R1, Num2
	LDR		R2, =Result1		; Destination addresses
	LDR		R3, =Result2
	MOV		R4, #0			
	MOV		R5, #0

	ADD		R4, R0, R0, LSL #0x08	; 291*x = 256x + 32x + 2x + x
	ADD		R4, R4, R0, LSL #0x05
	ADD		R4, R4, R0, LSL #0x01
	
	ADD		R4, R4, #0x05
	MOV		R4, R4, LSR #0x04		; x / 16 = x << 4
	STR		R4, [R2]
	 
	ADD		R5, R1, R1, LSL #0x09	; 595*x = 512x + 64x + 16x + 2x + x
	ADD		R5, R5, R1, LSL #0x06
	ADD		R5, R5, R1, LSL #0x04
	ADD		R5, R5, R1, LSL #0x01
	
	ADD		R5, R5, #0x13
	STR		R5, [R3]

	B .
	

	AREA INPUT, READONLY
Num1	DCD		&00000001
Num2	DCD		&00000001

	AREA OUTPUT, READWRITE

Result1	DCD		0
Result2	DCD		0

	END