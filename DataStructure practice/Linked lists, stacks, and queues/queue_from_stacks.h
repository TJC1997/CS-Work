/*
 * This file contains the definitions of structures and prototpyes of functions
 * you'll implement to create a queue using two stacks.
 */

#ifndef __QUEUE_FROM_STACKS_H
#define __QUEUE_FROM_STACKS_H

#include "stack.h"

/*
 * This is the definition of the structure you'll use to implement a queue
 * using two stacks.
 */
struct queue_from_stacks {
  struct stack* s1;
  struct stack* s2;
};


/*
 * These are the prototypes of the functions you'll write in
 * queue_from_stacks.c to implement a queue from two stacks.  See the
 * documentation in queue_from_stacks.c for more details about each function.
 */
struct queue_from_stacks* queue_from_stacks_create();
void queue_from_stacks_free(struct queue_from_stacks* queue);
int queue_from_stacks_isempty(struct queue_from_stacks* queue);
void queue_from_stacks_enqueue(struct queue_from_stacks* queue, int value);
int queue_from_stacks_front(struct queue_from_stacks* queue);
int queue_from_stacks_dequeue(struct queue_from_stacks* queue);

#endif
