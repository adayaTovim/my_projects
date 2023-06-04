CXX=g++
$(CC)=$(CXX)

CFLAGS = -pedantic -Wall -Werror
CFLAGS += -g
CXXFLAGS = $(CFLAGS) -std=c++17

CPPFLAGS = -DDEBUG
CPPFLAGS = -I$(INCLUDES_DIR)

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src


SOURCE := utest.cpp
TARGET := utest

all: $(TARGET)

$(SOURCES_DIR)/color_image.cpp: $(INCLUDES_DIR)/color_image.hpp

$(SOURCES_DIR)/draw_primitives.cpp: $(INCLUDES_DIR)/draw_primitives.hpp

$(SOURCE) : $(INCLUDES_DIR)/inl/matrix.hxx $(INCLUDES_DIR)/matrix.hpp $(SOURCES_DIR)/draw_primitives.cpp $(SOURCES_DIR)/color_image.cpp $(INCLUDES_DIR)/mu_test.h

$(TARGET): $(SOURCES_DIR)/draw_primitives.cpp $(SOURCES_DIR)/color_image.cpp

check : $(TARGET)
	@./$(TARGET) -v

recheck: clean check

clean:
	@$(RM) -f ./$(TARGET) *.o


.PHONY : make clean check recheck all

make:
	@echo 'Attend a maker faire'
	@${TRUE}