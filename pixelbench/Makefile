INCLUDES=-Iinclude

#https://stackoverflow.com/questions/7815400/how-do-i-make-makefile-to-recompile-only-changed-files

OBJDIR=-o .obj/$@
CC=g++ -g -O0 -std=c++17
CFLAGS=-Wall $(INCLUDES)

default:
	$(MAKE) dirs main
	
dirs:
	mkdir -p .obj bin

main.o: 
	$(CC) $(CFLAGS) -c -o .obj/$@ main.cpp

main: main.o
	$(CC) $(CFLAGS) .obj/*.o -o bin/main

clean:
	rm -rf bin .obj