# Makefile for the Huffman Compressor
CXX = g++
# Use -std=c++17 for modern C++ features
CXXFLAGS = -std=c++17 -Wall -Wextra

# The final executable name
TARGET = compressor

# All source files
SOURCES = main.cpp huffman_compressor.cpp

# All object files
OBJECTS = $(SOURCES:.cpp=.o)

# Default target: build the executable
all: $(TARGET)

# Rule to link the final executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Rule to compile source files into object files
%.o: %.cpp huffman_compressor.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean up build files
clean:
	rm -f $(TARGET) $(OBJECTS) *.huf

# Phony targets don't represent actual files
.PHONY: all clean
