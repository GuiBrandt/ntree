.POSIX:
.SUFFIXES:
CC=g++
STD=c++11
CFLAGS=-W -O
LDLIBS=-lm -lgtest
INCLUDES=include

all: tests
tests: obj/ntree_tests.o
	$(CC) $(LDFLAGS) $(LDLIBS) -o ntree_tests obj/ntree_tests.o

obj/ntree_tests.o: tests/ntree_tests.cpp include/ntree.hpp
	mkdir -p obj
	$(CC) $(CFLAGS) -I$(INCLUDES) $(LDLIBS) --std=$(STD) -c $< -o $@

clean:
	rm -f ntree_tests
	rm -rf obj