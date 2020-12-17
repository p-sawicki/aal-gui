CC=g++
CFLAGS=-I inc -Wall --std=c++17 -O3

default: all
all: dp graph gen tests timer bf

# Dynamic-programming solution
dp.o: dp/dp.cpp 
	$(CC) $(CFLAGS) -c dp/dp.cpp -o dp/dp.o
dp: dp/dp_main.cpp dp.o utils.o
	$(CC) $(CFLAGS) dp/dp.o dp/dp_main.cpp utils/utils.o -o bin/dp

# Graph solution
graph.o: inc/graph.h graph/graph.cpp
	$(CC) $(CFLAGS) -c graph/graph.cpp -o graph/graph.o
graph: graph/graph_main.cpp graph.o utils.o
	$(CC) $(CFLAGS) graph/graph.o graph/graph_main.cpp utils/utils.o -o bin/graph

# Brute-force solution
bf.o: inc/bf.h bf/bf.cpp
	$(CC) $(CFLAGS) -c bf/bf.cpp -o bf/bf.o
bf: bf/bf_main.cpp bf.o utils.o
	$(CC) $(CFLAGS) bf/bf.o bf/bf_main.cpp utils/utils.o -o bin/bf

# Tests generator
gen.o: inc/gen.h gen/gen.cpp
	$(CC) $(CFLAGS) -c gen/gen.cpp -o gen/gen.o
gen: gen/gen_main.cpp gen.o
	$(CC) $(CFLAGS) gen/gen_main.cpp gen/gen.o -o bin/gen

# Misc functions
utils.o: inc/utils.h utils/utils.cpp
	$(CC) $(CFLAGS) -c utils/utils.cpp -o utils/utils.o

# Trivial tests suite
tests: tests.cpp dp.o gen.o graph.o utils.o bf.o
	$(CC) $(CFLAGS) tests.cpp dp/dp.o gen/gen.o graph/graph.o utils/utils.o bf/bf.o -o bin/tests

# Auto-tests runner with timer
timer: timer.cpp gen.o dp.o graph.o utils.o bf.o
	$(CC) $(CFLAGS) timer.cpp gen/gen.o dp/dp.o graph/graph.o utils/utils.o bf/bf.o -o bin/timer

.PHONY: clean
clean:
	rm -f bin/* **/*.o
