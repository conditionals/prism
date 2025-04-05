CC = g++
CFLAGS = -Wall -std=c++20
INCLUDE_DIR = include
SRC_DIR = src
TARGET = prism

SOURCES = main.cpp \
          $(SRC_DIR)/tokenizer.cpp \
          $(SRC_DIR)/parser.cpp \
          $(SRC_DIR)/interpreter.cpp

OBJECTS = $(SOURCES:.cpp=.o)
HEADERS = $(INCLUDE_DIR)/tokenizer.hpp \
          $(INCLUDE_DIR)/parser.hpp \
          $(INCLUDE_DIR)/interpreter.hpp

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)
	rm -f $(OBJECTS)

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean

