CXX = g++
CXXFLAGS = -std=c++17 -Wall -I src
TARGET = c4
SRC = src/main.cpp
HEADERS = src/c4.hpp

all: $(TARGET)

$(TARGET): $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
