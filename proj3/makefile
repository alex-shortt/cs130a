all: kavl project3

project3: kavl test
	g++ -g kavl.o test.o -o project3.out

test: test.cpp
	g++ -g -c test.cpp

kavl: kavl.cpp
	g++ -g -c kavl.cpp

clean:
	rm *.o