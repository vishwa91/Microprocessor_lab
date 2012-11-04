#include<stdio.h>
#include<math.h>

#define pi 3.1415926
#define NSAMPLES 4
void main()
{
	// We want to create NSAMPLES+1 samples of sine wave between 0-pi/2
	float sineval;
	int i = 0;
	for(i = 0; i < NSAMPLES; i++)
	{
		sineval = sin(i * pi / (2*(NSAMPLES-1)));
		printf("\"MOV\tR1, #%d\\n\\t\"\n\"STR\tR1, [R0]\\n\\t\"\n", (int)(1024*(1 + sineval)*0.4/3.3));
	}
	for(i = NSAMPLES-2; i >= 0; i--)
	{
		sineval = sin(i * pi / (2*(NSAMPLES-1)));
		printf("\"MOV\tR1, #%d\\n\\t\"\n\"STR\tR1, [R0]\\n\\t\"\n", (int)(1024*(1 + sineval)*0.4/3.3));
	}
	for(i = 0; i < NSAMPLES; i++)
	{
		sineval = sin(i * pi / (2*(NSAMPLES-1)));
		printf("\"MOV\tR1, #%d\\n\\t\"\n\"STR\tR1, [R0]\\n\\t\"\n", (int)(1024*(1 - sineval)*0.4/3.3));
	}
	for(i = NSAMPLES-2; i > 0; i--)
	{
		sineval = sin(i * pi / (2*(NSAMPLES-1)));
		printf("\"MOV\tR1, #%d\\n\\t\"\n\"STR\tR1, [R0]\\n\\t\"\n", (int)(1024*(1 - sineval)*0.4/3.3));
	}
}
