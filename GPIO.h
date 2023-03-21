/*
 * GPIO.h
 *
 *  Created on: 17 feb 2023
 *      Author: gunhe
 */

#ifndef E2_P2_OSEK_INTERRUPCIONES_GPIO_H_
#define E2_P2_OSEK_INTERRUPCIONES_GPIO_H_
#include "stdint.h"

#define SIM_5 (*((volatile uint32_t *) 0x40048038))
#define PORTA_ISFR (*((volatile uint32_t *) 0x400490A0))
/*-----PIN CONTROL REGISTER PIN-----*/
typedef struct
{
	uint32_t PCR_pin[32];
	uint32_t PORTA_GPCLR;
	uint32_t PORTA_GPCHR;
	const uint32_t RESERVED[6];
	uint32_t PORTA_ISFRR;
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
#define SW2_PIN		10u		//PTD11
#define SW3_PIN		11u		//PTA10
/*-----CONSTANTS-----*/
typedef enum{
	IRQC_FALLING	= 10 << 16,
	LOCK_REG		= 1 << 15,
	MUX 		  	= 1 << 8,
	DRVE_STRG_EN  	= 1 << 6,
	OPEN_DRAIN_EN 	= 1 << 5,
	PSVE_FLTR_EN  	= 1 << 4,
	SLEW_RATE_EN  	= 1 << 2,
	PULL_EN		  	= 1 << 1,
	PULL_SEL		= 1 << 0,
}PCR_CNFG;

typedef enum{
	SIMCG5_PORTA_BIT = 1 << 9,
	SIMCG5_PORTB_BIT = 1 << 10,
	SIMCG5_PORTC_BIT = 1 << 11,
	SIMCG5_PORTD_BIT = 1 << 12,
	SIMCG5_PORTE_BIT = 1 << 13,
}SIMCG5;

typedef enum{
	PORT_A = 0,
	PORT_B = 1,
	PORT_C = 2,
	PORT_D = 3,
	PORT_E = 4,
}PORTx;

/*-----FUNCTIONS-----*/
void GPIO_Init();
void GPIO_callback_init(PORTx port, void (*handler)(uint32_t flags));
#endif /* E2_P2_OSEK_INTERRUPCIONES_GPIO_H_ */
