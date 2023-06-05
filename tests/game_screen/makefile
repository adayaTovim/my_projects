$(CXX)=g++
CC=CXX

CFLAGS = -pedantic -Wall -Werror
CFLAGS += -ggdb
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -ljsoncpp
CXXFLAGS = $(CFLAGS) -std=c++17

CPPFLAGS = -DDEBUG
CPPFLAGS += -I$(INCLUDES_DIR)

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

OBJECTS = $(SOURCES_DIR)/game_screen.cpp \
          $(SOURCES_DIR)/font.cpp \
		  $(SOURCES_DIR)/ball.cpp \
		  $(SOURCES_DIR)/brick.cpp \
		  $(SOURCES_DIR)/player.cpp \
		  $(SOURCES_DIR)/paddle.cpp 


SOURCE = utest.cpp $(OBJECTS) 
TARGET = utest

all: $(TARGET)

utest : $(SOURCE)

check : $(TARGET) 
	@./$(TARGET) -v

recheck: clean check

clean:
	@$(RM) -f ./$(TARGET) *.o


.PHONY : make clean check recheck all

make:
	@echo 'Attend a maker faire'
	@${TRUE}
