% Vishwanath (EE10B035) Shamanth (EE10B037)
% Program to split a byte, and swap the nibbles
	AREA Program, Code, Readonly

	LDR R0, value1	; Load the number
	LDR R1, mask	; Load the mask
	MOV	R2, R0, LSR #0x04	; Right shift by 4 bits.
							; This will store the higher nibble
	AND R3, R0, R1	; Extract the lower nibble
	MOV	R3, R3, LSL #0x08	; Shift by 8 bits, which moves it to 3rd nibble
	ORR	R4, R2, R3	; The final result is in R4
  
	SWI &11	; Software interrupt

value1 DCB &23	; The byte to be split
	align
mask DCW 0x000F ; The mask to extract one of the nibble
	align
Result DCD 0	; No clue what this does

END
