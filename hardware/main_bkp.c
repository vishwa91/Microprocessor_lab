#include "LPC23xx.h"

/**********************************************************************************************************
			Routine to set processor and peripheral clock 
***********************************************************************************************************/
void  TargetResetInit(void)
{
  // 72 Mhz Frequency
  if ((PLLSTAT & 0x02000000) > 0)
  {
      /* If the PLL is already running   */
      PLLCON  &= ~0x02;                         /* Disconnect the PLL                                       */
      PLLFEED  =  0xAA;                        	/* PLL register update sequence, 0xAA, 0x55                 */
      PLLFEED  =  0x55;
  }
  PLLCON   &= ~0x01;                            /* Disable the PLL                                          */
  PLLFEED   =  0xAA;                           	/* PLL register update sequence, 0xAA, 0x55                 */
  PLLFEED   =  0x55;
  SCS      &= ~0x10;                         	/* OSCRANGE = 0, Main OSC is between 1 and 20 Mhz           */
  SCS      |=  0x20;                         	/* OSCEN = 1, Enable the main oscillator                    */
  while ((SCS &  0x40) == 0);
  CLKSRCSEL = 0x01;                         	/* Select main OSC, 12MHz, as the PLL clock source          */
  PLLCFG    = (24 << 0) | (1 << 16);         	/* Configure the PLL multiplier and divider                 */   
  PLLFEED   = 0xAA;                         	/* PLL register update sequence, 0xAA, 0x55                 */
  PLLFEED   = 0x55;
  PLLCON   |= 0x01;                        		/* Enable the PLL                                           */
  PLLFEED   = 0xAA;                        		/* PLL register update sequence, 0xAA, 0x55                 */
  PLLFEED   = 0x55;
  CCLKCFG   = 3;                        		/* Configure the ARM Core Processor clock divider           */
  USBCLKCFG = 5;                    			/* Configure the USB clock divider                          */
  while ((PLLSTAT & 0x04000000) == 0);  
  PCLKSEL0  = 0xAAAAAAAA;                     	/* Set peripheral clocks to be half of main clock           */
  PCLKSEL1  = 0x22AAA8AA;
  PLLCON   |= 0x02;                         	/* Connect the PLL. The PLL is now the active clock source  */
  PLLFEED   = 0xAA;                          	/* PLL register update sequence, 0xAA, 0x55                 */
  PLLFEED   = 0x55;
  while ((PLLSTAT & 0x02000000) == 0);  
  PCLKSEL0 = 0x55555555;  		     			/* PCLK is the same as CCLK */
  PCLKSEL1 = 0x55555555;  
}
// delay routine 
static void delay(void)
{
	unsigned int i,j;
	for(i=0;i<0xff;i++)
	 for(j=0;j<0x3ff;j++);
}

void rotate(void)
{
	FIO3DIR	= 0xFF;
	FIO3PIN	= 0x01; 		// Our initial pin configuration
	int i;
	int tempnum = 0x01;
	while(1)
	{
		tempnum = 0x01; 
		for (i = 0; i < 8; i++ )
		{
			delay();
			delay();
			FIO3PIN = tempnum << i;
		}
			
	}
}
void rotate1(void)
{
	FIO3DIR	= 0xFF;
	FIO3PIN	= 0x01; 		// Our initial pin configuration
	int i = 0;
	int tempnum = 0x80;
	while(1)
	{
		FIO3PIN	= tempnum;
		
		delay();
		delay();
		tempnum = (0x80 >> i) + (1<<i) ;
		i += 1;
		if(tempnum==0)
		{
			i = 0;
			tempnum = 0x80;
		}
					
	}
}

void four_bit_add(void)
{
	FIO3DIR = 0xFF;
	FIO4DIR = 0x00;
	
	int num1, num2, result, mask1, mask2;
	mask1 = 0x0f;
	mask2 = 0xf0;
	
	while(1)
	{
		num1 = mask1 & FIO4PIN;
		num2 = mask2 & FIO4PIN;
		num2 = num2 >> 4;
		result = num1 + num2;
		if (result > 9)
			result += 6;
		FIO3PIN = result;
	}
}

void reflect(void)
{
	FIO3DIR = 0xff;
	FIO4DIR = 0x00;
	while(1)
		FIO3PIN = ~FIO4PIN;
}

void blink(void)
{
	while(1)
	{
		delay();
		FIO3PIN = 0x00;
		delay();
		FIO3PIN = 0x01;
	}
}

