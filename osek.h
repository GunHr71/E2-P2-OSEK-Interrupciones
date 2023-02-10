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

typedef struct
{
  uint8_t return_address;
  uint8_t stack_pointer;
  uint8_t program_counter;
  /*context data */
}context;

typedef void (*task_ptr)(void);
typedef struct
{
  uint8_t priority;
  uint8_t autostart: 1;
  uint8_t estado : 1;
  uint8_t task_ID;
  uint8_t p_actual_task;
  task_ptr p_initial_task;
  context task_context;
  /* data */
}task[N_tasks];

void OS_init ();
void scheduler();
void terminate_task (uint8_t task_ID);
void chain_task (uint8_t task_ID);
void activate_task (uint8_t task_ID);

uint8_t task_A (void);
void task_B (void);
void task_C (void);
#endif /* OSEK_H_ */
