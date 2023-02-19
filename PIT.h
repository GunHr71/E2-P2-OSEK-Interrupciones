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

#define DEMO_PIT_BASEADDR PIT
#define DEMO_PIT_CHANNEL kPIT_Chnl_0

#define PIT_IRQ_ID 		 PIT0_IRQn


void PIT_SIGNAL_HANDLER(void);

//void PIT_Init(void);

void PIT_callback_init(timerx timer, void (*handler)(uint32_t flags));

void Init_PIT();
#endif /* PIT_H_ */
