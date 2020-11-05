all: project2_first

project2_first: hash24 dictionary test_one
	g++ -g hash24.o dictionary.o test_one.o -o project2_first.out

hash24: hash24.cpp
	g++ -g -c hash24.cpp

dictionary: dictionary.cpp
	g++ -g -c dictionary.cpp

test_one: test_one.cpp
	g++ -g -c test_one.cpp

clean:
	rm *.o