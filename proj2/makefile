all: project2_first project2_second

project2_first: hash24 dictionary test_one
	g++ -g hash24.o dictionary.o test_one.o -o project2_first.out

project2_second: hash24 dictionary test_two
	g++ -g hash24.o dictionary.o test_two.o -o project2_second.out

hash24: hash24.cpp
	g++ -g -c hash24.cpp

dictionary: dictionary.cpp
	g++ -g -c dictionary.cpp

test_one: test_one.cpp
	g++ -g -c test_one.cpp

test_two: test_two.cpp
	g++ -g -c test_two.cpp

clean:
	rm *.o