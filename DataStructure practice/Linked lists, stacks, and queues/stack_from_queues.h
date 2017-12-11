/*
 * This file contains the definitions of structures and prototpyes of functions
 * you'll implement to create a stack using two queues.
 */

#ifndef __STACK_FROM_QUEUES_H
#define __STACK_FROM_QUEUES_H

#include "queue.h"

/*
 * This is the definition of the structure you'll use to implement a stack
 * using two queues.
 */
struct stack_from_queues {
  struct queue* q1;
  struct queue* q2;
};


/*
 * These are the prototypes of the functions you'll write in
 * stack_from_queues.c to implement a stack from two queues.  See the
 * documentation in stack_from_queues.c for more details about each function.
 */
struct stack_from_queues* stack_from_queues_create();
void stack_from_queues_free(struct stack_from_queues* stack);
int stack_from_queues_isempty(struct stack_from_queues* stack);
void stack_from_queues_push(struct stack_from_queues* stack, int value);
int stack_from_queues_top(struct stack_from_queues* stack);
int stack_from_queues_pop(struct stack_from_queues* stack);

#endif
