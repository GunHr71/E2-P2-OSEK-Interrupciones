/*
 * PIT.h
 *
	\file
	\brief
		This is the source file for PIT module, here we include the functions
		that we are going to use in relation for the PIT.

	\author Atzael Godinez Garcia, Gabriel Orlando Estrada
	\date	21/09/2022
	\todo
*/
#ifndef PIT_H_
#define PIT_H_

#include "MK64F12.h"
#include "fsl_clock.h"
#include "fsl_pit.h"

//esto es necesario para indicarle al callback del timer que timer es
//Probablemente crecera
typedef enum
{
	TIMER_1 = 6,
	TIMER_2 = 7,
	TIMER_3 = 8,
	TIMER_4 = 9,
}timerx;

#define SIXTEEN_KHZ		63u
#define REFRESH_RATE	300000U
#define LOGO_TIME		1000000U
#define PIT_SIGNAL_HANDLER PIT0_IRQHandler
#define PIT2_SIGNAL_HANDLER PIT1_IRQHandler
#define PIT3_SIGNAL_HANDLER PIT2_IRQHandler
#define PIT4_SIGNAL_HANDLER PIT3_IRQHandler

#define DEMO_PIT_BASEADDR PIT
#define DEMO_PIT_CHANNEL kPIT_Chnl_0
#define DEMO_PIT2_CHANNEL kPIT_Chnl_1
#define DEMO_PIT3_CHANNEL kPIT_Chnl_2
#define DEMO_PIT4_CHANNEL kPIT_Chnl_3

#define PIT_IRQ_ID 		 PIT0_IRQn
#define PIT2_IRQ_ID		 PIT1_IRQn
#define PIT3_IRQ_ID		 PIT2_IRQn
#define PIT4_IRQ_ID		 PIT3_IRQn


void PIT_SIGNAL_HANDLER(void);
void PIT3_SIGNAL_HANDLER(void);
void PIT4_SIGNAL_HANDLER(void);
void PIT2_SIGNAL_HANDLER(void);
void Change_frequency(void);

//void PIT_Init(void);

void PIT_callback_init(timerx timer, void (*handler)(uint32_t flags));

void Init_PIT();
void wait_for_timer(uint32_t time);
uint8_t is_timer_end(void);
#endif /* PIT_H_ */
