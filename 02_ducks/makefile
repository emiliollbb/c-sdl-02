#CC specifies which compiler we're using 
CC = gcc 

#COMPILER_FLAGS specifies the additional compilation options we're using 
# -w suppresses all warnings 
COMPILER_FLAGS = -w -c

#LINKER_FLAGS specifies the libraries we're linking against 
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm

# DEBUG FLAG specifies the flag used to add debug information
DEBUG_FLAG=-g

DIRS=mkdir -p bin

#This is the target that compiles our executable 

all: ducks.o ducks

ducks.o: src/ducks.c src/ducks.h
	$(DIRS) && $(CC) src/ducks.c $(COMPILER_FLAGS) -o bin/ducks.o

ducks: bin/ducks.o
	$(DIRS) && $(CC) ../01_pong/bin/main.o bin/ducks.o $(LINKER_FLAGS) -o bin/ducks

ducks_debug: ../01_pong/src/main.c
	$(CC) ../01_pong/src/main.c bin/ducks.o $(LINKER_FLAGS) -o bin/ducks

clean:
	rm -rf bin
