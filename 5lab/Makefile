CXX = clang++
CXXFLAGS = -O3 -Wall

SRC = src/main.cpp

all: build run plot

build:
	$(CXX) $(SRC) $(CXXFLAGS)

run:
	./a.out

clean:
	rm -rf a.out data
