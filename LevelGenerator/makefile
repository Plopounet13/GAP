CXX=g++
CXXFLAGS=-g -std=c++11 -Wall -pedantic
EXEC=patate

all: $(EXEC)
OBJS = main.o Library/Library.o Library/Platform.o Library/Point4.o Polynome.o Instance/Instance.o Instance/PlatInstance.o Instance/Position.o Instance/Vec3.o levelGenerator.o


patate: $(OBJS)
	$(CXX) -o patate $(OBJS) $(CXXFLAGS)



Library/Point4.o: Library/Point4.cpp Library/Point4.h
	$(CXX) -o Library/Point4.o -c Library/Point4.cpp $(CXXFLAGS)

Library/Platform.o: Library/Platform.cpp Library/Platform.h Library/Point4.h
	$(CXX) -o Library/Platform.o -c Library/Platform.cpp $(CXXFLAGS)

Library/Library.o: Library/Library.cpp Library/Library.h Library/Platform.h Library/Point4.h
	$(CXX) -o Library/Library.o -c Library/Library.cpp $(CXXFLAGS)



Instance/Instance.o: Instance/Instance.cpp Instance/Instance.h Instance/PlatInstance.h Instance/Position.h Instance/Vec3.h
	$(CXX) -o Instance/Instance.o -c Instance/Instance.cpp $(CXXFLAGS)

Instance/PlatInstance.o: Instance/PlatInstance.cpp Instance/PlatInstance.h Instance/Position.h Instance/Vec3.h
	$(CXX) -o Instance/PlatInstance.o -c Instance/PlatInstance.cpp $(CXXFLAGS)

Instance/Position.o: Instance/Position.cpp Instance/Position.h Instance/Vec3.h
	$(CXX) -o Instance/Position.o -c Instance/Position.cpp $(CXXFLAGS)

Instance/Vec3.o: Instance/Vec3.cpp Instance/Vec3.h
	$(CXX) -o Instance/Vec3.o -c Instance/Vec3.cpp $(CXXFLAGS)



Polynome.o: Polynome.cpp Polynome.h
	$(CXX) -o Polynome.o -c Polynome.cpp $(CXXFLAGS)

levelGenerator.o: levelGenerator.cpp levelGenerator.h Library/Library.h Library/Platform.h Library/Point4.h Polynome.h Instance/Instance.h Instance/PlatInstance.h Instance/Position.h Instance/Vec3.h
	$(CXX) -o levelGenerator.o -c levelGenerator.cpp $(CXXFLAGS)



main.o: main.cpp levelGenerator.h Library/Library.h Library/Platform.h Library/Point4.h Polynome.h Instance/Instance.h Instance/PlatInstance.h Instance/Position.h Instance/Vec3.h
	$(CXX) -o main.o -c main.cpp $(CXXFLAGS)






.PHONY: clean mrproper

clean:
	rm -rf *.o
	rm -rf *~
	rm -rf Library/*.o
	rm -rf Library/*~
	rm -rf Instance/*.o
	rm -rf Instance/*~

mrproper: clean
	rm -rf $(EXEC)