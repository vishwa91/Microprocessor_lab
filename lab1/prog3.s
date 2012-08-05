; Vishwanath (EE10B035) Shamanth (EE10B037)
; Program to subtract two numbers using 2's compliment

	AREA Program, CODE, READONLY
	ENTRY

Main
	LDR 	R1, num1	; Load the first number
	LDR		R2, num2	; Load the second number
	MVN		R3, R2		; Compliment the second number
	ADD		R3,#0x01	; Add 1 to get 2's compliment
	ADD		R4,R1,R3	; Add the 2's compliment
	SUB		R5,R1,R2	; Subtract directly
	CMP		R4,R5		; Compare the two outputs
	BZ		Done		; If it is same, jump to finish

Done
	NOP
	SWI		&11			; Software interrupt
	END
