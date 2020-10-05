
CFLAGS := -Wall --std=c++17 -g -fPIC -O2

default: a.out

libsimplemath.so: Function.o Command.o CommandWhileLoop.o AssemblyCode.s.o
	g++ $(CFLAGS) $^ -shared -o $@

a.out: test.o libsimplemath.so
	g++ $(CFLAGS) test.o -o a.out -L. -l:libsimplemath.so -Wl,-rpath=/home/zachary/Programming/simple_math_compiler
	g++ $(CFLAGS) test.o -o a.out -L. -l:libsimplemath.so -Wl,-rpath=.

%.o: %.cpp $(wildcard *.hpp)
	g++ $(CFLAGS) -c $< -o $@

%.s.o: %.s
	g++ $(CFLAGS) -c $< -o $@

clean:
	rm *.o a.out *.so
