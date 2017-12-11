# Assignment 3
**Due by 11:59pm on Monday, 11/13/2017**

**Demo due by 11:59pm on Monday 11/27/2017**

This assignment is intended to have you start working with binary search trees.  There are several parts to the assignment, each described below.

For this assignment, you are provided with some starter code that defines the structures you'll be working with and prototypes the functions you'll be writing.  *It's important that you don't modify the function prototypes.*  To help grade your assignment, we will use a set of unit tests that assume these functions exist and have the same prototypes that are defined in the starter code.  If you change the prototypes, it will cause the unit tests to break, and your grade for the assignment will likely suffer.  Feel free, however, to write any additional functions you need to accomplish the tasks described below.

In this assignment, your work will be limited to the file `bst.c`, where you will implement the functions described below.  In particular, you should write all of your code below the comment in `bst.c` that says "Below are the functions and structures you'll implement in this assignment."  In addition to the descriptions below, there is thorough documentation in `bst.c` describing how each function you'll write should behave.

## 1. Implement a function to determine the size of a BST

For the first part of the assignment, you will implement a function called `bst_size()` that determines the size of a given BST.  Specifically, this function should return the number of nodes in the BST.

> Hint: it could be easier to think recursively.  Feel free to implement any helper functions you need.

## 2. Implement a function to determine the height of a BST

For the second part of the assignment, you will implement a function called `bst_height()` that determines the height of a given BST.  Remember, the height of a tree is the maximum depth of any node in the tree (i.e. the number of edges in the path from the root to that node).

> Hint: again, it could be easier to think recursively.  Feel free to implement any helper functions you need.

## 3. Implement a function to check path sums in a BST

For the third part of the assignment, you will implement a function called `bst_path sum()` that determines whether a BST contains any path from the root to a leaf in which the values of the nodes sum to a specified value.

> Hint: again, it could be easier to think recursively.  Feel free to implement any helper functions you need.

## 4. Implement an in-order iterator for a BST

Finally, you will implement an iterator that returns values from a BST in the same order they would be visited in an in-order traversal of the tree.  For a BST, this will be equivalent to ascending sorted order.  You will have to define a structure `struct bst_iterator` to hold the needed data for your iterator, and then you must implement the following functions:

* `bst_iterator_create()` - allocates and initializes an iterator for a given BST
* `bst_iterator_free()` - frees all memory allocated to a BST iterator
* `bst_iterator_has_next()` - should tell the user whether there are more values in the BST to which to iterate
* `bst_iterator_next()` - should return the next value in the in-order iteration of the BST

>Hint: the key to implementing this iterator is figuring out how to perform an in-order traversal non-recursively, since we can't easily break out of a recursion at a specified step once it's started.  Note that you're provided with a stack implementation in stack.h.  Can you use this to mimic the way a recursive in-order traversal visits nodes in a BST?

## Testing your work

In addition to the starter code provided, you are also provided with some application code in `test.c` to help verify that your functions are behaving the way you want them to.  In particular, the code in `test.c` calls the functions you'll implement in this assignment, passing them appropriate arguments, and then prints the results.  You can use the provided `Makefile` to compile all of the code in the project together, and then you can run the testing code as follows:
```
make
./test
```
You can see some example output from a correct solution to the assignment in the file `example_output.txt`.

In order to verify that your memory freeing functions work correctly, it will be helpful to run the testing application through `valgrind`.

## Submission

As always, we'll be using GitHub Classroom for this assignment, and you will submit your assignment via GitHub. Just make sure your completed files are committed and pushed by the assignment's deadline to the master branch of the GitHub repo that was created for you by GitHub Classroom. A good way to check whether your files are safely submitted is to look at the master branch of your assignment repo on the github.com website (i.e. http://github.com/OSU-CS261-F17/assignment-3-YourGitHubUsername/). If your changes show up there, you can consider your files submitted.

## Grading criteria

The assignment is worth 100 total points, broken down as follows:

* 10 points: `bst_size()` works as described above
* 15 points: `bst_height()` works as described above
* 25 points: `bst_path_sum()` works as described above
* 50 points: your BST iterator correctly implements an in-order iterator over a given BST

Importantly, your code MUST compile and run on one of the ENGR servers, e.g. `flip.engr.oregonstate.edu`.  If your code does not compile there, you will lose 25 points.  Also, you may not modify any of the existing starter code, and you may not re-define any of the existing structures.  You will lose points for doing this, as well.