void bin2gry(void)
{
	FIO3PIN	= 0xFF;
	FIO4PIN	= 0x00;
	int tempnum = 0x00;
	
	while(1)
	{
		tempnum = FIO4PIN;
		FIO3PIN = tempnum ^ (tempnum >> 1);
	}
}

void labADC(void)
{
	// First select our ADC channel. I hope it is ADC1
	// Suppose I want to set the 3rd bit of register R, then
	// R |= (1 << 3)
	// For clearin,
	// R &= ~(1 << 3)
	int digital;
	PINSEL1 |= (0x01 << 16);		// Make the pin as ADC
	PCONP	|= (0x01 << 12);		// Switch on the ADC	 

	AD0CR |= (0x01 << 1);		// ADC1
	AD0CR |= (0xFF << 8);		// Get the slowest ADC system clock. Too lazy to calculate.
	AD0CR |= (0x01 << 16);		// Burst on. This means that sampling takes regularly.
	AD0CR |= (0x02 << 17);		// CLKS = 010, 9 clock cycles for each conversion, 8 bit resolution.
	AD0CR |= (0x01 << 21); 		// ADC is operational

	// Our initialisation is done. Now go into an infinite loop
	while(1)
	{
		if(AD0DR1 & 0x80000000)
		{
			digital = ((AD0DR1 >> 8) & 0xFF);
			FIO3PIN = digital;
		}
	}
}
void volt_out(float voltage)
{
	PINSEL1 |= (0x02 << 20);		// AOUT is enabled
	PCLKSEL0 |= (0x01 << 22);		// Select the appropriate clock configuration. Need to find out why
	PINMODE1 |= (0x03 << 20);		// Select the internal pullup.
	int value;
	while(1)
	{
		value=voltage*1023/3.3;
		DACR = (value << 6);
	}
	
}
void sawtoothDAC(void)
{
	PINSEL1 |= (0x02 << 20);		// AOUT is enabled
	PCLKSEL0 |= (0x01 << 22);		// Select the appropriate clock configuration. Need to find out why
	PINMODE1 |= (0x03 << 20);		// Select the internal pullup.
	
	int value = 0;

	while(1)
	{
		while(value < 0x400)
		{
			DACR = (value << 6);
			value += 1;
		}
		value = 0;
	}
	
}

void sinDAC(void)
{
	PINSEL1 |= (0x02 << 20);		// AOUT is enabled
	PCLKSEL0 |= (0x01 << 22);		// Select the appropriate clock configuration. Need to find out why
	PINMODE1 |= (0x03 << 20);		// Select the internal pullup.
	
	int value = 0,i;
	float sinval[] = {0,0.156,0.3,0.45,0.58,0.707,0.8,0.89,0.95,0.98,1.0};
	while(1)
	{
		for(i=0;i<11;i++)
		{
			value = 1024 * (1 + sinval[i])/3.3;
			DACR = value<<6;
		}
		for(i=10;i>=0;i--)
		{
			value = 1024 * (1 + sinval[i])/3.3;
			DACR = value<<6;
		}for(i=0;i<11;i++)
		{
			value = 1024 * (1 - sinval[i])/3.3;
			DACR = value<<6;
		}
		for(i=10;i>=0;i--)
		{
			value = 1024 * (1 - sinval[i])/3.3;
			DACR = value<<6;
		}
		
	}
	
} 

void triangleDAC(void)
{
	PINSEL1 |= (0x02 << 20);		// AOUT is enabled
	PCLKSEL0 |= (0x01 << 22);		// Select the appropriate clock configuration. Need to find out why
	PINMODE1 |= (0x03 << 20);		// Select the internal pullup.
	
	int value = 0;

	while(1)
	{
		while(value < 0x400)
		{
			DACR = (value << 6);
			value += 1;
		}
		while(value > 0)
		{
			value -= 1;
			DACR = (value << 6);
		}
		
	}
	
}

void relay(void)
{
	int a,b,c;
	while(1)
	{
		a = FIO4PIN;
		a = b;
		a &= 0x01;				// get the values of 1st two bits
		c = a;
		b &= 0x02;
		c = a|b;
		b = b<<1;
		a = a|b;
		a=a<<24; 
		a = a|c;
		FIO3PIN=a;
		
	}

}
void relay1(void)
{
	
	while(1)
	{
		FIO3PIN=0x1000000;
		delay();
		delay();
		delay();
		delay();
		FIO3PIN=0x4000000;
		delay();
		delay();
		delay();
		delay(); 
					
	}

}		
/************************* main routine ************************************************************/

int main ()
{
	FIO3DIR=0xFFFFFFFF;
	FIO4DIR=0x00;	
	init_timer(((72000000/100)-1));
	relay();
	return 0;
}

  
