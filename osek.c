//OSEK.c
#include <stdlib.h>
#include <stdint.h>
#include <osek.h>

task g_task_arr[N_tasks];

uint8_t AutoStart_flag = DEACTIVATED;

uint8_t Running_tasks_flag = ACTIVATED;

void OS_init ()
{
	for(uint8_t i=0; i < N_tasks; i++) //i = 0
	{
		if(task_A_ID == i)
		{
			g_task_arr[i].autostart = ACTIVATED;
			AutoStart_flag  = ACTIVATED;
		}
		g_task_arr[i].estado = DEACTIVATED;
		g_task_arr[i].task_ID = i;
	}

	g_task_arr[task_A_ID].priority = 0;
	g_task_arr[task_B_ID].priority = 2;
	g_task_arr[task_C_ID].priority = 1;

	g_task_arr[task_A_ID].p_initial_task = task_A;
	g_task_arr[task_B_ID].p_initial_task = task_B;
	g_task_arr[task_C_ID].p_initial_task = task_C;

	scheduler();

}

void activate_task (uint8_t task_ID)
{
   g_task_arr[task_ID].estado = ACTIVATED;	//0: ready, 1: run
   scheduler();
}

void chain_task (uint8_t task_ID,uint8_t Current_task_ID)
{
   //TODO g_task_arr[task_ID].p_actual_task
   //termina la tarea actual e inicia la siguiente
	g_task_arr[Current_task_ID].estado = DEACTIVATED;
	activate_task (task_ID);
}

void terminate_task (uint8_t task_ID)
{
   //Revisa si alguna tarea tiene mayor prioridad y lo guardad en una var,
   g_task_arr[task_ID].estado = DEACTIVATED;
   scheduler();
}

void scheduler()
{
	uint8_t max_priority = 0;
	uint8_t max_priority_ID = 0;

	//Buscamos la tarea autostart
	if(ACTIVATED == AutoStart_flag)
	{
		for(uint8_t counter = 0; counter < N_tasks; counter++)
		{
			if(ACTIVATED == g_task_arr[counter].autostart)
			{
				//Una vez encontrada la tara con autostar, desactivamos la bandera
				AutoStart_flag = DEACTIVATED;
				g_task_arr[counter].p_initial_task();
			}
		}
	}

	//Buscamos la tarea con mayor prioridad
	for(uint8_t counter = 0; counter < N_tasks; counter++)
	{
		if((g_task_arr[counter].priority > max_priority) && (ACTIVATED == g_task_arr[counter].estado))
	    {
			   max_priority = g_task_arr[counter].priority;
			   max_priority_ID = g_task_arr[counter].task_ID;
	    }

	}

	if(0 == max_priority)
	{
		Running_tasks_flag = DEACTIVATED;
	}
	//Ejecutamos la tarea con mayor prioridad
	if(ACTIVATED == Running_tasks_flag)
	{
		g_task_arr[max_priority_ID].p_initial_task();
	}

}
