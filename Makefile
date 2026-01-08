CXX=clang++
CXXFLAGS=-std=c++20 -g -Wall -I.

SRCS=main.cpp orderBook.cpp pricing.cpp orderIncrement.cpp
TEST_SRCS=tests/test.cpp orderBook.cpp pricing.cpp orderIncrement.cpp

.PHONY: all build main test clean

all: main

build: main

main: $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o main

test: $(TEST_SRCS)
	$(CXX) $(CXXFLAGS) $(TEST_SRCS) -o test
	./test

clean:
	rm -f main test
