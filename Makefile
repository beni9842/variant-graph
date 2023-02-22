CXX = g++
CXXFLAGS	= -std=c++17 -Wall

all: main

clean:
	rm main graph.o

main: graph.o
	$(CXX) $(CXXFLAGS) main.cpp graph.o -o main

graph.o: graph.cpp
	$(CXX) $(CXXFLAGS) -c graph.cpp

