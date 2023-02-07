CXXFLAGS := -O3 -mavx -m64 -mtune=sandybridge -march=sandybridge -flto -I./include -Wall -Wpedantic -std=gnu++17
CXX := g++

objects := main.o mem.o

all: test

test: $(objects)
	$(CXX) $(CXXFLAGS) $^ -o $@

main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) $^ -c -o $@

mem.o: src/mem.cpp
	$(CXX) $(CXXFLAGS) $^ -c -o $@