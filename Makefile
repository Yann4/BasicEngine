OBJS=main.cpp graphics.cpp gameObject.cpp game.cpp
ELF=app
LINKER_FLAGS=-lSDL2 -std=c++0x

all:
		g++ $(OBJS) $(LINKER_FLAGS) -o $(ELF)
