/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name:
 * Email:
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "dynarray.h"
#include "pq.h"

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
struct pq
{
  struct dynarray*pri;//pri is priority
  struct dynarray*data;//data is actual value
};

/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
  struct pq* pq=malloc(sizeof(struct pq));
  pq->pri=dynarray_create();
  pq->data=dynarray_create();
  return pq;
}


/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {
  assert(pq);
  int size=dynarray_size(pq->pri);//get the size of pri array
  for(int i=0;i<size;i++)//free all the element in pri array
  {
    void * p=dynarray_get(pq->pri,i);
    free(p);
  }
  dynarray_free(pq->pri);
  dynarray_free(pq->data);
  free(pq);
}


/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
  assert(pq);
  //int size=pq->d->size;
  int size=dynarray_size(pq->pri);
  if(size==0)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}


/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */
void swap(struct pq*pq,int a,int b)
{
  void* apri=dynarray_get(pq->pri,a);
  void* bpri=dynarray_get(pq->pri,b);
  void* adata=dynarray_get(pq->data,a);
  void* bdata=dynarray_get(pq->data,b);

  dynarray_set(pq->pri,a,bpri);
  dynarray_set(pq->pri,b,apri);
  dynarray_set(pq->data,a,bdata);
  dynarray_set(pq->data,b,adata);
}

void pq_insert(struct pq* pq, void* value, int priority) {
  assert(pq);
  int size=dynarray_size(pq->pri);//size is son index
  int* pri=malloc(sizeof(int));//since priority is local var, we need to store it into the heap
  *pri=priority;
  dynarray_insert(pq->pri,size,pri);
  dynarray_insert(pq->data,size,value);
  int sonindex=size;

  if(sonindex>0)//if sonindex is 0, which hits the top, it does not have a father
  {
    int fatherindex=(sonindex-1)/2;//get the father index
    int sonpri=*(int*)dynarray_get(pq->pri,sonindex);
    int fatherpri=*(int*)dynarray_get(pq->pri,fatherindex);
    
    while(sonpri<fatherpri)
    {
      swap(pq,sonindex,fatherindex);//swap son and father
      sonindex=fatherindex;//update sonindex to father
      if(sonindex==0)
      {
        break;
      }
      fatherindex=(sonindex-1)/2;
      sonpri=*(int*)dynarray_get(pq->pri,sonindex);
      fatherpri=*(int*)dynarray_get(pq->pri,fatherindex);
    }
  }
}
/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) {
  return dynarray_get(pq->data,0);
}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {
  return *(int*)dynarray_get(pq->pri,0);
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_remove_first(struct pq* pq) {
  void* f=dynarray_get(pq->data,0);//get the first actual value in data
  void* p=dynarray_get(pq->pri,0);//get the first element in pri
  free(p);
  int lastindex=dynarray_size(pq->pri)-1;//get the lastindex in array

  void* lastpri=dynarray_get(pq->pri,lastindex);//the last value in priority
  void* lastdata=dynarray_get(pq->data,lastindex);//the last value in actual data
  dynarray_remove(pq->pri,lastindex);
  dynarray_remove(pq->data,lastindex);//remove the last value in array
  int size=dynarray_size(pq->pri);
  if(size==0)//if we do not have any element left, we return the last element directly
  {
    return f;
  }
  dynarray_set(pq->pri,0,lastpri);//replace the first element with last element
  dynarray_set(pq->data,0,lastdata);

  int father=0;
  int left=father*2+1;
  int right=father*2+2;
  int maxindex=dynarray_size(pq->pri)-1;//get the maxindex
  while(left<=maxindex || right<=maxindex)
  {
    if(left==maxindex)//special case,only have left 
    {
      int fatherpri=*(int*)dynarray_get(pq->pri,father);
      int leftpri=*(int*)dynarray_get(pq->pri,left);
      if(fatherpri>leftpri)
      {
        swap(pq,father,left);
      }
      break;
    }
    else//normal case, have both left and right
    {
      int fatherpri=*(int*)dynarray_get(pq->pri,father);
      int leftpri=*(int*)dynarray_get(pq->pri,left);
      int rightpri=*(int*)dynarray_get(pq->pri,right);
      if(leftpri<=rightpri)//find the smaller one between right and left
      {
        if(fatherpri>leftpri)
        {
          swap(pq,father,left);
          father=left;
          left=father*2+1;
          right=father*2+2;//update father,left,right
        }
        else
        {
          break;
        }
      }
      else
      {
        if(fatherpri>rightpri)
        {
          swap(pq,father,right);
          father=right;
          left=father*2+1;
          right=father*2+2;
        }
        else
        {
          break;
        }
      }
    }
  }
  return f;//return the first actual data
}