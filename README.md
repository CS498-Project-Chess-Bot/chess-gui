# chess-gui
C++ Frontend Chess GUI

A chess GUI developed using OpenGL C++ for CS498

By: Matthew Whalen, Cameron Egbert, Anna Thompson, and Ethan Tate

## Current Issues
- Queen movement is a bit wacky, sometimes fails on long distances for black
- Checks and Checkmate is not enforced, therefore the game cannot end
- En Passant is also not possible
- Castling is not legal yet
- Players cannot switch from colors
- Chess engine not yet integrated with the GUI

## Getting Started

## Running Pre-Compiled Binaries
 - Download latest release build from the release section on the right column of the repo
 - Unzip the `.zip` file and place anywhere
 - Please maintain the directory structure inside the extracted folder. The shaders and textures are required to run
 - Run the `chess-gui-<target>.exe` and enjoy

## Compiling From Source

### For Windows:
- Install [w64devkit](https://github.com/skeeto/w64devkit)
- Get the latest zip release and extract it
- Add folder to `PATH`
- Restart PC
- Open `cmd`
- Run `make` and check that it finds the command

### For Linux and MacOS:
- Currently the project does not have support for mac or linux

## Running chess-gui
- When inside chess-gui directory, run `make`
- to execute code, run `make run`
