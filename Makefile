BUILD_DIR = build
INCLUDE_DIR = src/
SRC_FILES = src/*.cpp

CFLAGS = -Wall 

all: build chess-gui

build:
	mkdir $(BUILD_DIR)

chess-gui:
	g++ $(CFLAGS) -o $(BUILD_DIR)/chess-gui $(SRC_FILES)

clean:
	rm -rf $(BUILD_DIR)