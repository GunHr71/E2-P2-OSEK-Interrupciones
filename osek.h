/*
 * osek.h
 *
 *  Created on: 31 ene 2023
 *      Author: gunhe
 */

#ifndef OSEK_H_
#define OSEK_H_

#include <stdint.h>
#include <stdio.h>

#define N_tasks 3
#define task_A_ID 0
#define task_B_ID 1
#define task_C_ID 2

#define ACTIVATED 1
#define DEACTIVATED 0

typedef struct
{
  uint32_t return_address;
  uint32_t stack_pointer;
  uint32_t program_counter;
  /*context data */
}context;

typedef void (*task_ptr)(void);
typedef struct
{
  uint8_t priority;
  uint8_t autostart;
  uint8_t estado;
  uint8_t task_ID;
  uint8_t p_actual_task;
  task_ptr p_initial_task; //CHange to pc
  context task_context;
  /* data */
}task;

void OS_init ();
void scheduler();
void terminate_task (uint8_t task_ID);
void chain_task (uint8_t task_ID,uint8_t Current_task_ID );
void activate_task (uint8_t task_ID);
void GPIO_Init();

void task_A (void);
void task_B (void);
void task_C (void);


#endif /* OSEK_H_ */
