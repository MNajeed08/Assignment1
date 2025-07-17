# Makefile for bots assignment

CXX = g++
CXXFLAGS = -Wall -g -std=c++20
LDFLAGS = -lpthread
TARGET = bots
SRC = main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)
