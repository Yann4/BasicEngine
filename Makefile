CPP=main.cpp graphics.cpp gameObject.cpp game.cpp collision.cpp
H=dataTypes.h
ELF=app
LINKER_FLAGS=-lSDL2 -std=c++0x

all:
	g++ $(CPP) $(LINKER_FLAGS) -o $(ELF)
clean:
	rm $(ELF)
