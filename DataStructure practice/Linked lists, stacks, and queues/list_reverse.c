/*
 * This is the file in which you'll write a function to reverse a linked list.
 * Make sure to add your name and @oregonstate.edu email address below:
 *
 * Name:
 * Email:
 */

#include <stdio.h>

#include "list_reverse.h"

/*
 * In this function, you will be passed the head of a singly-linked list, and
 * you should reverse the linked list and return the new head.  The reversal
 * must be done in place, and you may not allocate any new memory in this
 * function.
 *
 * Params:
 *   head - the head of a singly-linked list to be reversed
 *
 * Return:
 *   Should return the new head of the reversed list.  If head is NULL, this
 *   function should return NULL.
 */
struct link* list_reverse(struct link* head) {
  if(head==NULL)
  {
    return NULL;//check if head is NULL
  }
  int size=0;
  struct link *tail,*search,*end;
  for(tail=head;tail->next!=NULL;tail=tail->next)  
  {
    size++;//get the size of list
  }
  end=tail;//set end point to the last list
  for(int i=0;i<size;i++)
  {
    search=head;
    while(search->next!=end)
    {
      search=search->next;//find the list before the end list
    }
    end->next=search;//reverse:let the end list point to the last list
    end=end->next;//set new end
  }
  head->next=NULL;
  head=tail;
  return head;

}