PROG = WorldGenerator/main
PRODNAME = generate_level
# Variables pour la compilation des fichiers
CC        =  clang++
CFLAGS    =  -Wall -O3
STD = -std=c++11
LIBRARY = Library Platform Point4
INSTANCE = Instance PlatInstance Position Vec3

LEVELGEN = levelGenerator Polynome $(LIBRARY:%=Library/%) $(INSTANCE:%=Instance/%)

WORLDGEN = createWorld functions geometrie

TARGETS = $(LEVELGEN:%=LevelGenerator/%) $(WORLDGEN:%=WorldGenerator/%)
OBJECTS = $(TARGETS:=.o)


all : $(PROG)

%.o : %.cpp
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $(STD) $< -o $@

$(PROG): % : %.o $(OBJECTS)
	$(CC) $(LDFLAGS) $(STD) -o $(PRODNAME) $< $(OBJECTS) -lm

cleanall : clean
	rm -f $(PRODNAME)

clean :
	rm -f $(OBJECTS) $(PROG:=.o)
