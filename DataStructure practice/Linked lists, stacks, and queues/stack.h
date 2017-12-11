/*
 * This file contains the definition of an interface for a stack data structure.
 */

#ifndef __STACK_H
#define __STACK_H

/*
 * Structure used to represent a stack.
 */
struct stack;

/*
 * Creates a new, empty stack and returns a pointer to it.
 */
struct stack* stack_create();

/*
 * Free all of the memory associated with a stack.
 *
 * Params:
 *   stack - the stack to be destroyed.  May not be NULL.
 */
void stack_free(struct stack* stack);

/*
 * Returns 1 if the given stack is empty or 0 otherwise.
 *
 * Params:
 *   stack - the stack whose emptiness is to be checked.  May not be NULL.
 */
int stack_isempty(struct stack* stack);

/*
 * Push a new value onto a stack.
 *
 * Params:
 *   stack - the stack onto which to push a value.  May not be NULL.
 *   value - the new value to be pushed onto the stack
 */
void stack_push(struct stack* stack, int value);

/*
 * Returns a stack's top value without removing that value from the stack.
 *
 * Params:
 *   stack - the stack from which to read the top value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Returns the value stored at the top of the stack.
 */
int stack_top(struct stack* stack);

/*
 * Removes the top element from a stack and returns its value.
 *
 * Params:
 *   stack - the stack from which to pop a value.  May not be NULL or empty.
 *
 * Return:
 *   Returns the value stored at the top of the stack before that value is
 *   popped.
 */
int stack_pop(struct stack* stack);

#endif
