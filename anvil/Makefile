INCLUDES=-Iinclude

#https://stackoverflow.com/questions/7815400/how-do-i-make-makefile-to-recompile-only-changed-files

OBJDIR=-o .obj/$@
CC=g++ -g -O0 -std=c++17
CFLAGS=-Wall $(INCLUDES)

default:
	$(MAKE) dirs lib
	
dirs:
	mkdir -p .obj lib

mat4x4f.o: 
	$(CC) $(CFLAGS) -c -o .obj/$@ src/math/mat4x4f.cpp

util.o: 
	$(CC) $(CFLAGS) -c -o .obj/$@ src/math/util.cpp

vec4f.o: 
	$(CC) $(CFLAGS) -c -o .obj/$@ src/math/vec4f.cpp

lib: mat4x4f.o util.o vec4f.o
	ar rvs lib/libanvil.a .obj/*.o

clean:
	rm -rf lib .obj