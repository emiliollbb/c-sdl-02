#CC specifies which compiler we're using 
CC = gcc 

#COMPILER_FLAGS specifies the additional compilation options we're using 
# -w suppresses all warnings 
COMPILER_FLAGS = -w -c

#LINKER_FLAGS specifies the libraries we're linking against 
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

# DEBUG FLAG specifies the flag used to add debug information
DEBUG_FLAG=-g

#This is the target that compiles our executable 

all: dirs game.o game

dirs:
	mkdir -p bin

game.o: src/game.c src/game.h
	$(CC) src/game.c $(COMPILER_FLAGS) -o bin/game.o

game: bin/game.o
	$(CC) ../01_pong/bin/main.o bin/game.o $(LINKER_FLAGS) -o bin/game

clean:
	rm -rf bin
