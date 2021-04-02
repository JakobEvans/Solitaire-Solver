# Jakob Evans Makefile
# CS315 Section 1
# Makefile for Lab11
# Linking
easyexec: lab11.o
	g++ -o easyexec lab11.o


# Compilation
Lab11.o: lab11.cpp SeparateChaining.cpp
	g++ -c lab11.cpp
