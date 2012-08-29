; Vishwanath EE10B035 Shamanth EE10B037
; Program to find the inner product of two n dimension vectors

	AREA Program, Code, READONLY

	LDR		R0, =TABLEX		; Load the data addresses
	LDR		R1, =TABLEH
	LDR		R2, =RESULT		; Load the destination address
	LDR		R3, LENX		; LENX = LENH, hence no need to load other value
	SUB		R3, #1			; We need to go from n-1 to zero
	
LOOP
	LDR		R4, [R0]		; Load the values
	LDR		R5, [R1]
	MUL		R6, R4, R5		; Multiply and store in R6
	STR		R6, [R2]
	ADD		R0, #4			; Increment all addresses
	ADD		R1, #4			
	ADD		R2, #4
	SUBS	R3, #1			; Decrement the count
	BPL		LOOP

	B .
	AREA INPUT, READONLY

TABLEX	DCD	&00000001
	DCD		&00000002
	DCD		&00000003
	DCD		&00000004
TABLEXEND 	DCD	0

TABLEH	DCD	&00000001
	DCD		&00000002
	DCD		&00000003
	DCD		&00000004
TABLEHEND 	DCD	0

LENX	DCW	(TABLEXEND-TABLEX) / 4
	ALIGN
LENH	DCW (TABLEHEND-TABLEH)/ 4
	ALIGN

	AREA OUTPUT, READWRITE

RESULT	DCD	0

	END