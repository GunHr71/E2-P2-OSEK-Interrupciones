/*
 * help.h
 *
 *  Created on: 24 feb 2023
 *      Author: gunhe
 */

#ifndef E2_P2_OSEK_INTERRUPCIONES_HELP_H_
#define E2_P2_OSEK_INTERRUPCIONES_HELP_H_

#include "stdint.h"

#define PCM_PDA_ADDR (*((volatile uint32_t *) 0x0000012C))
#define NVIC_ISER1 (*((volatile uint32_t *) 0xE000E104))
#define NVIC_ICER1 (*((volatile uint32_t *) 0xE000E184))
#define NVIC_ISPR1 (*((volatile uint32_t *) 0xE000E204))
#define NVIC_ICPR1 (*((volatile uint32_t *) 0xE000E284))
#define NVIC_IABR1 (*((volatile uint32_t *) 0xE000E304))
#define NVIC_IPR59 (*((volatile uint32_t *) 0xE000E4EC))
#endif /* E2_P2_OSEK_INTERRUPCIONES_HELP_H_ */
