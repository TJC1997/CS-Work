CC=gcc --std=c99 -g

all: test

test: test.c bst.o stack.o
	$(CC) test.c bst.o stack.o -o test

bst.o: bst.c bst.h
	$(CC) -c bst.c

stack.o: stack.c stack.h
	$(CC) -c stack.c

clean:
	rm -rf *.dSYM/
	rm -f *.o test
