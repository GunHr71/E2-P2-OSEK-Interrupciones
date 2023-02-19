#include "fsl_pit.h"
#include "PIT.h"

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

void Init_PIT(void)
{
	pit_config_t pitConfig;
	uint32_t clock;
	clock = CLOCK_GetFreq(kCLOCK_BusClk);
	CLOCK_SetSimSafeDivs();
	PIT_GetDefaultConfig(&pitConfig);

	PIT_Init(DEMO_PIT_BASEADDR, &pitConfig);
	PIT_SetTimerPeriod(DEMO_PIT_BASEADDR, DEMO_PIT_CHANNEL, USEC_TO_COUNT(SIXTEEN_KHZ, clock));
	PIT_EnableInterrupts(DEMO_PIT_BASEADDR, DEMO_PIT_CHANNEL, kPIT_TimerInterruptEnable);
	EnableIRQ(PIT_IRQ_ID);

	PIT_StartTimer(DEMO_PIT_BASEADDR, DEMO_PIT_CHANNEL);
}
