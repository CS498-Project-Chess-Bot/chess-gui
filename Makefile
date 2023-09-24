BUILD_DIR = build
EXEC_FILE = chess-gui

INCLUDE_DIRS = src/ src/vendor/glad/include src/vendor/glfw/include
INCLUDE_PARAMS = $(foreach d, $(INCLUDE_DIRS), -I$d)

LIB_DIRS = src/vendor/glfw/lib-mingw-w64
LIB_DIRS_PARAMS = $(foreach l, $(LIB_DIRS), -L$l)

### library order matter! glfw3 needs to be before the others
LIBS = glfw3 gdi32 opengl32 
LIBS_PARAMS = $(foreach l, $(LIBS), -l$l)

OBJ_DIR = build/
SRC_FILES = $(wildcard src/*.cpp) src/vendor/glad/src/glad.c
HEADER_FILES = $(wildcard src/*.hpp)
CFLAGS = -g -Wall -Werror -pedantic -std=c++23

ifeq ($(OS), Windows_NT)
EXEC_FILE = chess-gui-windows
else 
EXEC_FILE = chess-gui-macos
endif

all: $(EXEC_FILE)

build:
	mkdir -p $(BUILD_DIR)

$(EXEC_FILE): $(SRC_FILES) $(HEADER_FILES) build
	g++ $(CFLAGS) $(INCLUDE_PARAMS) $(LIB_DIRS_PARAMS) -o $(BUILD_DIR)/$(EXEC_FILE) $(SRC_FILES)  $(LIBS_PARAMS) 

run:
	./$(BUILD_DIR)/$(EXEC_FILE)

clean:
	rm -rf $(BUILD_DIR)