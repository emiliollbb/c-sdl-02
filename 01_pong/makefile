#CC specifies which compiler we're using 
CC = gcc 

#COMPILER_FLAGS specifies the additional compilation options we're using 
# -w suppresses all warnings 
COMPILER_FLAGS = -w -c

#LINKER_FLAGS specifies the libraries we're linking against 
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

# DEBUG FLAG specifies the flag used to add debug information
DEBUG_FLAG=-g

DIRS=mkdir -p bin

#This is the target that compiles our executable 

all: bin/pong

bin/main.o: src/main.c src/main.h
	$(DIRS) && $(CC) src/main.c $(COMPILER_FLAGS) -o bin/main.o
	
bin/pong.o: src/pong.c src/pong.h
	$(DIRS) && $(CC) src/pong.c $(COMPILER_FLAGS) -o bin/pong.o

bin/pong: bin/main.o bin/pong.o
	$(DIRS) && $(CC) bin/main.o bin/pong.o $(LINKER_FLAGS) -o bin/pong

debug: src/main.c
	$(DIRS) && $(CC) src/main.c src/pong.c ${DEBUG_FLAG} $(COMPILER_FLAGS) $(LINKER_FLAGS) -o bin/pong_debug

clean:
	rm -rf bin
