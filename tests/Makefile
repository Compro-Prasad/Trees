CC = g++
CXX = $(CC)

CFLAGS = -g -DTESTING

all: avlTest bstTest

avlTest: avlTest.cpp ../avlBranch.hpp ../tree.hpp
	$(CC) $(CFLAGS) $< -o $@

bstTest: bstTest.cpp ../bstBranch.hpp ../tree.hpp
	$(CC) $(CFLAGS) $< -o $@
