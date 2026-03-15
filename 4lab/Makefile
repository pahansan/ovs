CXX = clang++
CXXFLAGS = -O3 -Wall

SRC = src/main.cpp

all: build run plot

build:
	$(CXX) $(SRC) $(CXXFLAGS)

run:
	./a.out

plot:
	gnuplot plots/exp2_1/theta.gnu
	gnuplot plots/exp2_2/theta.gnu
	gnuplot plots/exp2_3/theta.gnu
	gnuplot plots/exp3_1/T.gnu
	gnuplot plots/exp3_2/T.gnu
	gnuplot plots/exp3_3/T.gnu
	@echo "Graphs saved in graphs/ folder"

clean:
	rm -rf a.out data graphs
