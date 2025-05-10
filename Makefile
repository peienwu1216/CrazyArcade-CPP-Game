# Compiler and compiler flags
CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -pedantic -Isrc
LDFLAGS =

# Project name
TARGET = CrazyArcade

# Source files directory
SRCDIR = src

# Find all .cpp files in the source directory
# Note: This lists all .cpp files in src/. Ensure only necessary files are there
# or list them explicitly if needed.
# For your specific files:
# SOURCES = $(SRCDIR)/main.cpp $(SRCDIR)/GameObject.cpp $(SRCDIR)/Globals.cpp $(SRCDIR)/GameCrazyArcade.cpp $(SRCDIR)/Menu.cpp $(SRCDIR)/AIController.cpp
# Using wildcard is more general if all .cpp in src should be compiled:
SOURCES = $(wildcard $(SRCDIR)/*.cpp)

# Generate object file names from source file names
# This will create .o files in the root directory alongside the Makefile
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=%.o)

# Default target: build the executable
all: $(TARGET)

# Rule to link the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Rule to compile source files into object files
# This rule compiles .cpp files from SRCDIR into .o files in the current directory
%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Target to run the executable
run: all
	./$(TARGET)

# Target to clean up build files
clean:
		rm -f $(TARGET) $(OBJECTS)

# Phony targets (targets that are not actual files)
.PHONY: all run clean