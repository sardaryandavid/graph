CC=g++
CFLAGS= -Wall -Wall -Wextra -Wpedantic -Werror -lgtest -pthread

all: main

main: main.o stack.o graph.o
	$(CC) main.o stack.o graph.o -o main

tests: tests.cpp graph.cpp stack.cpp
	$(CC) $(CFLAGS) tests.cpp graph.cpp stack.cpp -o tests

tests.o: tests.cpp
	$(CC) -c $(CFLAGS) tests.cpp

main.o: main.cpp
	$(CC) -c $(CFLAGS) main.cpp

graph.o: graph.cpp
	$(CC) -c $(CFLAGS) graph.cpp

stack.o: stack.cpp
	$(CC) -c $(CFLAGS) stack.cpp

clean:
	rm -rf *.o main