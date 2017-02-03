CXX=g++
CXXFLAGS=-g -std=c++11 -Wall -pedantic
EXEC=patate

all: $(EXEC)


patate: main.o PFinstance.o Library.o Platform.o Point.o Polynome.o
	$(CXX) -o patate main.o PFinstance.o Library.o Platform.o Point.o Polynome.o $(CXXFLAGS)


Polynome.o: Polynome.cpp Polynome.h
	$(CXX) -o Polynome.o -c Polynome.cpp $(CXXFLAGS)
	
Point.o: Point.cpp Point.h
	$(CXX) -o Point.o -c Point.cpp $(CXXFLAGS)

Platform.o: Platform.cpp Platform.h Point.h
	$(CXX) -o Platform.o -c Platform.cpp $(CXXFLAGS)

Library.o: Library.cpp Library.h Platform.h Point.h
	$(CXX) -o Library.o -c Library.cpp $(CXXFLAGS)

PFinstance.o: PFinstance.cpp PFinstance.h Library.h Platform.h Point.h
	$(CXX) -o PFinstance.o -c PFinstance.cpp $(CXXFLAGS)

main.o: main.cpp PFinstance.h Library.h Platform.h Point.h Polynome.h
	$(CXX) -o main.o -c main.cpp $(CXXFLAGS)


.PHONY: clean mrproper

clean:
	rm -rf *.o
	rm -rf *~

mrproper: clean
	rm -rf $(EXEC)
