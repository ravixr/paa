# Makefile for compiling a C++ source file

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

# Source file and target executable
SRC = subset_sum_problem.cpp
TARGET = run

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(TARGET)

.PHONY: all clean
