; Vishwanath (EE10B035) Shamanth (EE10B037)
; Program to find the maximum of 3 numbers

	AREA test,code,readonly
	MOV 	R1,#10		; Move the first number to R1
	MOV		R2,#8		; Second number in R2
	MOV		R3,#5		; Third number in R3
	LDR 	R4,Result	; Result is the final register
	CMP		R1,R2 		; Compare first two numbers
	BHI		Done1		; Jump to Done1 if R1>R2
	MOV		R1,R2		; If R2>R1, move R2 to R1

Done1
	CMP		R1,R3		; Compare the greater number and the third number
	BHI		Done2		; Do nothing if R1 is greatest
	MOV		R1,R3		; Move R3 to R1 if R3 is greatest

Done2
	STR		R1,[R4]		; Store the result in memory
	SWI		&11			; Software interrupt

Result DCD 0x40000000
	END
