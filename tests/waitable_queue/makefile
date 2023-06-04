CXX = g++
CC = $(CXX)

CFLAGS = -pedantic -Wall -Werror
CFLAGS += -ggdb
CXXFLAGS = $(CFLAGS) -std=c++17

LDLIBS = -pthread

CPPFLAGS = -DDEBUG
CPPFLAGS = -I$(INCLUDES_DIR)

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

SOURCE := utest.cpp
TARGET := utest

all: $(TARGET)

check : $(TARGET)
	@./$(TARGET) -v

recheck: clean check

clean:
	@$(RM) ./$(TARGET) *.o

vala: $(TARGET)
	valgrind --leak-check=yes --track-origins=yes ./$(TARGET)

hell: $(TARGET)
	valgrind  --tool=helgrind ./$(TARGET) 2> hell.txt

.PHONY : make clean check recheck all vala hell