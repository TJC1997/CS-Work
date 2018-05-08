CC = g++
e = run
$(e):main.o hash.o
	$(CC) main.o hash.o -g -o $(e)
	rm -f *.o
main.o: main.cpp
	$(CC) -c main.cpp
pizza.o:hash.cpp
	$(CC) -c hash.cpp
clean:
	rm -f *.out *.o $(e)