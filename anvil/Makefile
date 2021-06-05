INCLUDES=-Iinclude

#https://stackoverflow.com/questions/7815400/how-do-i-make-makefile-to-recompile-only-changed-files

OBJDIR=-o .obj/$@
CC=g++ -g -O0 -std=c++17
CFLAGS=-Wall $(INCLUDES)

default:
	$(MAKE) dirs lib
	
dirs:
	mkdir -p .obj lib

mat.o: 
	$(CC) $(CFLAGS) -c -o .obj/$@ src/math/mat.cpp

util.o: 
	$(CC) $(CFLAGS) -c -o .obj/$@ src/math/util.cpp

vec.o: 
	$(CC) $(CFLAGS) -c -o .obj/$@ src/math/vec.cpp

lib: mat.o util.o vec.o
	ar rvs lib/libanvil.a .obj/*.o

clean:
	rm -rf lib .obj