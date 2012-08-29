; Vishwanath EE10B035 Shamath EE10B035
; Program to find HCF using conditional execution

	AREA Program, Code, READONLY
	LDR		R0, Num1		; Load the numbers
	MOV		R1, #0x01		; Our result will be stored in this
	LDR		R2, =Result		; Memory address for destination

	PUSH	R0
	PUSH	R1
	BL		Factorial
Return
	POP		R1
	STR		R1, [R2]
	B .

Factorial
	POP		R1
	POP		R0
	MUL		R1, R1, R0
	SUB		R0, R0, #0x01
	CMP		R0, #1
	PUSH	R0
	PUSH	R1
	BEQ		Return
	B 		Factorial		

	AREA INPUT, READONLY
Num1	DCD	&00000001

	AREA OUTPUT, READWRITE
Result	DCD	0

	END