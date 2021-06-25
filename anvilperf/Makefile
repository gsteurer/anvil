INCLUDES=-I../anvil/include
LIB_LOCATIONS=-L../anvil/lib
TEST_LIBS=-lanvil

# https://stackoverflow.com/questions/7815400/how-do-i-make-makefile-to-recompile-only-changed-files
# detecting leaks:
# https://www.osc.edu/resources/getting_started/howto/howto_use_address_sanitizer
OBJDIR=-o .obj/$@
CC=clang++ -g -O0 -std=c++17
CFLAGS=-Wall -Wextra $(INCLUDES)
SRC_FILES := $(wildcard *.cpp)
OBJ_FILES := $(patsubst %.cpp,%.o,$(SRC_FILES))

default:
	$(MAKE) dirs tests

dirs:
	mkdir -p .obj bin

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o .obj/$@ $<

tests: $(OBJ_FILES)
	$(CC) $(CFLAGS) $(LIB_LOCATIONS) $(TEST_LIBS) .obj/*.o -o bin/tests 

clean:
	rm -rf bin .obj