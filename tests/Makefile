INCLUDES=-I../include -I$${HOME}/Code/cpp_workbench/external/googletest/googletest/include
LIB_LOCATIONS=-L$${HOME}/Code/cpp_workbench/external/googletest/build/lib -L../build/lib
TEST_LIBS=-lgtest -lgtest_main -lpthread -lanvil

# https://stackoverflow.com/questions/7815400/how-do-i-make-makefile-to-recompile-only-changed-files
# detecting leaks:
# https://www.osc.edu/resources/getting_started/howto/howto_use_address_sanitizer
OBJDIR=-o .obj/$@
CC=clang++ -g -O0 -std=c++17
CPPFLAGS=-Wall -Wextra $(INCLUDES)
SRC_FILES := $(wildcard *.cpp)
OBJ_FILES := $(patsubst %.cpp,%.o,$(SRC_FILES))

SRC_DIR := ./
OBJ_DIR := build/obj
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

default:
	$(MAKE) dirs tests

all: 
	$(MAKE) dirs tests
dirs:
	mkdir -p build/obj build/bin

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CPPFLAGS) -c -o $@ $<

tests: $(OBJ_FILES)
	$(CC) $(CFLAGS) $(LIB_LOCATIONS) $(TEST_LIBS) build/obj/*.o -o build/bin/tests 

clean:
	rm -rf build