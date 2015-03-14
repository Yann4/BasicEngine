OBJS=main.cpp graphics.cpp
ELF=app
LINKER_FLAGS=-lSDL2

all:
		g++ $(OBJS) $(LINKER_FLAGS) -o $(ELF)
