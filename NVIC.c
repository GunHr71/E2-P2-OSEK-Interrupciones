/**
	\file
	\brief
		This is the source file for the NVIC device driver for Kinetis K64.
		It contains some configuration functions and runtime functions.
		It is implemented using  CMSIS Core functions
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	27/07/2015
	\todo
	    Pending interrupts and disable interrupts are not enable.
 */

#include "NVIC.h"
#include "PIT.h"
#include "help.h"
void NVIC_enable_interrupt_and_priotity(interrupt_t interrupt_number, priority_level_t priority)
{
	/**This functions are part of CMSIS Core functions*/
	/**It enables the IRQ*/
	NVIC_EnableIRQ(interrupt_number);
	/**It Sets the priority of the IRQ*/
	NVIC_SetPriority(interrupt_number, priority);
}

void NVIC_set_basepri_threshold(priority_level_t priority)
{
	/**Sets the threshold level to attend interrupts*/
	/**A shift is needed to align in a correct manner the data in priority inside BASEPRI register*/
	__asm("LSL R0, R0, #0x4");
	__asm("MSR BASEPRI, R0");
	//ESTO HACE LO MISMO QUE:
	//__set_BASEPRI(priority << (8 - __NVIC_PRIO_BITS));

}

void NVIC_Init(void)
{
	NVIC_set_basepri_threshold(PRIORITY_9);
	NVIC_ISER1 = (1 << 27);//Necesario
	NVIC_IPR59 = (PRIORITY_8 << 28);
	//27
	//31:28
	//PCM_PDA_ADDR = (PRIORITY_8 << ((75 % 4) * 8) + 4);
	//NVIC_enable_interrupt_and_priotity(PORTA_IRQ,PRIORITY_8);
	//NVIC_enable_interrupt_and_priotity(PORTD_IRQ,PRIORITY_7);
	NVIC_global_enable_interrupts;
}
