.POSIX:
.SUFFIXES:

CC=g++
STD=c++11
CFLAGS=-W -O

GOOGLE_TEST_LIB = gtest
LDLIBS=-lm -l$(GOOGLE_TEST_LIB) -lpthread
INCLUDES=include

all: tests
tests: obj/ntree_tests.o
	$(CC) $(LDFLAGS) $(LDLIBS) -o tests/all obj/ntree_tests.o

win32: tests
	ren tests\all test\all.exe

obj/ntree_tests.o: tests/ntree_tests.cpp include/ntree.hpp
	mkdir -p obj
	$(CC) $(CFLAGS) -I$(INCLUDES) $(LDLIBS) --std=$(STD) -c $< -o $@

clean:
	rm -f tests/all
	rm -rf obj

.PHONY: all clean