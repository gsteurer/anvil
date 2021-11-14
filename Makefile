INCLUDES=-Iinclude

#https://stackoverflow.com/questions/7815400/how-do-i-make-makefile-to-recompile-only-changed-files

OBJDIR=build/obj
CC=clang++ -g -O0 -std=c++17
CFLAGS=-Wall -Wextra $(INCLUDES)

default:
	$(MAKE) dirs libanvil
	
all:
	$(MAKE) dirs libanvil
	
dirs:
	mkdir -p $(OBJDIR) build/lib

mat4x4f.o: src/anvil/math/mat4x4f.cpp
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$@ $<

vec4f.o: src/anvil/math/vec4f.cpp
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$@ $<

cstring.o: src/anvil/string/cstring.cpp
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$@ $<

string.o: src/anvil/string/string.cpp
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$@ $<

stlutils.o: src/anvil/string/stlutils.cpp
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$@ $<

wavefront.o: src/anvil/file/wavefront.cpp
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$@ $<

libanvil: mat4x4f.o vec4f.o cstring.o string.o stlutils.o wavefront.o
	ar rvs build/lib/$@.a $(OBJDIR)/*.o

clean:
	rm -rf build