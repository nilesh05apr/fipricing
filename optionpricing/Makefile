CXX=g++
CXXFLAGS=-Wall -Wextra -std=c++11

SRCS=$(wildcard *.cpp)

all: $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

run: all
	./all

.PHONY: clean
clean:
	rm -f all
