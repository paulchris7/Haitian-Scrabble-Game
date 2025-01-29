# Compiler and flags
CXX = g++
CPPFLAGS = -g -Wall
BIN_DIR = bin

# Default target
all: bin/Scrabble

# Linking the final executable
bin/Scrabble: bin/Player.o bin/UserInterface.o bin/Bag.o \
	bin/Square.o bin/Dictionary.o bin/Board.o
	$(CXX) $(CPPFLAGS) -I headers bin/Player.o bin/UserInterface.o \
	bin/Bag.o bin/Square.o bin/Dictionary.o \
	bin/Board.o Scrabble.cpp -o bin/Scrabble

# Compiling object files
bin/Player.o: headers/Player.h src/Player.cpp bin/.dirstamp
	$(CXX) $(CPPFLAGS) -c -I headers src/Player.cpp -o bin/Player.o

bin/Board.o: headers/Board.h src/Board.cpp bin/.dirstamp
	$(CXX) $(CPPFLAGS) -c -I headers src/Board.cpp -o bin/Board.o

bin/UserInterface.o: headers/UserInterface.h src/UserInterface.cpp bin/.dirstamp
	$(CXX) $(CPPFLAGS) -c -I headers src/UserInterface.cpp -o bin/UserInterface.o

bin/Bag.o: headers/Tile.h headers/Bag.h src/Bag.cpp bin/.dirstamp
	$(CXX) $(CPPFLAGS) -c -I headers src/Bag.cpp -o bin/Bag.o

bin/Square.o: headers/Square.h src/Square.cpp bin/.dirstamp
	$(CXX) $(CPPFLAGS) -c -I headers src/Square.cpp -o bin/Square.o

bin/Dictionary.o: headers/Dictionary.h src/Dictionary.cpp bin/.dirstamp
	$(CXX) $(CPPFLAGS) -c -I headers src/Dictionary.cpp -o bin/Dictionary.o

# Clean up build artifacts
.PHONY: clean
clean:
	rm -rf bin

# Ensure bin directory exists
bin/.dirstamp:
	mkdir -p bin
	echo > bin/.dirstamp

# 1. Variable Definitions
# CXX = g++
# Defines the C++ compiler to be used in the build process (GNU C++ Compiler).

# CPPFLAGS = -g -Wall
# Compiler flags:
# -g: Generates debugging information.
# -Wall: Enables most common warnings.

# BIN_DIR = bin
# Directory for the output of the build process (object files and final executable).

# 2. The Default Target: all
# all: bin/Scrabble
# Default target. When make is run without specifying a target, it builds this target.

# 3. Target: bin/Scrabble (Final Executable)
# bin/Scrabble: bin/Player.o bin/UserInterface.o bin/Bag.o bin/Square.o bin/Dictionary.o bin/Board.o
# Links the final executable from the object files.

# $(CXX) $(CPPFLAGS) -I lib bin/Player.o bin/UserInterface.o bin/Bag.o bin/Square.o bin/Dictionary.o bin/Board.o Scrabble.cpp -o bin/Scrabble
# Compilation command:
# -I lib: Includes the lib directory for header files.
# Links object files and Scrabble.cpp into the final executable bin/Scrabble.

# 4. Compilation Targets for Object Files
# Each object file (e.g., bin/Player.o) has a compilation rule.

# bin/Player.o: lib/Player.h src/Player.cpp bin/.dirstamp
# $(CXX) $(CPPFLAGS) -c -I lib src/Player.cpp -o bin/Player.o
# Dependencies:
# - lib/Player.h: Header file.
# - src/Player.cpp: Source file.
# - bin/.dirstamp: Ensures bin directory exists.
# Compilation command:
# -c: Compiles source file into an object file without linking.

# Similar rules for other object files (bin/Board.o, bin/UserInterface.o, etc.).

# 5. Target: clean
# .PHONY: clean
# clean:
# Removes the bin directory and its contents.

# 6. Target: bin/.dirstamp (Directory Setup)
# bin/.dirstamp:
# mkdir -p bin
# echo > bin/.dirstamp
# Ensures bin directory exists before compiling object files.

# Summary of the Build Process:
# 1. Compilation of Object Files:
# - Each source file (src/*.cpp) is compiled into its respective object file (bin/*.o).
# - Flags -g and -Wall are used for debugging and warnings.
# - -I lib ensures the compiler finds header files in the lib directory.

# 2. Linking Object Files into the Executable:
# - Object files are linked together with Scrabble.cpp to produce the final executable bin/Scrabble.

# 3. Clean-up:
# - make clean removes the bin directory and all its contents.

# 4. Directory Creation:
# - bin/.dirstamp ensures the bin directory exists before object files are written to it.

# Conclusion:
# This Makefile automates the build process for a C++ project by defining rules for compiling source files, linking them into an executable, and cleaning up build artifacts. The use of variables for compiler flags and directories enhances maintainability and flexibility.