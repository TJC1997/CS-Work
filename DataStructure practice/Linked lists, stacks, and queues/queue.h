/*
 * This file contains the definition of an interface for a queue data structure.
 */

#ifndef __QUEUE_H
#define __QUEUE_H

/*
 * Structure used to represent a queue.
 */
struct queue;

/*
 * Creates a new, empty queue and returns a pointer to it.
 */
struct queue* queue_create();

/*
 * Free all of the memory associated with a queue.
 *
 * Params:
 *   queue - the queue to be destroyed.  May not be NULL.
 */
void queue_free(struct queue* queue);

/*
 * Returns 1 if the given queue is empty or 0 otherwise.
 *
 * Params:
 *   queue - the queue whose emptiness is to be checked.  May not be NULL.
 */
int queue_isempty(struct queue* queue);

/*
 * Enqueue a new value onto a queue.
 *
 * Params:
 *   queue - the queue onto which to enqueue a value.  May not be NULL.
 *   value - the new value to be enqueueed onto the queue
 */
void queue_enqueue(struct queue* queue, int value);

/*
 * Returns a queue's front value without removing that value from the queue.
 *
 * Params:
 *   queue - the queue from which to read the front value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Returns the value stored at the front of the queue.
 */
int queue_front(struct queue* queue);

/*
 * Removes the front element from a queue and returns its value.
 *
 * Params:
 *   queue - the queue from which to dequeue a value.  May not be NULL or empty.
 *
 * Return:
 *   Returns the value stored at the front of the queue before that value is
 *   dequeued.
 */
int queue_dequeue(struct queue* queue);

#endif
