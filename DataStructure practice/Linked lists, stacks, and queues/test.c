/*
 * This file contains executable code for testing your work in this assignment.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "link.h"
#include "list_reverse.h"
#include "queue_from_stacks.h"
#include "stack_from_queues.h"

/*
 * A function to convert an array of integers into a linked list.
 */
struct link* list_from_array(int* array, int n) {
  struct link* link, * head = NULL, * tail = NULL;

  for (int i = 0; i < n; i++) {
    /*
     * Allocate a new link and store the current value there.
     */
    link = malloc(sizeof(struct link));
    link->value = array[i];
    link->next = NULL;

    /*
     * If the list was empty, put the new link at the head.
     */
    if (!head) {
      head = link;
    }

    /*
     * Put the new link at the tail of the list.
     */
    if (tail) {
      tail->next = link;
    }
    tail = link;
  }

  return head;
}


/*
 * A simple function to print the contents of a linked list, given its head.
 */
void list_print(struct link* head) {
  struct link* curr = head;

  if (!curr) {
    printf(" (null)");
  }

  while (curr) {
    printf(" %4d", curr->value);
    curr = curr->next;
  }
  printf("\n");
}


/*
 * A function to free all of the memory allocated to a list, given its head.
 */
void list_free(struct link* head) {
  struct link* next, * curr = head;
  while (curr) {
    next = curr->next;
    free(curr);
    curr = next;
  }
}


int main(int argc, char** argv) {
  int n = 16, m = 8;
  int* array = malloc(n * sizeof(int));
  struct link* list;
  struct queue_from_stacks* queue;
  struct stack_from_queues* stack;

  printf("\n===========================\n");
  printf("== Testing list_reverse()\n");
  printf("===========================\n\n");

  for (int i = 0; i < n; i++) {
    array[i] = i * i;
  }

  /*
   * Test list reversal using a list created from array.
   */
  list = list_from_array(array, n);
  printf("== Original list contents:");
  list_print(list);
  list = list_reverse(list);
  printf("== Reversed list contents:");
  list_print(list);
  printf("\n");

  /*
   * Test list reversal on a list of length 1 (using a pointer trick to create
   * the list).
   */
  list_free(list);
  list = list_from_array(&n, 1);
  printf("== Original length=1 list contents:");
  list_print(list);
  list = list_reverse(list);
  printf("== Reversed length=1 list contents:");
  list_print(list);
  printf("\n");

  /*
   * Test list reversal on a null list.
   */
  list_free(list);
  list = NULL;
  printf("== Original null list contents:");
  list_print(list);
  list = list_reverse(list);
  printf("== Reversed null list contents:");
  list_print(list);
  printf("\n");

  free(array);

  /*
   * Test queue-from-stacks implementation by enqueueing, checking the front,
   * and dequeueing.
   */
  printf("\n=============================================\n");
  printf("== Testing queue-from-stacks implementation\n");
  printf("=============================================\n\n");
  queue = queue_from_stacks_create();
  printf("== Enqueueing some into queue-from-stacks:");
  for (int i = 0; i < n; i++) {
    int val = 2 * i + 1;
    printf(" %4d", val);
    queue_from_stacks_enqueue(queue, val);
  }
  /*
  printf("\n");
  while(!stack_isempty(queue->s1))
  {
    printf("%d\t",stack_pop(queue->s1));
  }
  */
  printf("\n");

  printf("== Dequeueing some from queue-from-stacks:");
   
  for (int i = 0; i < m; i++) {
    int front = queue_from_stacks_front(queue);
    assert(front == queue_from_stacks_dequeue(queue));
    printf(" %4d", front);
  }
  printf("\n");

  printf("== Enqueueing more into queue-from-stacks:");
  for (int i = n; i < n + m; i++) {
    int val = 2 * i + 1;
    printf(" %4d", val);
    queue_from_stacks_enqueue(queue, val);
  }
  printf("\n");

  printf("== Dequeueing rest from queue-from-stacks:");
  while (!queue_from_stacks_isempty(queue)) {
    int front = queue_from_stacks_front(queue);
    assert(front == queue_from_stacks_dequeue(queue));
    printf(" %4d", front);
  }
  printf("\n");

  queue_from_stacks_free(queue);

  /*
   * Test stack-from-queues implementation by pushing, checking the top, and
   * popping.
   */
  printf("\n=============================================\n");
  printf("== Testing stack-from-queues implementation\n");
  printf("=============================================\n\n");
  stack = stack_from_queues_create();
  printf("== Pushing some onto stack-from-queues:");
  for (int i = 0; i < n; i++) {
    int val = 2 * i;
    printf(" %4d", val);
    stack_from_queues_push(stack, val);
  }
  printf("\n");

  printf("== Popping some from stack-from-queues:");
  for (int i = 0; i < m; i++) {
    int top = stack_from_queues_top(stack);
    assert(top == stack_from_queues_pop(stack));
    printf(" %4d", top);
  }
  printf("\n");

  printf("== Pushing more onto stack-from-queues:");
  for (int i = n; i < n + m; i++) {
    int val = 2 * i;
    printf(" %4d", val);
    stack_from_queues_push(stack, val);
  }
  printf("\n");

  printf("== Dequeueing rest from stack-from-queues:");
  while (!stack_from_queues_isempty(stack)) {
    int top = stack_from_queues_top(stack);
    assert(top == stack_from_queues_pop(stack));
    printf(" %4d", top);
  }
  printf("\n");

  stack_from_queues_free(stack);
}
