CC = gcc
FLAGS = -Wall -ansi -g -Iincludes

all: run1.o run2.o run3.o
	$(CC) $(FLAGS) -o contactList bin/run1.o bin/run2.o bin/run3.o

run1.o: src/contactListApp.c includes/contactDefs.h
	$(CC) $(FLAGS) -c src/contactListApp.c -o bin/run1.o

run2.o: src/stringHandling.c
	$(CC) $(FLAGS) -c src/stringHandling.c -o bin/run2.o

run3.o: src/sortingAlgorithms.c
	$(CC) $(FLAGS) -c src/sortingAlgorithms.c -o bin/run3.o

run: all
	./contactList

memtest: all
	valgrind ./contactListApp

clean:
	rm bin/*
	rm ./contactListApp
	rm ./*.db

cppcheck: 
	cppcheck --enable=all --language=c --std=c99 --inconclusive --suppress=missingInclude src/*.c
