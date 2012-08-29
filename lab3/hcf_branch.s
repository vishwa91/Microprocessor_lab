; Vishwanath EE10B035 Shamath EE10B035
; Program to find HCF using conditional execution

	AREA Program, Code, READONLY
	LDR		R0, Num1		; Load the numbers
	LDR		R1, Num2
	LDR		R2, =Result1	; Destination addresses

loop
	MOV		R3, R0
	CMP		R0, R1			; Compare the two numbers
	BEQ		Done1
	BHI		sub1
	BLT		sub2
sub1
	SUB		R0, R1
	CMP		R0, #0
	BEQ		Done1	; Result is in R1
	B loop
sub2
	SUB		R1, R0
	CMP		R1, #0
	BEQ		Done0	; Result is in R0
	B loop

Done1
	STR		R1, [R2]
	B .
Done0
	STR		R0, [R2]
	B .

	AREA INPUT, READONLY
Num1	DCD		&00000060
Num2	DCD		&00000004

	AREA OUTPUT, READWRITE

Result1	DCD		0

	END