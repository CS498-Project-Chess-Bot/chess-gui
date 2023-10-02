BUILD_DIR = build
EXEC_FILE = chess-gui

INCLUDE_DIRS = src/ vendor/glad/include vendor/glfw/include vendor/glm
INCLUDE_PARAMS = $(foreach d, $(INCLUDE_DIRS), -I$d)

### library order matters! glfw3 needs to be before the others
LIBS = glfw3 gdi32 opengl32 
LIBS_PARAMS = $(foreach l, $(LIBS), -l$l)

LIB_DIRS = vendor/glfw/lib-mingw-w64
LIB_DIRS_PARAMS = $(foreach l, $(LIB_DIRS), -L$l)

SRC_FILES = $(wildcard src/*.cpp) vendor/glad/src/glad.c
HEADER_FILES = $(wildcard src/*.hpp)
SHADER_FILES = $(wildcard shaders/*.vs) $(wildcard shaders/*.fs)
CFLAGS = -g -Wall -Werror -pedantic -std=c++23

ifeq ($(OS), Windows_NT)
EXEC_FILE = chess-gui-windows
else 
EXEC_FILE = chess-gui-macos
endif

all: $(EXEC_FILE) shaders

build:
	mkdir -p $(BUILD_DIR)

shaders: $(SHADER_FILES)
	mkdir -p $(BUILD_DIR)/shaders
	cp -r shaders $(BUILD_DIR)

$(EXEC_FILE): $(SRC_FILES) $(HEADER_FILES) build
	g++ $(CFLAGS) $(INCLUDE_PARAMS) $(LIB_DIRS_PARAMS) -o $(BUILD_DIR)/$(EXEC_FILE) $(SRC_FILES)  $(LIBS_PARAMS) 

run:
	cd $(BUILD_DIR); pwd; ./$(EXEC_FILE)

clean:
	rm -rf $(BUILD_DIR)