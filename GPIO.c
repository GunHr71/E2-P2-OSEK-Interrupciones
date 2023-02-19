/*
 * GPIO.c
 *
 *  Created on: 17 feb 2023
 *      Author: gunhe
 */

#include "GPIO.h"
#include <stdint.h>

#define SIM_5 (*((volatile uint32_t *) 0x40048038))

void GPIO_Init()
{
	SIM_5 	= 0x00002A00; //conectamos el clock al gpio C, E , A
	PCR_PTEn->PCR_pin[6] = 0x00000100;
	PCR_PTCn->PCR_pin[9] = 0x00000100;
	PCR_PTAn->PCR_pin[11] = 0x00000100;

	GPIO_C->PDOR = (1 << RED_PIN); //APAGADO
	GPIO_C->PDDR = (1 << RED_PIN);

	GPIO_E->PDOR = (1 << GREEN_PIN); //APAGADO
	GPIO_E->PDDR = (1 << GREEN_PIN);

	GPIO_A->PDOR = (1 << BLUE_PIN); //APAGADO
	GPIO_A->PDDR = (1 << BLUE_PIN);

    /*CLOCK_EnableClock(kCLOCK_PortC);
    CLOCK_EnableClock(kCLOCK_PortE);
    CLOCK_EnableClock(kCLOCK_PortA);
    PORT_SetPinMux(PORTC, 9U, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTE, 6U, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTA, 11U, kPORT_MuxAsGpio);

    GPIO_PinInit(BOARD_LED_GPIO, BOARD_LED_GPIO_PIN, &led_config);
    GPIO_PinInit(BOARD_LED_GPIO, BOARD_LED_GPIO_PIN, &led_config);
    GPIO_PinInit(BOARD_LED_GPIO, BOARD_LED_GPIO_PIN, &led_config);
    GPIO_PinInit(GPIOE, 6U, &led_config);
    GPIO_PinInit(GPIOA, 11U, &led_config);*/
}
