//OSEK.c
#include <stdlib.h>
#include <stdint.h>
#include <osek.h>

task g_task_arr;

void OS_init ()
{
	//g_task_arr[task_A_ID].p_initial_task = (void*)task_A();

}

void activate_task (uint8_t task_ID)
{
   g_task_arr[task_ID].estado = 1;		//0: ready, 1: run
   scheduler();
}

void chain_task (uint8_t task_ID)
{
   //TODO g_task_arr[task_ID].p_actual_task
   //termina la tarea actual e inicia la siguiente
	g_task_arr[task_ID].estado = 1;
	activate_task (task_ID);
	scheduler();
}

void terminate_task (uint8_t task_ID)
{
   //Revisa si alguna tarea tiene mayor prioridad y lo guardad en una var,
   g_task_arr[task_ID].estado = 0;
   scheduler();
}

void scheduler()
{
	uint8_t max_priority = 0;
	uint8_t max_priority_ID = 0;
	for(uint8_t counter = 0; counter < N_tasks; counter++)
	{
		if(g_task_arr[counter].priority > max_priority)
	    {
			   max_priority = g_task_arr[counter].priority;
			   max_priority_ID = counter;
	    }
	}
}
