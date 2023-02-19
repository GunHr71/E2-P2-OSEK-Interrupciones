/*registro
  prioridad
  autostart
  apuntador al inicio de la tarea
  task ID
  apuntador de direccion actual de ejecucion
  contexto

*/
#include <stdint.h>
#include <stdlib.h>
#include "osek.h"
#include "fsl_gpio.h"
#include "board.h"
#include "PIT.h"
#include "RGB.h"
#define BOARD_LED_GPIO     BOARD_LED_RED_GPIO
#define BOARD_LED_GPIO_PIN BOARD_LED_RED_GPIO_PIN

int main(void)
{
	GPIO_Init();
	RGB_blue_on();
	RGB_blue_off();
	Init_PIT();
	PIT_callback_init(TIMER_1, scheduler);
	OS_init();
	while (1){};
}

void task_A (void)
{
	GPIO_PortClear(GPIOC, 1 << 9U);
	GPIO_PortSet(GPIOC, 1 << 9U);
	activate_task (task_B_ID);

}

void task_B (void)
{
	GPIO_PortClear(GPIOE, 1 << 6U);
	GPIO_PortSet(GPIOE, 1 << 6U);
	chain_task (task_C_ID, task_B_ID);
}

void task_C (void)
{
	GPIO_PortClear(GPIOA, 1 << 11U);
	GPIO_PortSet(GPIOA, 1 << 11U);
	terminate_task (task_C_ID);

}


