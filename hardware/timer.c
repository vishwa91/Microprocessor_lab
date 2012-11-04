/*****************************************************************************
 *   timer.c:  Timer C file for NXP LPC23xx/24xx Family Microprocessors
 *
 *   Copyright(C) 2006, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2006.09.01  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#include "LPC23xx.h"		/* LPC23xx/24xx Peripheral Registers	*/

volatile int timer_counter = 0;
#define NULL    ((void *)0)
#define FALSE   (0)
#define TRUE    (1)
/*******************************copied files from irq.h file *************************************************/
#define VECT_ADDR_INDEX	0x100
#define VECT_CNTL_INDEX 0x200

/* Be aware that, from compiler to compiler, nested interrupt will have to
be handled differently. More details can be found in Philips LPC2000
family app-note AN10381 */
 

// mthomas
#ifdef __GNUC__
#define __irq
#define IENABLE 
#define IDISABLE
#else
/* unlike Keil CARM Compiler, in ARM's RealView compiler, don't save and 
restore registers into the stack in RVD as the compiler does that for you. 
See RVD ARM compiler Inline and embedded assemblers, "Rules for 
using __asm and asm keywords. */
static int sysreg;		/* used as LR register */
#define IENABLE __asm { MRS sysreg, SPSR; MSR CPSR_c, #SYS32Mode }
#define IDISABLE __asm { MSR CPSR_c, #(IRQ32Mode|I_Bit); MSR SPSR_cxsf, sysreg }
#endif

/******************************************************************************************************************/
/******************************************************************************
** Function name:		install_irq
**
** Descriptions:		Install interrupt handler
** parameters:			Interrupt number, interrupt handler address, 
**						interrupt priority
** Returned value:		true or false, return false if IntNum is out of range
** 
******************************************************************************/
int install_irq( int IntNumber, void *HandlerAddr, int Priority )
{
    int *vect_addr;
    int *vect_cntl;
      
    VICIntEnClr = 1 << IntNumber;	/* Disable Interrupt */
    if ( IntNumber >= 32 )
    {
		return ( FALSE );
    }
    else
    {
		/* find first un-assigned VIC address for the handler */
		vect_addr = (int *)(VIC_BASE_ADDR + VECT_ADDR_INDEX + IntNumber*4);
		vect_cntl = (int *)(VIC_BASE_ADDR + VECT_CNTL_INDEX + IntNumber*4);
		*vect_addr = (int)HandlerAddr;	/* set interrupt vector */
		*vect_cntl = Priority;
		VICIntEnable = 1 << IntNumber;	/* Enable Interrupt */
		return( TRUE );
    }
}

/******************************************************************************
** Function name:		Timer0Handler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**				executes each 10ms @ 60 MHz CPU Clock
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
#ifdef __GNUC__
void Timer0Handler (void); // avoid missing proto warning - mthomas
#endif
void Timer0Handler (void) __irq 
{  
    T0IR = 1;			/* clear interrupt flag */
    IENABLE;			/* handles nested interrupt */

    timer_counter++;

    IDISABLE;
    VICVectAddr = 0;		/* Acknowledge Interrupt */
}

/******************************************************************************
** Function name:		enable_timer
**
** Descriptions:		Enable timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
** 
******************************************************************************/
void enable_timer( char timer_num )
{
    if ( timer_num == 0 )
    {
		T0TCR = 1;
    }
    else
    {
		T1TCR = 1;
    }
    return;
}

/******************************************************************************
** Function name:		disable_timer
**
** Descriptions:		Disable timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
** 
******************************************************************************/
void disable_timer( char timer_num )
{
    if ( timer_num == 0 )
    {
		T0TCR = 0;
    }
    else
    {
		T1TCR = 0;
    }
    return;
}

/******************************************************************************
** Function name:		reset_timer
**
** Descriptions:		Reset timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
** 
******************************************************************************/
void reset_timer( char timer_num )
{
    int regVal;

    if ( timer_num == 0 )
    {
		regVal = T0TCR;
		regVal |= 0x02;
		T0TCR = regVal;
    }
    else
    {
		regVal = T1TCR;
		regVal |= 0x02;
		T1TCR = regVal;
    }
    return;
} 

/******************************************************************************
** Function name:		init_timer
**
** Descriptions:		Initialize timer, set timer interval, reset timer,
**						install timer interrupt handler
**
** parameters:			None
** Returned value:		true or false, if the interrupt handler can't be
**						installed, return false.
** 
******************************************************************************/
int init_timer ( int TimerInterval ) 
{
    timer_counter = 0;
    T0MR0 = TimerInterval;
    T0MCR = 3;				/* Interrupt and Reset on MR0*/ 
    if ( install_irq( 4, (void *)Timer0Handler, 0x01 ) == FALSE )
    {
		return (FALSE);
    }
   else
    {
		return (TRUE);
    }
}

/******************************************************************************
**                            End Of File
******************************************************************************/
