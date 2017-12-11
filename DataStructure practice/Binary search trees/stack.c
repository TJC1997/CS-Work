/*
 * This file contains the definitions of structures and functions implementing
 * a simple stack using a linked list.
 */

#include <stdlib.h>
#include <assert.h>

#include "stack.h"


/*
 * This is the definition for a link structure for implementing singly-linked
 * lists that contain pointer values of arbitrary type.
 */
struct link {
  void* value;
  struct link* next;
};

/*
 * This is the definition of the stack structure.  Using a linked list to
 * implement a stack requires only that we keep track of the top of the stack.
 */
struct stack {
  struct link* top;
};


struct stack* stack_create() {
  struct stack* stack = malloc(sizeof(struct stack));
  assert(stack);
  stack->top = NULL;
  return stack;
}


void stack_free(struct stack* stack) {
  assert(stack);

  /*
   * Here, we're assuming that stack_pop() handles freeing the memory
   * associated with each popped element.
   */
  while (!stack_isempty(stack)) {
    stack_pop(stack);
  }
  free(stack);
}


int stack_isempty(struct stack* stack) {
  assert(stack);
  return stack->top == NULL;
}


void stack_push(struct stack* stack, void* value) {
  assert(stack);
  struct link* new_link = malloc(sizeof(struct link));
  assert(new_link);

  /*
   * Fill out the new link at put it at the head of the list, which represents
   * the top of the stack.
   */
  new_link->value = value;
  new_link->next = stack->top;
  stack->top = new_link;
}


void* stack_top(struct stack* stack) {
  assert(stack && !stack_isempty(stack));
  return stack->top->value;
}


void* stack_pop(struct stack* stack) {
  assert(stack && !stack_isempty(stack));

  /*
   * Remove the old top element from the list and remember its value before
   * we free it.
   */
  struct link* popped_top = stack->top;
  void* value = popped_top->value;
  stack->top = popped_top->next;
  free(popped_top);

  return value;
}
