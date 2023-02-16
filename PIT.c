#include "fsl_pit.h"
#include "PIT.h"

//Curiosamente se ocupan todos los pits
static void (*timer_0_callback)(uint32_t flags) = 0;
static void (*timer_1_callback)(uint32_t flags) = 0;
static void (*timer_2_callback)(uint32_t flags) = 0;
static void (*timer_3_callback)(uint32_t flags) = 0;
void PIT_callback_init(timerx timer, void (*handler)(uint32_t flags))
{

 	if(TIMER_1 == timer)
 	{
 		timer_0_callback = handler;
 	}
 	else if(TIMER_2 == timer)
 	{
 		timer_1_callback = handler;
 	}
 	else if(TIMER_3 == timer)
 	{
 		timer_2_callback = handler;
 	}
 	else
 	{
 		timer_3_callback = handler;
 	}
}

//!Aunque este IRQ este creada, no significa que se entre a el
//*Solo se crea, porque sin el la base de tiempo para el DMA -> DAC
//*No funciona
void PIT_SIGNAL_HANDLER(void)
{
	static uint32_t irq = 0;
	irq = PIT_GetStatusFlags(DEMO_PIT_BASEADDR, DEMO_PIT_CHANNEL);
 	if(timer_0_callback)
 	{
 		timer_0_callback(irq);
 	}
	PIT_ClearStatusFlags(DEMO_PIT_BASEADDR, DEMO_PIT_CHANNEL, kPIT_TimerFlag);
	__DSB();
}
//*Bandera necesaria para hacer el delay
uint8_t g_pit_flag_end = 0;
//*Interrupcion para mostrar las imagenes o screens de cada estado
void PIT2_SIGNAL_HANDLER(void)
{
	static uint32_t irq = 0;
	irq = PIT_GetStatusFlags(DEMO_PIT_BASEADDR, DEMO_PIT2_CHANNEL);
 	if(timer_1_callback)
 	{
 		timer_1_callback(irq);
 	}
	PIT_ClearStatusFlags(DEMO_PIT_BASEADDR, DEMO_PIT2_CHANNEL, kPIT_TimerFlag);
	__DSB();
}

//delay
void PIT3_SIGNAL_HANDLER(void)
{
	static uint32_t irq = 0;
	irq = PIT_GetStatusFlags(DEMO_PIT_BASEADDR, DEMO_PIT3_CHANNEL);
 	if(timer_2_callback)
 	{
 		timer_2_callback(irq);
 	}
	PIT_ClearStatusFlags(DEMO_PIT_BASEADDR, DEMO_PIT3_CHANNEL, kPIT_TimerFlag);
	__DSB();
	g_pit_flag_end = g_pit_flag_end ^ 1;
	PIT_StopTimer(DEMO_PIT_BASEADDR, DEMO_PIT3_CHANNEL);
}

//se encarga solo de la pantalla de inicialización
void PIT4_SIGNAL_HANDLER(void)
{
	static uint32_t irq = 0;
	irq = PIT_GetStatusFlags(DEMO_PIT_BASEADDR, DEMO_PIT4_CHANNEL);
 	if(timer_3_callback)
 	{
 		timer_3_callback(irq);
 	}
 	PIT_StopTimer(DEMO_PIT_BASEADDR, DEMO_PIT4_CHANNEL);
	PIT_ClearStatusFlags(DEMO_PIT_BASEADDR, DEMO_PIT4_CHANNEL, kPIT_TimerFlag);
	__DSB();
}

void Init_PIT(void)
{
	pit_config_t pitConfig;
	uint32_t clock;
	clock = CLOCK_GetFreq(kCLOCK_BusClk);
	CLOCK_SetSimSafeDivs();
	PIT_GetDefaultConfig(&pitConfig);
	PIT_Init(DEMO_PIT_BASEADDR, &pitConfig);

	PIT_SetTimerPeriod(DEMO_PIT_BASEADDR, DEMO_PIT_CHANNEL, USEC_TO_COUNT(SIXTEEN_KHZ, clock));
	PIT_SetTimerPeriod(DEMO_PIT_BASEADDR, DEMO_PIT2_CHANNEL, USEC_TO_COUNT(REFRESH_RATE, clock));
	PIT_SetTimerPeriod(DEMO_PIT_BASEADDR, DEMO_PIT4_CHANNEL, USEC_TO_COUNT(LOGO_TIME, clock));

	PIT_EnableInterrupts(DEMO_PIT_BASEADDR, DEMO_PIT_CHANNEL, kPIT_TimerInterruptEnable);
	PIT_EnableInterrupts(DEMO_PIT_BASEADDR, DEMO_PIT2_CHANNEL, kPIT_TimerInterruptEnable);
	PIT_EnableInterrupts(DEMO_PIT_BASEADDR, DEMO_PIT3_CHANNEL, kPIT_TimerInterruptEnable);
	PIT_EnableInterrupts(DEMO_PIT_BASEADDR, DEMO_PIT4_CHANNEL, kPIT_TimerInterruptEnable);

	EnableIRQ(PIT2_IRQ_ID);
	EnableIRQ(PIT3_IRQ_ID);
	EnableIRQ(PIT4_IRQ_ID);
	PIT_StartTimer(DEMO_PIT_BASEADDR, DEMO_PIT_CHANNEL);
	PIT_StartTimer(DEMO_PIT_BASEADDR, DEMO_PIT2_CHANNEL);
	PIT_StartTimer(DEMO_PIT_BASEADDR, DEMO_PIT4_CHANNEL);
}

//*Esta funcion sirve para iniciar un PIT y decirle cuando tiempo quieres que trabaje
void Change_Timer_period(PIT_Type *base, pit_chnl_t channel, uint32_t count)
{
	uint32_t clock;
	clock = CLOCK_GetFreq(kCLOCK_BusClk);
	PIT_StopTimer(base, channel);
	PIT_SetTimerPeriod(base, channel, USEC_TO_COUNT(count, clock));
	PIT_StartTimer(base, channel);
}

//*Funcion que se encarga de los delays
//* la funcion o el estado en el que estemos hace la duracion del pit
void wait_for_timer(uint32_t time)
{
	g_pit_flag_end = 1;
	uint32_t clock = 0;
	clock = CLOCK_GetFreq(kCLOCK_BusClk);
	PIT_SetTimerPeriod(DEMO_PIT_BASEADDR, DEMO_PIT3_CHANNEL, USEC_TO_COUNT(time, clock));
	PIT_StartTimer(DEMO_PIT_BASEADDR, DEMO_PIT3_CHANNEL);
}
//* Esta funcion regresa un "1" si la interrupcion por el pit 3 se ha terminado
//* 0 indica que no esta un uso actualmente
uint8_t is_timer_end(void)
{
	return g_pit_flag_end;
}
