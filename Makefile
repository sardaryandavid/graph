CC=g++
CFLAGS= -Wall -Wall -Wextra -Wpedantic -Werror -lgtest -pthread -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment -fsanitize=address

all: main

main: main.o stack.o graph.o
	$(CC) main.o stack.o graph.o -o main $(CFLAGS)


# Download gTest:
# sudo apt-get install libgtest-dev
# sudo apt-get install libtbb-dev

tests: tests.cpp graph.cpp stack.cpp
	$(CC) tests.cpp graph.cpp stack.cpp -o tests $(CFLAGS)

tests.o: tests.cpp
	$(CC) -c tests.cpp $(CFLAGS)

main.o: main.cpp
	$(CC) -c main.cpp $(CFLAGS)

graph.o: graph.cpp
	$(CC) -c graph.cpp $(CFLAGS)

stack.o: stack.cpp
	$(CC) -c stack.cpp $(CFLAGS)

clean:
	rm -rf *.o main