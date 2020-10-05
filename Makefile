
CFLAGS := -Wall --std=c++17 -g -O2

default: a.out


a.out: test.o Function.o Command.o CommandWhileLoop.o
	g++ $(CFLAGS) $^ -o a.out

%.o: %.cpp $(wildcard *.hpp)
	g++ $(CFLAGS) -c $< -o $@

clean:
	rm *.o a.out
