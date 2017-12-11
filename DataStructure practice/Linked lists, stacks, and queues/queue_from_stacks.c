/*
 * This is the file in which you'll write the functions required to implement
 * a queue using two stacks.  Make sure to add your name and @oregonstate.edu
 * email address below:
 *
 * Name:Yuhang Chen  
 * Email:chenyuha@oregonstate.edu
 */

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "queue_from_stacks.h"
#include <assert.h>

/*
 * This function should allocate and initialize all of the memory needed for
 * your queue and return a pointer to the queue structure.
 */
struct queue_from_stacks* queue_from_stacks_create() {
  struct queue_from_stacks* q=malloc(sizeof(struct queue_from_stacks));
  assert(q);
  q->s1=stack_create();
  q->s2=stack_create();
  return q;
}

/*
 * This function should free all of the memory allocated to a queue, including
 * the memory associated with each stack.
 *
 * Params:
 *   queue - the queue to be destroyed.  May not be NULL.  The function should
 *     exit the program with an error if queue is NULL.
 */
void queue_from_stacks_free(struct queue_from_stacks* queue) {
  assert(queue);
  stack_free(queue->s1);
  stack_free(queue->s2);
  free(queue);
  queue=NULL;
}

/*
 * This function should return 0 if a queue is completely empty or 1 if there
 * is at least one element stored in the queue.
 *
 * Params:
 *   queue - the queue whose emptiness is to be checked.  May not be NULL.
 *     The function should exit the program with an error if queue is NULL.
 *
 * Return:
 *   Should return 1 if the queue is empty or 0 otherwise.
 */
int queue_from_stacks_isempty(struct queue_from_stacks* queue) {
  assert(queue);
  if(stack_isempty(queue->s1) && stack_isempty(queue->s2))
  //if s1 and s2 are empty,stack_isempty fucntion will return ture
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/*
 * Should enqueue a new value onto the end of a queue.
 *
 * Params:
 *   queue - the queue onto which to enqueue a value.  May not be NULL.
 *     The function should exit the program with an error if queue is NULL.
 *   value - the new value to be enqueueed onto the queue
 */
void queue_from_stacks_enqueue(struct queue_from_stacks* queue, int value) {
  assert(queue);
  int num;
  if(stack_isempty(queue->s1)&&stack_isempty(queue->s2))
  {
    stack_push(queue->s1,value);
  }
  else
  {
    //why for(struct link * i=queue->s1->top does not work
    while(!stack_isempty(queue->s1))//while stack 1 is not empty
    {
      num=stack_pop(queue->s1);//clean stack1 and store all numbers in stack2
      stack_push(queue->s2,num);
    }
    stack_push(queue->s2,value);//add new value in stack2
    
    while(!stack_isempty(queue->s2))//while stack 2 is not empty
    {
      num=stack_pop(queue->s2);//clean stack2 and store all numbers in stack1
      stack_push(queue->s1,num);
    }
  }
}

/*
 * Should return a queue's front value without removing that value from the
 * queue.
 *
 * Params:
 *   queue - the queue from which to read the front value.  May not be NULL or
 *     empty.  The function should exit the program with an error if queue is
 *     NULL or empty.
 *
 * Return:
 *   Should return the value stored at the front of the queue.
 */
int queue_from_stacks_front(struct queue_from_stacks* queue) {
  assert(queue);
  return stack_top(queue->s1);
}

/*
 * Should remove the front element from a queue and return its value.
 *
 * Params:
 *   queue - the queue from which to dequeue a value.  May not be NULL or
 *     empty.  The function should exit the program with an error if queue is
 *     NULL or empty.
 *
 * Return:
 *   Should return the value stored at the front of the queue before that value
 *   is dequeued.
 */
int queue_from_stacks_dequeue(struct queue_from_stacks* queue) {
  assert(queue);
  return stack_pop(queue->s1);
}
