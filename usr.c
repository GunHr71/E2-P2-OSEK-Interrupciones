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
#include <osek.h>
#include "fsl_gpio.h"
#include "board.h"

#define BOARD_LED_GPIO     BOARD_LED_RED_GPIO
#define BOARD_LED_GPIO_PIN BOARD_LED_RED_GPIO_PIN

int main(void)
{
	GPIO_Init();
	OS_init();
	while (1){};
}

uint8_t task_A (void)
{
	GPIO_PortClear(GPIOC, 1 << 9U);
	activate_task (task_B_ID);
	GPIO_PortSet(GPIOC, 1 << 9U);
	return 1;
}

void task_B (void)
{
	GPIO_PortClear(GPIOE, 1 << 6U);
	chain_task (task_C_ID);
	GPIO_PortSet(GPIOE, 1 << 6U);
}

void task_C (void)
{
	GPIO_PortClear(GPIOA, 1 << 11U);
	terminate_task (task_C_ID);
	GPIO_PortSet(GPIOA, 1 << 11U);
}

void GPIO_Init()
{
    gpio_pin_config_t led_config = {
        kGPIO_DigitalOutput,
        1,
    };
    CLOCK_EnableClock(kCLOCK_PortC);
    CLOCK_EnableClock(kCLOCK_PortE);
    CLOCK_EnableClock(kCLOCK_PortA);
    PORT_SetPinMux(PORTC, 9U, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTE, 6U, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTA, 11U, kPORT_MuxAsGpio);

    GPIO_PinInit(BOARD_LED_GPIO, BOARD_LED_GPIO_PIN, &led_config);
    GPIO_PinInit(BOARD_LED_GPIO, BOARD_LED_GPIO_PIN, &led_config);
    GPIO_PinInit(BOARD_LED_GPIO, BOARD_LED_GPIO_PIN, &led_config);
    GPIO_PinInit(GPIOE, 6U, &led_config);
    GPIO_PinInit(GPIOA, 11U, &led_config);
}
