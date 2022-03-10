EXEC = prog.exe
CXX = g++
CXX_FLAGS = -I include -Wall -Wextra -pedantic -Wno-unused-parameter -Werror -c
LD_FLAGS = -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

SRC1 = $(wildcard src/*.cpp)
SRC2 = $(wildcard src/*/*.cpp)

OBJ1 = ${SRC1:.cpp=.o}
OBJ2 = ${SRC2:.cpp=.o}


all : $(EXEC)

$(EXEC) : $(OBJ1) $(OBJ2)
	$(CXX) -o $@ $^ $(LD_FLAGS)


src/%.o : src/%.cpp
	$(CXX) -o $@ $< $(CXX_FLAGS)

src/%/%.o : src/%/%.cpp
	$(CXX) -o $@ $< $(CXX_FLAGS)