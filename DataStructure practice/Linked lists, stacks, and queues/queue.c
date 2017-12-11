/*
 * This file contains the definitions of structures and functions implementing
 * a simple queue using a linked list.
 */

#include <stdlib.h>
#include <assert.h>

#include "link.h"
#include "queue.h"

/*
 * This is the definition of the queue structure.  Using a linked list to
 * implement a queue requires that we keep track of both the head and the
 * tail of the queue.
 */
struct queue {
  struct link* head;
  struct link* tail;
};


struct queue* queue_create() {
  struct queue* queue = malloc(sizeof(struct queue));
  assert(queue);
  queue->head = NULL;
  queue->tail = NULL;
  return queue;
}


void queue_free(struct queue* queue) {
  assert(queue);

  /*
   * Here, we're assuming that queue_dequeue() handles freeing the memory
   * associated with each dequeued element.
   */
  while (!queue_isempty(queue)) {
    queue_dequeue(queue);
  }
  free(queue);
}


int queue_isempty(struct queue* queue) {
  assert(queue);
  return queue->head == NULL;
}


void queue_enqueue(struct queue* queue, int value) {
  assert(queue);
  struct link* new_link = malloc(sizeof(struct link));
  assert(new_link);

  /*
   * Fill out the new link at put it at the tail of the list, which represents
   * the top of the queue.
   */
  new_link->value = value;
  new_link->next = NULL;
  if (queue->tail) {
    queue->tail->next = new_link;
  }
  queue->tail = new_link;

  // If we didn't have a head link before, set the head to this new link, too.
  if (!queue->head) {
    queue->head = new_link;
  }
}


int queue_front(struct queue* queue) {
  assert(queue && queue->head);
  return queue->head->value;
}


int queue_dequeue(struct queue* queue) {
  assert(queue && queue->head);

  /*
   * Remove the old front element from the list and remember its value before
   * we free it.
   */
  struct link* dequeued_head = queue->head;
  int value = dequeued_head->value;
  queue->head = dequeued_head->next;

  /*
   * If the dequeued head was also the tail, set the tail to NULL.
   */
  if (queue->tail == dequeued_head) {
    queue->tail = NULL;
  }

  free(dequeued_head);
  return value;
}
