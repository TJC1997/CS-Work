/*
 * This is the file in which you'll write the functions required to implement
 * a stack using two queues.  Make sure to add your name and @oregonstate.edu
 * email address below:
 *
 * Name:
 * Email:
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "queue.h"
#include "link.h"
#include "stack_from_queues.h"

/*
 * This function should allocate and initialize all of the memory needed for
 * your stack and return a pointer to the stack structure.
 */
struct stack_from_queues* stack_from_queues_create() {
  struct stack_from_queues* s=malloc(sizeof(struct stack_from_queues));
  assert(s);
  s->q1=queue_create();
  s->q2=queue_create();
  return s;
}

/*
 * This function should free all of the memory allocated to a stack, including
 * the memory associated with each queue.
 *
 * Params:
 *   stack - the stack to be destroyed.  May not be NULL.  The function should
 *     exit the program with an error if stack is NULL.
 */
void stack_from_queues_free(struct stack_from_queues* stack) {
  assert(stack);
  queue_free(stack->q1);
  queue_free(stack->q2);
  free(stack);
  stack=NULL;
}

/*
 * This function should return 0 if a stack is completely empty or 1 if there
 * is at least one element stored in the stack.
 *
 * Params:
 *   stack - the stack whose emptiness is to be checked.  May not be NULL.
 *     The function should exit the program with an error if stack is NULL.
 *
 * Return:
 *   Should return 1 if the stack is empty or 0 otherwise.
 */
int stack_from_queues_isempty(struct stack_from_queues* stack) {
  assert(stack);
  if(queue_isempty(stack->q1) && queue_isempty(stack->q2))
  //if q1 and q2 are empty,queue_isempty fucntion will return ture
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/*
 * Should push a new value onto a stack.
 *
 * Params:
 *   stack - the stack onto which to push a value.  May not be NULL.
 *     The function should exit the program with an error if stack is NULL.
 *   value - the new value to be pushed onto the stack
 */
void stack_from_queues_push(struct stack_from_queues* stack, int value) {
  assert(stack);
  queue_enqueue(stack->q1,value);
}

/*
 * Should return a stack's top value without removing that value from the
 * stack.
 *
 * Params:
 *   stack - the stack from which to read the top value.  May not be NULL or
 *     empty.  The function should exit the program with an error if stack is
 *     NULL or empty.
 *
 * Return:
 *   Should return the value stored at the top of the stack.
 */
int stack_from_queues_top(struct stack_from_queues* stack) {
  assert(stack);
  int num;
  while(!queue_isempty(stack->q1))
  {
    num=queue_dequeue(stack->q1);//move all numbers from q1 to q2
    queue_enqueue(stack->q2,num);
  }
  int num2;
  while(!queue_isempty(stack->q2))//move all elements in q2 back to q1
  {
    num2=queue_dequeue(stack->q2);
    queue_enqueue(stack->q1,num2);
  }
  return num;//num is the last element in q1
}

/*
 * Should remove the top element from a stack and return its value.
 *
 * Params:
 *   stack - the stack from which to pop a value.  May not be NULL or
 *     empty.  The function should exit the program with an error if stack is
 *     NULL or empty.
 *
 * Return:
 *   Should return the value stored at the top of the stack before that value
 *   is popped.
 */
int stack_from_queues_pop(struct stack_from_queues* stack) {
  assert(stack);
  int num;
  while(!queue_isempty(stack->q1))
  {
    num=queue_dequeue(stack->q1);//get all the value of q1 excpet the last one 
    if(!queue_isempty(stack->q1))//if the queue is not empty,store them in to q2,we will leave the last element in the end
    {
      queue_enqueue(stack->q2,num);
    }
  }
  int num2;
  while(!queue_isempty(stack->q2))//move all elements in q2 back to q1
  {
    num2=queue_dequeue(stack->q2);
    queue_enqueue(stack->q1,num2);
  }
  return num;
}
