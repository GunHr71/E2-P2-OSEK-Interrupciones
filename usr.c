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
	//Init_PIT();
	//PIT_callback_init(TIMER_1, scheduler);
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
	chain_task (task_C_ID, task_B_ID);
}

void task_C (void)
{
	RGB_blue_on();
	RGB_blue_off();
	Load_context(task_C_ID);
	terminate_task (task_C_ID);
}
