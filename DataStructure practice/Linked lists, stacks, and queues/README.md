# Assignment 2
**Due by 11:59pm on Monday, 10/23/2017**

**Demo due by 11:59pm on Monday 11/6/2017**

This assignment is intended to have you start working with stacks, queues, and linked lists.  There are several parts to the assignment, each described below.

For this assignment, you are provided with some starter code that defines the structures you'll be working with and prototypes the functions you'll be writing.  *It's important that you don't modify the function prototypes.*  To help grade your assignment, we will use a set of unit tests that assume these functions exist and have the same prototypes that are defined in the starter code.  If you change the prototypes, it will cause the unit tests to break, and your grade for the assignment will likely suffer.  Feel free, however, to write any additional functions you need to accomplish the tasks described below.

In this assignment, your work will be limited to the files `list_reverse.c`, `queue_from_stacks.c`, and `stack_from_queues.c`, where you will implement the functions described below. In addition to the descriptions below, there is thorough documentation in these files describing how each function should behave.

## 1. Implement a function to reverse a linked list in place

In `link.h`, a simple structure implementing a link in a singly-linked list is defined.  For this part of the assignment, you will implement a function called `list_reverse()` that takes as an argument a single link structure representing the head of a linked list, reverses that list, and returns the new head of the reversed list.  This function is prototyped in `list_reverse.h`, and you will implement it in `list_reverse.c`.  **Importantly, you must perform the list reversal in place and may not allocate any new memory in this function.**

## 2. Implement a queue using two stacks

In the files `stack.h` and `stack.c`, a simple stack data structure is implemented.  For the second part of this assignment, you will use two instances of this stack data structure to implement a queue.  The interface of your queue-from-stacks is defined in `queue_from_stacks.h`, and you must complete each of the functions implementing the queue-from-stacks in `queue_from_stacks.c`.  Each of the functions in `queue_from_stacks.c` has a function header comment that describes more precisely how it should behave.

Importantly, you may only use the functions prototyped in `stack.h` to interface with your two stacks, and you may not access the underlying data directly.  Also, make sure your queue-from-stacks implementation does not have any memory leaks!

> Hint: think of one stack as an "inbox" and one stack as an "outbox".

## 3. Implement a stack using two queues

In the files `queue.h` and `queue.c`, a simple queue data structure is implemented.  For the third part of this assignment, you will use two instances of this queue data structure to implement a stack.  The interface of your stack-from-queues is defined in `stack_from_queues.h`, and you must complete each of the functions implementing the stack-from-queues in `stack_from_queues.c`.  Each of the functions in `stack_from_queues.c` has a function header comment that describes more precisely how it should behave.

Importantly, you may only use the functions prototyped in `queue.h` to interface with your two queues, and you may not access the underlying data directly.  Also, make sure your stack-from-queues implementation does not have any memory leaks!

> Hint: there are two possible implementations of the queue-from-stacks, one with an expensive pop operation and an efficient push operation, and one with an expensive push operation and an efficient pop operation.  Whichever of these you choose to implement, the key is knowing where in your two queues the most recently pushed element is.

## Testing your work

In addition to the starter code provided, you are also provided with some application code in `test.c` to help verify that your functions are behaving the way you want them to.  In particular, the code in `test.c` calls the functions you'll implement in this assignment, passing them appropriate arguments, and then prints the results.  You can use the provided `Makefile` to compile all of the code in the project together, and then you can run the testing code as follows:
```
make
./test
```
You can see some example output from a correct solution to the assignment in the file `example_output.txt`.

In order to verify that your memory freeing functions work correctly, it will be helpful to run the testing application through `valgrind`.

## Submission

As always, we'll be using GitHub Classroom for this assignment, and you will submit your assignment via GitHub. Just make sure your completed files are committed and pushed by the assignment's deadline to the master branch of the GitHub repo that was created for you by GitHub Classroom. A good way to check whether your files are safely submitted is to look at the master branch of your assignment repo on the github.com website (i.e. http://github.com/OSU-CS261-F17/assignment-2-YourGitHubUsername/). If your changes show up there, you can consider your files submitted.

## Grading criteria

The assignment is worth 100 total points, broken down as follows:

* 20 points: `list_reverse()` works as described above
* 40 points: all functions in your queue-from-stacks implementation correctly implement a queue
* 40 points: all functions in your stack-from-queues implementation correctly implement a stack
