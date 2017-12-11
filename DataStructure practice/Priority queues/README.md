# Assignment 4
**Due by 11:59pm on Monday, 11/27/2017**

**Demo due by 11:59pm on Friday 12/8/2017**

In this assignment, you will implement a complete heap-based priority queue.  In addition to the description of your task below, there is thorough documentation in the file `pq.c` describing how each function you'll write should behave.

Your work for this assignment will be limited to the file `pq.c`.  In other files, you are provided with some additional starter code that defines the structures you'll be working with and prototypes functions you'll be using and writing.  *It's important that you don't modify the function prototypes.*  To help grade your assignment, we will use a set of unit tests that assume these functions exist and have the same prototypes that are defined in the starter code.  If you change the prototypes, it will cause the unit tests to break, and your grade for the assignment will likely suffer.  Feel free, however, to write any additional functions you need to accomplish the tasks described below.

## Implement a heap-based priority queue

Your task for this assignment is to implement a heap-based priority queue.  Specifically, in the file `pq.c`, you must define the `struct pq` and implement the following functions:

  * `pq_create()` - allocates and initializes a heap-based priority queue
  * `pq_free()` - frees all memory allocated to a priority queue
  * `pq_isempty()` - should tell the user whether a priority queue is empty
  * `pq_insert()` - should insert an element with a specified priority value into a priority queue
  * `pq_first()` - should return the value of the first element in a priority queue
  * `pq_first_priority()` - should return the *priority value* associated with the first element in a priority queue
  * `pq_remove_first()` - should remove the first element from a priority queue and return its value

Here are some specific notes on how the priority queue you'll implement should behave:

  * Your priority queue must be implemented using a heap as the underlying data structure.

  * In the priority queue you implement, *lower* priority values should correspond to elements with *higher* priority.  In other words, the first element in the priority queue should be the one with the *lowest* priority value among all elements in the collection.  For example, your priority queue should return an element with priority value 0 before it returns one with priority value 10.

  * Your `pq_insert()` and `pq_remove_first()` functions should both be *O(log n)*, and your `pq_first()` and `pq_first_priority()` functions should both be *O(1)*.

  * Your priority queue should not have any memory leaks.

  * In lecture, we discussed how you can implement a heap using an array.  In `dynarray.c` and `dynarray.h`, you are provided with a dynamic array implementation you can use to implement your heap, if you'd like.  In addition to this dynamic array implementation, you may implement any additional helper functions you need to make your priority queue work.

## Testing your work

In addition to the starter code provided, you are also provided with some application code in `test.c` to help verify that your functions are behaving the way you want them to.  In particular, the code in `test.c` calls the functions you'll implement in this assignment, passing them appropriate arguments, and then prints the results.  You can use the provided `Makefile` to compile all of the code in the project together, and then you can run the testing code as follows:
```
make
./test
```
You can see some example output from a correct solution to the assignment in the file `example_output.txt`.

In order to verify that your memory freeing functions work correctly, it will be helpful to run the testing application through `valgrind`.

## Submission

As always, we'll be using GitHub Classroom for this assignment, and you will submit your assignment via GitHub. Just make sure your completed files are committed and pushed by the assignment's deadline to the master branch of the GitHub repo that was created for you by GitHub Classroom. A good way to check whether your files are safely submitted is to look at the master branch of your assignment repo on the github.com website (i.e. http://github.com/OSU-CS261-F17/assignment-4-YourGitHubUsername/). If your changes show up there, you can consider your files submitted.

## Grading criteria

The assignment is worth 100 total points, broken down as follows:

* 5 points: `struct pq` defines a heap-based priority queue
* 5 points: `pq_create()` correctly allocates and initializes a heap-based priority queue
* 5 points: `pq_free()` correctly frees all memory associated with a priority queue (no memory leaks!)
* 5 points: `pq_isempty()` correctly determines whether a priority queue contains any elements or not
* 5 points: `pq_first()` correctly returns the value in a priority queue with the *lowest* priority value
* 5 points: `pq_first_priority()` correctly returns the *lowest* priority value in a priority queue
* 30 points: `pq_insert()` correctly inserts a value into a priority queue with the specified priority and restores the heap property as needed
* 30 points: `pq_remove_first()` correctly removes the element with the *lowest* priority from a priority queue and returns its value, restoring the heap property as needed
* 10 points: `pq_insert()` and `pq_remove_first()` are both *O(log n)*, and `pq_first()` and `pq_first_priority()` are both *O(1)*

Importantly, your code MUST compile and run on one of the ENGR servers, e.g. `flip.engr.oregonstate.edu`.  If your code does not compile there, you will lose 25 points.  Also, you may not modify any of the existing starter code, and you may not re-define any of the existing structures.  You will lose points for doing this, as well.
