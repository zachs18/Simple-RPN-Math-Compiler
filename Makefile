
CFLAGS := -Wall --std=c++17 -g -fPIC -O2

default: a.out

libsimplemath.so: Function.o Command.o CommandWhileLoop.o AssemblyCode.s.o
	$(CXX) $(CFLAGS) $^ -shared -o $@

a.out: test.o libsimplemath.so
	$(CXX) $(CFLAGS) test.o -o a.out -L. -l:libsimplemath.so -Wl,-rpath=/home/zachary/Programming/simple_math_compiler
	$(CXX) $(CFLAGS) test.o -o a.out -L. -l:libsimplemath.so -Wl,-rpath=.

%.o: %.cpp $(wildcard *.hpp)
	$(CXX) $(CFLAGS) -c $< -o $@

%.s.o: %.s
	$(CXX) $(CFLAGS) -c $< -o $@

clean:
	rm *.o a.out *.so
