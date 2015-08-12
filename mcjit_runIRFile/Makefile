



all: hello_world.ll
	g++ -g main.cpp `llvm-config --cxxflags --ldflags --system-libs --libs core mcjit native irreader` -rdynamic -O0 -o test


%.ll : %.cpp
	clang -fno-use-cxa-atexit -emit-llvm -S $< -o $@


clean:
	rm hello_world.ll test -rf

