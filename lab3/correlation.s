; Vishwanath EE10B035 Shamanth EE10B037
; Program to find the correlation of two n dimension arrays

	AREA Program, Code, READONLY

	LDR		R0, =TABLEX		; Load the data addresses
	LDR		R1, =TABLEH
	LDR		R2, =RESULT		; Load the destination address
	LDR		R3, LENX		; LENX = LENH, hence no need to load other value
	SUB		R3, #1			; We need to go from n-1 to zero
	MOV		R7, R1			; Another copy of address for second loop
	MOV		R8, R3		  	; 
	MOV		R9,	R0
	
loop1
	MOV		R1, R7
	MOV		R6, #0			; Clear R6. This stores the temporary sum in each iter
	MOV		R3, R8
	MOV		R0, R9
LOOP
	LDR		R4, [R0]		; Load the values
	LDR		R5, [R1]
	MLA		R6, R4, R5, R6		; Multiply and store in R6
	
	ADD		R0, #4			; Increment all addresses
	ADD		R1, #4			
	
	SUBS	R3, #1			; Decrement the count
	BPL		LOOP
	STR		R6, [R2]
	ADD		R2, #4
	ADD		R7, #4
	SUBS	R8, #1
	BPL 	loop1

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