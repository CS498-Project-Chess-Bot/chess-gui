BUILD_DIR = build
EXEC_FILE = chess-gui

INCLUDE_DIRS = src/ vendor/glad/include vendor/glfw/include vendor/glm vendor/stb_image
INCLUDE_PARAMS = $(foreach d, $(INCLUDE_DIRS), -I$d)

### library order matters! glfw3 needs to be before the others
LIBS = glfw3 gdi32 opengl32 
LIBS_PARAMS = $(foreach l, $(LIBS), -l$l)

LIB_DIRS = vendor/glfw/lib-mingw-w64
LIB_DIRS_PARAMS = $(foreach l, $(LIB_DIRS), -L$l)

SRC_DIR = src
SRC_FILES_FROM_DIR = $(wildcard src/*.cpp)
SRC_FILES = $(notdir $(SRC_FILES_FROM_DIR))
OBJ_FILES = $(SRC_FILES:%.cpp=%.o)
GLAD_SRC = vendor/glad/src

HEADER_FILES = $(wildcard src/*.hpp)
SHADER_FILES = $(wildcard shaders/*.vs) $(wildcard shaders/*.fs)
BUILD_SHADER_FILES = $(SHADER_FILES:%=$(BUILD_DIR)/%)
TEXTURE_FILES = $(wildcard textures/*)
BUILD_TEXTURE_FILES = $(TEXTURE_FILES:%=$(BUILD_DIR)/%)

PY_FILES = $(wildcard chess-engine/*.py)
BUILD_PY_FILES = $(BUILD_DIR)/MoveGenerator.exe

CFLAGS = -g -Wall -Werror -pedantic -std=c++23
LFLAGS = -Wl,--allow-multiple-definition

ifeq ($(OS), Windows_NT)
EXEC_FILE = chess-gui-windows
else 
EXEC_FILE = chess-gui-macos
endif

all: build $(BUILD_SHADER_FILES) $(BUILD_TEXTURE_FILES) $(BUILD_PY_FILES) $(EXEC_FILE) 

build:
	mkdir -p $(BUILD_DIR)

$(BUILD_SHADER_FILES): $(SHADER_FILES)
	mkdir -p $(BUILD_DIR)/shaders
	cp -r shaders $(BUILD_DIR)

$(BUILD_TEXTURE_FILES): $(TEXTURE_FILES)
	mkdir -p $(BUILD_DIR)/textures
	cp -r textures $(BUILD_DIR)

$(BUILD_PY_FILES) : $(PY_FILES)
	cd chess-engine; ls; ./BuildEngine.bat
	cp chess-engine/MoveGenerator.exe $(BUILD_DIR)

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.cpp $(SRC_DIR)/%.hpp
	g++ -c $(CFLAGS) -o $@ $< $(INCLUDE_PARAMS)

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.cpp
	g++ -c $(CFLAGS) -o $@ $< $(INCLUDE_PARAMS)

$(BUILD_DIR)/glad.o : $(GLAD_SRC)/glad.c
	g++ -c $(CFLAGS) -o $@ $< $(INCLUDE_PARAMS)

$(EXEC_FILE): $(OBJ_FILES:%=$(BUILD_DIR)/%) $(BUILD_DIR)/glad.o
	g++ $(CFLAGS) $(LFLAGS) $(INCLUDE_PARAMS) $(LIB_DIRS_PARAMS) -o $(BUILD_DIR)/$(EXEC_FILE) $^ $(LIBS_PARAMS) 

run:
	cd $(BUILD_DIR); ./$(EXEC_FILE)

clean:
	rm -rf $(BUILD_DIR)