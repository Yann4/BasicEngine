CPP=main.cpp graphics.cpp gameObject.cpp game.cpp qtree.cpp
H=dataTypes.h
ELF=app
LINKER_FLAGS=-lSDL2
STD=-std=c++11

all:
	g++ $(CPP) $(STD) $(LINKER_FLAGS) -o $(ELF)
clean:
	rm $(ELF)
