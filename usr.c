#include <stdint.h>
#include <stdlib.h>
#include "osek.h"
#include "PIT.h"
#include "RGB.h"
#include "NVIC.h"
#define BOARD_LED_GPIO     BOARD_LED_RED_GPIO
#define BOARD_LED_GPIO_PIN BOARD_LED_RED_GPIO_PIN

int main(void)
{
	GPIO_Init();
	NVIC_Init();
	GPIO_callback_init(PORTA, (void*)activate_task);
	OS_init();
 	while (1){};
}

void task_A (void)
{
	RGB_red_on();
	RGB_red_off();
	Save_context(task_A_ID);
	activate_task (task_B_ID);
}

void task_B (void)
{
	RGB_green_on();
	RGB_green_off();
	//GPIO_callback_init(PORTA, (void*)chain_task);
	chain_task (task_C_ID, task_B_ID);
}

void task_C (void)
{
	RGB_blue_on();
	RGB_blue_off();
	Load_context(task_C_ID);
	//GPIO_callback_init(PORTA, (void*)terminate_task);
	terminate_task (task_C_ID);
}
