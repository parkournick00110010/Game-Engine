##
CC = g++
LANG_STD = -std=c++17
COMPILER_FLAGS = -Wall -Wfatal-errors
INCLUDE_PATH = -I"./libs/"
SRC_FILES = src/*.cpp \
						src/Game/*.cpp
LINKER_FLAGS = -lspdlog \
							 -lfmt -lSDL2 \
							 -lSDL2_image \
							 -lSDL2_ttf \
							 -lSDL2_mixer \
							 -llua5.3
OUTPUT = fantasia
##

build:
	$(CC) $(COMPILER_FLAGS) $(LANG_STD) $(INCLUDE_PATH) $(SRC_FILES) $(LINKER_FLAGS) -o $(OUTPUT);

run:
	./$(OUTPUT)

clean:
	rm $(OUTPUT)
