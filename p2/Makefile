all:treeins_test

treeins_test: treeins_test.o recursive.o p2.o
	g++ -o treeins_test treeins_test.o recursive.o p2.o

treeins_test.o: treeins_test.cpp
	g++ -c treeins_test.cpp

p2.o: p2.cpp
	g++ -c p2.cpp

recursive.o: recursive.cpp
	g++ -c recursive.cpp

clean:
	sudo rm -f *.o