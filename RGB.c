/*
 * RGB.c
 *
 *  Created on: 17 feb 2023
 *      Author: gunhe
 */
#include "RGB.h"
#include "GPIO.h"
void RGB_blue_on(void)
{
	GPIO_A->PCOR = (1 << BLUE_PIN); //PRENDIó

}
void RGB_blue_off(void)
{
	GPIO_A->PSOR = (1 << BLUE_PIN); //APAGADO
}
void RGB_red_on(void)
{
	GPIO_C->PCOR = (1 << RED_PIN);
}
void RGB_red_off(void)
{
	GPIO_C->PSOR = (1 << RED_PIN);
}
void RGB_green_on(void)
{
	GPIO_E->PCOR = (1 << GREEN_PIN);
}
void RGB_green_off(void)
{
	GPIO_E->PSOR = (1 << GREEN_PIN);
}

