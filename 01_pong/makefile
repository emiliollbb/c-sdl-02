#CC specifies which compiler we're using 
CC = gcc 

#COMPILER_FLAGS specifies the additional compilation options we're using 
# -w suppresses all warnings 
COMPILER_FLAGS = -w 

#LINKER_FLAGS specifies the libraries we're linking against 
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

# DEBUG FLAG specifies the flag used to add debug information
DEBUG_FLAG=-g

#This is the target that compiles our executable 

all: dirs main debug

dirs:
	mkdir -p bin

main: src/main.c
	$(CC) src/main.c src/pong.c $(COMPILER_FLAGS) $(LINKER_FLAGS) -o bin/pong

debug: src/main.c
	$(CC) src/main.c src/pong.c ${DEBUG_FLAG} $(COMPILER_FLAGS) $(LINKER_FLAGS) -o bin/pong_debug

clean:
	rm -rf bin
