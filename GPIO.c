/*
 * GPIO.c
 *
 *  Created on: 17 feb 2023
 *      Author: gunhe
 */

#include "GPIO.h"
#include <stdint.h>
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "help.h"
#include "osek.h"
void GPIO_Init()
{
	SIM_5 	= SIMCG5_PORTC_BIT | SIMCG5_PORTE_BIT | SIMCG5_PORTA_BIT | SIMCG5_PORTD_BIT; //conectamos el clock al gpio C, E , A
	PCR_PTEn->PCR_pin[6]  = MUX;
	PCR_PTCn->PCR_pin[9]  = MUX;
	PCR_PTAn->PCR_pin[11] = MUX;
	PCR_PTAn->PCR_pin[4]  = MUX;
	PCR_PTAn->PCR_pin[10] = MUX | DRVE_STRG_EN | OPEN_DRAIN_EN | SLEW_RATE_EN | PULL_EN | PULL_SEL | IRQC_FALLING;
	PCR_PTDn->PCR_pin[11] = MUX | DRVE_STRG_EN | OPEN_DRAIN_EN | SLEW_RATE_EN | PULL_EN | PULL_SEL | IRQC_FALLING;
	GPIO_C->PDOR = (1 << RED_PIN); //APAGADO
	GPIO_C->PDDR = (1 << RED_PIN);

	GPIO_E->PDOR = (1 << GREEN_PIN); //APAGADO
	GPIO_E->PDDR = (1 << GREEN_PIN);

	GPIO_A->PDOR = (1 << BLUE_PIN); //APAGADO
	GPIO_A->PDDR = (1 << BLUE_PIN);

	//No se necesita indiciar al puerto PTA11 como input, por defecto queda asi
}
static void (*gpio_A_callback)(uint32_t flags) = 0;
static void (*gpio_B_callback)(uint32_t flags) = 0;
static void (*gpio_C_callback)(uint32_t flags) = 0;
static void (*gpio_D_callback)(uint32_t flags) = 0;
static void (*gpio_E_callback)(uint32_t flags) = 0;

void GPIO_callback_init(PORTx port, void (*handler)(uint32_t flags))
{
 	if(PORT_A == port) {
 		gpio_A_callback = handler;
 	}
 	else if(PORT_A == port) {
 		gpio_B_callback = handler;
 	}
 	else if(PORT_C == port) {
 		gpio_C_callback = handler;
 	}
 	else if(PORT_D == port) {
 		gpio_D_callback = handler;
 	}
 	else if(PORT_E == port) {
 		gpio_E_callback = handler;
 	}
}

void PORTA_IRQHandler(void)
{
 	static uint32_t irq_status = 0;
 	if(gpio_A_callback)
 	{
 		gpio_A_callback(task_B_ID);
 	}
 	PCR_PTAn->PORTA_ISFRR = 1 << 10;	//Con esto se limpia la bandera de la irq
}

void PORTD_IRQHandler(void)
{
 	static uint32_t irq_status = 0;
 	irq_status = 2;
 	irq_status++;
}
