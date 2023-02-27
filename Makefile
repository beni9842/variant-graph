CXX = g++
CXXFLAGS	= -std=c++17 -Wall -O3

all: main

clean:
	rm variant_graph graph.o

main: graph.o
	$(CXX) $(CXXFLAGS) main.cpp graph.o -o variant_graph

graph.o: graph.cpp
	$(CXX) $(CXXFLAGS) -c graph.cpp

