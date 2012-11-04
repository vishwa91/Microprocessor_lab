; Vishwanath EE10B035 Shamath EE10B035
; Program to find HCF using conditional execution

	AREA Program, Code, READONLY
	LDR		R0, Num1		; Load the numbers
	MOV		R1, #0x01		; Our result will be stored in this
	LDR		R2, =Result		; Memory address for destination

	STMFD	SP!,{R0, R1}
	BL		Factorial
	LDMFD   SP!,{R0, R1}
	STR		R1, [R2]
	B .

Factorial
	LDMFD	{R0, R1}
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
