/*
 * GPIO.h
 *
 *  Created on: 17 feb 2023
 *      Author: gunhe
 */

#ifndef E2_P2_OSEK_INTERRUPCIONES_GPIO_H_
#define E2_P2_OSEK_INTERRUPCIONES_GPIO_H_
#include "stdint.h"

/*-----PIN CONTROL REGISTER PIN-----*/
typedef struct
{
	uint32_t PCR_pin[32];
}PCRn_t;

typedef struct {
	uint32_t PDOR;
	uint32_t PSOR;
	uint32_t PCOR;
	uint32_t PTOR;
	uint32_t PDIR;
	uint32_t PDDR;
} GPIO_t;

/*-----PIN CONTROL REGISTERS A B C D E-----*/
#define PCRn_E_BASE_ADDR (((volatile uint32_t *) 0x4004D000))
#define PCRn_D_BASE_ADDR (((volatile uint32_t *) 0x4004C000))
#define PCRn_C_BASE_ADDR (((volatile uint32_t *) 0x4004B000))
#define PCRn_B_BASE_ADDR (((volatile uint32_t *) 0x4004A000))
#define PCRn_A_BASE_ADDR (((volatile uint32_t *) 0x40049000))
#define PCRn_E  ( (PCRn_t*) PCRn_E_BASE_ADDR)
#define PCRn_D  ( (PCRn_t*) PCRn_D_BASE_ADDR)
#define PCRn_C  ( (PCRn_t*) PCRn_C_BASE_ADDR)
#define PCRn_B  ( (PCRn_t*) PCRn_B_BASE_ADDR)
#define PCRn_A  ( (PCRn_t*) PCRn_A_BASE_ADDR)


/*-----GPIO BASE REGS-----*/
#define GPIO_E_BASE_ADDR (((volatile uint32_t *) 0x400FF100))
#define GPIO_D_BASE_ADDR (((volatile uint32_t *) 0x400FF0C0))
#define GPIO_C_BASE_ADDR (((volatile uint32_t *) 0x400FF080))
#define GPIO_B_BASE_ADDR (((volatile uint32_t *) 0x400FF040))
#define GPIO_A_BASE_ADDR (((volatile uint32_t *) 0x400FF000))
#define GPIO_E ( (GPIO_t*) GPIO_E_BASE_ADDR)
#define GPIO_D ( (GPIO_t*) GPIO_D_BASE_ADDR)
#define GPIO_C ( (GPIO_t*) GPIO_C_BASE_ADDR)
#define GPIO_B ( (GPIO_t*) GPIO_B_BASE_ADDR) //El primer asterisco hace ya la ind de ADDR
#define GPIO_A ( (GPIO_t*) GPIO_A_BASE_ADDR)

#define PCR_PTEn_BASE_ADDR (((volatile uint32_t *) 0x4004D000))
#define PCR_PTDn_BASE_ADDR (((volatile uint32_t *) 0x4004C000))
#define PCR_PTCn_BASE_ADDR (((volatile uint32_t *) 0x4004B000))
#define PCR_PTBn_BASE_ADDR (((volatile uint32_t *) 0x4004A000))
#define PCR_PTAn_BASE_ADDR (((volatile uint32_t *) 0x40049000))
#define PCR_PTEn	( (PCRn_t*) PCR_PTEn_BASE_ADDR)
#define PCR_PTDn	( (PCRn_t*) PCR_PTDn_BASE_ADDR)
#define PCR_PTCn	( (PCRn_t*) PCR_PTCn_BASE_ADDR)
#define PCR_PTBn	( (PCRn_t*) PCR_PTBn_BASE_ADDR)
#define PCR_PTAn	( (PCRn_t*) PCR_PTAn_BASE_ADDR)

/*-----PIN DEFINITIONS-----*/
#define BLUE_PIN 	11u
#define RED_PIN 	9u
#define GREEN_PIN 	6u
/*-----FUNCTIONS-----*/
void GPIO_Init();

#endif /* E2_P2_OSEK_INTERRUPCIONES_GPIO_H_ */
